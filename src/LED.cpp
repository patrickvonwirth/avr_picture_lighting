/*
 * LED.cpp
 *
 *  Created on: 12.06.2016
 *      Author: patrick
 */

#include "LED.h"

#include "hw_definitions.h"
#include "PowerManagement.h"

void LED::startPWM() {
  // !! the order is important !!
  PowerManagement::registerActiveTimer(hwt_ExternalLightPWM);
  TCCR1B = TCCR1B_PWM_Active; // starts the timer
  TCCR1A = TCCR1A_PWM_Active; // switches to PWM output
}

void LED::stopPWM() {
  // !! the order is important !!
  TCCR1A = TCCR1A_PWM_Inactive; // switch to digital output
  TCCR1B = TCCR1B_PWM_Inactive; // stop timer
  PowerManagement::releaseStoppedTimer(hwt_ExternalLightPWM);
}

uint16_t LED::percentToPWM(const uint8_t aPercent) {
  return (((aPercent * aPercent) + aPercent) >> 1); // (x^2 +x) / 2
}

void LED::setPWM(const uint8_t aPercent) {
  // !! the order is important !!
  if (aPercent == 0) { // switch off completely
    LED_PWM::setActive(false); // set digital output to "off"
    stopPWM();
  } else if (aPercent >= 100) { // switch on digitally
    LED_PWM::setActive(true); // set digital output to "on"
    stopPWM(); // switch to digital mode
  } else {
    OCR1A = percentToPWM(aPercent); // set new PWM
    startPWM(); // start PWM, no matter whether it already has been started
  }
}
