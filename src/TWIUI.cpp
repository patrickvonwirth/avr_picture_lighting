/*
 * TWIUI.cpp
 *
 *  Created on: 09.11.2016
 *      Author: patrick
 */

#include "TWIUI.h"

#include "hw_definitions.h"
#include "avr_lib/avrp/TWISlave.h"
#include "UntimedEventsManagement.h"

typedef avrp::TWISlave<TWI_BUFFER_SIZE,TWI_UI::onDataReceive, TWI_UI::onDataRequest> _TWI_CONNECTOR;

void TWI_UI::onDataReceive() {
  if (_TWI_CONNECTOR::data_size == 1) { // a system event has been received
    if (_TWI_CONNECTOR::data[0] < ue_STATE_COUNT) { // received event is valid
      UntimedEventsManagement::addEvent(UntimedEvent(_TWI_CONNECTOR::data[0]));
    }
  }
}

void TWI_UI::onDataRequest() {
  //TODO: implement
}

void TWI_UI::initialize() {
  _TWI_CONNECTOR::start(TWI_ADDRESS, TWI_GENERALCALL_ENABLE);
}

void TWI_UI::onInterrupt() {
  _TWI_CONNECTOR::onInterrupt();
}
