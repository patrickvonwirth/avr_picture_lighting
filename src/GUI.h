/*
 * KeyboardSystemController.h
 *
 *  Created on: 24.07.2016
 *      Author: patrick
 */

#ifndef SRC_GUI_H_
#define SRC_GUI_H_

#include <avr/io.h>

#include "konfigurations.h"

enum ksc_control {
  ksc_cUP      = 0,
  ksc_cDown    = 1,
  ksc_cOK      = 2,
  ksc_cSafe    = 3,
  ksc_cRefresh = 4,
  ksc_cInit    = 5
};

typedef void(*ksc_FSMState)(const ksc_control aControl);

class GUI {
private:
  // FSM
  static ksc_FSMState fsmState;
  static SystemKonfiguration config;
  static uint8_t cachedInitValue;
  static void sConfigChoose(const ksc_control aControl);
  static void sConfigChange(const ksc_control aControl);
public:
  static void ControlUp();
  static void ControlDown();
  static void ControlOK();
  static void ControlSafe();
  static void ReloadLCD();
};

#endif /* SRC_GUI_H_ */
