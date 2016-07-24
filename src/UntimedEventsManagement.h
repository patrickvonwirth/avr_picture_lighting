/*
 * UntimedEventsManagement.h
 *
 *  Created on: 24.07.2016
 *      Author: patrick
 */

#ifndef SRC_UNTIMEDEVENTSMANAGEMENT_H_
#define SRC_UNTIMEDEVENTSMANAGEMENT_H_

#include "avr_lib/avrp/FixSizeArrayQueue.h"
#include "hw_definitions.h"
#include "events.h"

class UntimedEventsManagement : private avrp::FixSizeArrayQueue<UT_EVENTSQUEUE_SIZEBITS, UntimedEvent> {
public:
  static bool executeNextEvent(); // return true, if an event has been executed
  static void addEvent(const UntimedEvent aEvent);
};

#endif /* SRC_UNTIMEDEVENTSMANAGEMENT_H_ */
