/*
 * UntimedEventsManagement.cpp
 *
 *  Created on: 24.07.2016
 *      Author: patrick
 */

#include "UntimedEventsManagement.h"

bool UntimedEventsManagement::executeNextEvent() {
  UntimedEvent event;
  if (popInto(&event)) {
    UntimedEvent_Actions[event]();
    return true;
  } else {
    return false;
  }
}

void UntimedEventsManagement::addEvent(const UntimedEvent aEvent) {
  push(aEvent);
}
