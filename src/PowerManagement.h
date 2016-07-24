/*
 * PowerManagement.h
 *
 *  Created on: 04.03.2016
 *      Author: patrick
 */

#ifndef SRC_POWERMANAGEMENT_H_
#define SRC_POWERMANAGEMENT_H_

#include <avr/io.h>

enum hw_Timer {
    hwt_InternalTimeEvents = 0, // Timer 0
    hwt_ExternalLightPWM   = 1, // Timer 1
    hwt_ExternalDisplayDC  = 2  // Timer 2
};

class PowerManagement {
private:
  // this component will be used by the main method and interrupt routines,
  // so make the variables volatile to avoid wrong compiler optimizations
  static volatile uint8_t activeTimerSet;
public:
  static void registerActiveTimer(const hw_Timer aTimer);
  static void releaseStoppedTimer(const hw_Timer aTimer);
  static void sleep();
};

#endif /* SRC_POWERMANAGEMENT_H_ */
