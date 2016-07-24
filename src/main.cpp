/*
 * main.cpp
 *
 *  Created on: 18.02.2016
 *      Author: patrick
 */

#include <avr/interrupt.h>

#include "hw_definitions.h"
#include "avr_lib/avrp/Randuint8.h"
#include "Keyboard.h"
#include "PowerManagement.h"
#include "TimedEventsManagement.h"
#include "UntimedEventsManagement.h"
#include "System.h"
#include "GUI.h"

// Button0 Interrupt
ISR(INT0_vect) {
  Keyboard::startSampling();
}

// Button1 Interrupt
ISR(INT1_vect) {
  Keyboard::startSampling();
}

// Internal Timer Interrupt
ISR(TIMER0_OVF_vect) {
  TimedEventsManagement::nextStep();
}

int main() {
  // initialize hardware
  initialize_controller();
  avrp::sranduint8_eeprom();

  // load initial system konfiguration from eeprom
  System::initialize();

  // initialize GUI
  GUI::ReloadLCD();

  // run program
  while (true) {
    // timed events are of higher priority than untimed ones
    TimedEventsManagement::executeEvents(); // execute all timed events right after wake-up
    // execute ONE untimed event, if there is one, otherwise go to sleep
    if (!(UntimedEventsManagement::executeNextEvent())) {
      PowerManagement::sleep();
    }
  }

  return 0;
}
