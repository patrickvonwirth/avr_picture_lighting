/*
 * TimedEventsManagement.cpp
 *
 *  Created on: 02.03.2016
 *      Author: patrick
 */

#include "TimedEventsManagement.h"

#include <avr/interrupt.h>

#include "hw_definitions.h"
#include "PowerManagement.h"

volatile TimedEvent_uint8_Array TimedEventsManagement::remainingSteps = TimedEvent_Startup_Delay_Initialization;

volatile TimedEvent_BitArray_t TimedEventsManagement::activeEvents = TimedEvent_Startup_Active_Initialization;

void TimedEventsManagement::pause() {
  TCCR0 = TCCR0_EVENTS_DOWN;
  PowerManagement::releaseStoppedTimer(hwt_InternalTimeEvents);
}

void TimedEventsManagement::resume() {
  PowerManagement::registerActiveTimer(hwt_InternalTimeEvents);
  TCCR0 = TCCR0_EVENTS_UP;
}

void TimedEventsManagement::nextStep() {
  bool stop = true;
  for (uint8_t i=0; i < te_STATE_COUNT; i = i + 1) {
    // decrement the remaining steps if there are some
    if (remainingSteps[i] > 0) {
      stop = false;
      remainingSteps[i]--;
      if (remainingSteps[i] == 0) { // if the remaining steps reaches zero activate the event
        activeEvents |= (1 << i);
      }
    }
  }
  if (stop) {
    pause(); // stop the timer, if there are no actions to be done
  }
}

void TimedEventsManagement::executeEvents() {
  cli(); // take an atomic snapshot of the current events and reset them
  uint8_t currentEvents = activeEvents;
  activeEvents = 0; // reset the events
  sei();
  // execute the snapshot of the events
  for (uint8_t i=0; i < te_STATE_COUNT; i++) {
    // execute all current active Events
    // usually, this will be just one action
    if ((currentEvents & (1 << i)) > 0) {
      TimedEvent_Actions[i](); // execute the action
    }
  }
}

void TimedEventsManagement::activateEvent(const TimedEvent aEvent) {
  remainingSteps[aEvent] = TimedEvent_Delays_CONST[aEvent]; // set the remaining steps to the start count
  resume();
}

void TimedEventsManagement::deactivateEvent(const TimedEvent aEvent) {
  remainingSteps[aEvent] = 0; // change the remaining steps to zero, that is deactivated
}
