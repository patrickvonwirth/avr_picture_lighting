/*
 * KeyboardSystemController.cpp
 *
 *  Created on: 24.07.2016
 *      Author: patrick
 */

#include "GUI.h"
#include "System.h"
#include "LCD.h"

ksc_FSMState GUI::fsmState = sConfigChoose;
SystemConfiguration GUI::config = sk_brightness;
uint8_t GUI::cachedInitValue = 0; // will be initialized later


void GUI::sConfigChoose(const ksc_control aControl) {
  switch (aControl) {
  case ksc_cUP:
    if (config == SystemConfiguration(sk_STATE_COUNT-1)) {
      config = SystemConfiguration(0);
    } else {
      config = SystemConfiguration(config + 1);
    }
    break;
  case ksc_cDown:
    if (config == SystemConfiguration(0)) {
      config = SystemConfiguration(sk_STATE_COUNT-1);
    } else {
      config = SystemConfiguration(config - 1);
    }
    break;
  case ksc_cOK:
    fsmState = sConfigChange;
    break;
  case ksc_cSafe:
    System::initialize(); // restore initial values
    break;
  case ksc_cRefresh:
    LCD::setLCD(ls_F, false, LCDSegment(config), false);
    break;
  case ksc_cInit:
    // nothing to do here
    break;
  }
}

void GUI::sConfigChange(const ksc_control aControl) {
  uint8_t value = System::getKonfiguration(config); // often used
  switch (aControl) {
  case ksc_cUP:
    System::setKonfiguration(config, value + 1);
    break;
  case ksc_cDown:
    System::setKonfiguration(config, value - 1);
    break;
  case ksc_cOK:
    fsmState = sConfigChoose;
    break;
  case ksc_cSafe:
    System::setInitValue(config, value);
    break;
  case ksc_cRefresh:
    LCD::setDecimalNumber(value, (value == cachedInitValue), false);
    break;
  case ksc_cInit:
    cachedInitValue = System::getInitValue(config);
    break;
  }
}

void GUI::ControlUp() {
  fsmState(ksc_cUP);
  fsmState(ksc_cRefresh);
}

void GUI::ControlDown() {
  fsmState(ksc_cDown);
  fsmState(ksc_cRefresh);
}

void GUI::ControlOK() {
  fsmState(ksc_cOK);
  fsmState(ksc_cInit);
  fsmState(ksc_cRefresh);
}

void GUI::ControlSafe() {
  fsmState(ksc_cSafe);
  fsmState(ksc_cInit);
  fsmState(ksc_cRefresh);
}

void GUI::ReloadLCD() {
  fsmState(ksc_cInit);
  fsmState(ksc_cRefresh);
}
