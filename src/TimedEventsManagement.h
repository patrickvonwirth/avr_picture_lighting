/*
 * TimedEventsManagement.h
 *
 *  Created on: 02.03.2016
 *      Author: patrick
 */

#ifndef SRC_TIMEDEVENTSMANAGEMENT_H_
#define SRC_TIMEDEVENTSMANAGEMENT_H_

#include <avr/io.h>

#include "events.h"

class TimedEventsManagement {
private:
  // this component will be used by the main method and interrupt routines,
  // so make the variables volatile to avoid wrong compiler optimizations
  static volatile TimedEvent_uint8_Array remainingSteps;
  static volatile TimedEvent_BitArray_t activeEvents;
  static void pause();
  static void resume();
public:
  static void nextStep();
  static void executeEvents();
  static void activateEvent(const TimedEvent aEvent);
  static void deactivateEvent(const TimedEvent aEvent);
};

#endif /* SRC_TIMEDEVENTSMANAGEMENT_H_ */
