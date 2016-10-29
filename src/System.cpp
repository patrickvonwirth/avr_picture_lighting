/*
 * System.cpp
 *
 *  Created on: 02.07.2016
 *      Author: patrick
 */

#include "System.h"

#include <avr/eeprom.h>

#include "avr_lib/avrp/Randuint8.h"
#include "TimedEventsManagement.h"
#include "LED.h"

SystemConfiguration_Array System::values = SystemConfiguration_Array_ZEROS; // initialization useless, but mandatory

SystemConfiguration_Array EEMEM System::initialValues = SystemConfiguration_Array_EEPROM_INITIAL_VALUES;

uint8_t System::nextFlicker = 0;
uint8_t System::rand_shift = 0;
uint8_t System::rand_minimalBitMask = 0xFF;
uint8_t System::rand_missedRange = 0;

uint8_t System::validate(const SystemConfiguration aSystemKonfiguration, const uint8_t aValue) {
  if (aValue <= SystemConfiguration_MinValues[aSystemKonfiguration]) {
    return SystemConfiguration_MinValues[aSystemKonfiguration];
  }
  if (aValue >= SystemConfiguration_MaxValues[aSystemKonfiguration]) {
    return SystemConfiguration_MaxValues[aSystemKonfiguration];
  }
  return aValue;
}

void System::initializeRand() {
  if (values[sk_variance] == 0) {
    return; // random deactivated
  }
  // compute minimal bit mask
  rand_minimalBitMask = 0b01111111;
  while ((values[sk_variance] & rand_minimalBitMask) == values[sk_variance]) {
    rand_minimalBitMask = (rand_minimalBitMask >> 1);
  }
  rand_minimalBitMask = (rand_minimalBitMask << 1) | 0b00000001;
  // compute missed Range (below computation avoids underflow errors)
  rand_missedRange = rand_minimalBitMask - values[sk_variance];
  rand_missedRange = values[sk_variance] - rand_missedRange;
  // reset shift
  rand_shift = 0;
}

uint8_t System::rangedRand() {
  uint8_t value = avrp::randuint8() & rand_minimalBitMask; // just use mandatory bits of high byte of random number
  // compute correct shifted value
  if (value < rand_shift) {
    value = values[sk_variance] - value; // since rand is equally distributed, the order is unimportant
  } else {
    value -= rand_shift;
    if (value > values[sk_variance]) {
      value -= values[sk_variance];
    }
  }
  // compute next shift
  rand_shift += rand_missedRange;
  if (rand_shift >= values[sk_variance]) {
    rand_shift = 0;
  }
  //
  return value;
}

void System::updateLEDOutput() {
  if ((values[sk_brightness] && values[sk_variance]) == 0) { // if one of these values are zero
    // either no variance -> static Light, or light turned of -> ignore variance
    LED::setPWM(values[sk_brightness]);
  } else { // flickering light
    // activate flickering
    nextFlicker = (avrp::randuint8() & flicker_tick_random_mask) + 1;
    TimedEventsManagement::activateEvent(te_flicker_tick);
    // set LED Output
    uint8_t brightness = values[sk_brightness];
    for (uint8_t i = 0; i < 4; i++) { // add four times random variance
      brightness += rangedRand();
    }
    uint8_t doubleVariance = values[sk_variance] << 1;
    if (brightness < doubleVariance) {
      brightness = doubleVariance - brightness -1; // the -1 is to add the first neighbor to zero
    } else {
      brightness -= doubleVariance; // subtract here, to avoid overflows in the following calculations
      if (brightness > 100) {
        brightness = 201 - brightness;
      }
    }
    LED::setPWM(brightness);
  }
}

void System::initialize() {
  eeprom_read_block(&values, &initialValues, sizeof(initialValues));
  initializeRand();
  updateLEDOutput();
}

void System::flicker() {
  nextFlicker--;
  if (nextFlicker == 0) {
    updateLEDOutput();
  } else {
    TimedEventsManagement::activateEvent(te_flicker_tick);
  }
}

uint8_t System::getKonfiguration(const SystemConfiguration aSystemKonfiguration) {
  return values[aSystemKonfiguration];
}

void System::setKonfiguration(const SystemConfiguration aSystemKonfiguration, const uint8_t aNewValue) {
  values[aSystemKonfiguration] = validate(aSystemKonfiguration, aNewValue);
  if (aSystemKonfiguration == sk_variance) {
    initializeRand();
  }
  updateLEDOutput();
}

uint8_t System::getInitValue(const SystemConfiguration aSystemKonfiguration) {
  return eeprom_read_byte(&initialValues[aSystemKonfiguration]);
}

void System::setInitValue(const SystemConfiguration aSystemKonfiguration, const uint8_t aNewValue) {
  eeprom_update_byte(&initialValues[aSystemKonfiguration], validate(aSystemKonfiguration, aNewValue));
}
