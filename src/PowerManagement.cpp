/*
 * PowerManagement.cpp
 *
 *  Created on: 04.03.2016
 *      Author: patrick
 */

#include "PowerManagement.h"

#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "hw_definitions.h"

volatile uint8_t PowerManagement::activeTimerSet = 0; // initialize without any timer active

void PowerManagement::registerActiveTimer(const hw_Timer aTimer) {
  activeTimerSet |= (1 << aTimer);
}

void PowerManagement::releaseStoppedTimer(const hw_Timer aTimer) {
  activeTimerSet &= ~(1 << aTimer);
}

void PowerManagement::sleep() {
  cli(); // atomic operation
  if (activeTimerSet == 0) {
    MCUCR = MCUCR_SYSTEM_POWERDOWN; // this also activates sleep enabled
  } else {
    MCUCR = MCUCR_SYSTEM_ACTIVETIMER; // this also activates sleep enabled
  }
  sei();
  sleep_cpu();

  // after wake-up disable sleep
  MCUCR = MCUCR_SYSTEM_FULLACTIVE;
}
