/*
 * events.h
 *
 *  Created on: 02.03.2016
 *      Author: patrick
 */

#ifndef SRC_EVENTS_H_
#define SRC_EVENTS_H_

#include "GUI.h"
#include "Keyboard.h"
#include "System.h"

// define the typ event as function without in- and output
typedef void(*event)();

enum TimedEvent { // note, that the order is important
  te_sample_buttons = 0,
  te_flicker_tick   = 1,
  // insert new states here
  te_STATE_COUNT // this has to be the last, it gives the number of states
};
typedef uint8_t TimedEvent_uint8_Array[te_STATE_COUNT];
#define TimedEvent_Startup_Delay_Initialization {0, 0} // event delays at start up initialization: zero equals inactive
const TimedEvent_uint8_Array TimedEvent_Delays_CONST = {
  1, // sample_buttons = 16.66 ms
  2  // flicker_tick   = 33.33 ms
};
#define flicker_tick_random_mask 0b00000111 // use random numbers between 0 and 7
const event TimedEvent_Actions[te_STATE_COUNT] = {
  Keyboard::sampleButtons,
  System::flicker
};
typedef uint8_t TimedEvent_BitArray_t; // Number of Bits of this type have to be at least te_STATE_COUNT
#define TimedEvent_Startup_Active_Initialization 0b00000000; // bit array representing no active events at startup

enum UntimedEvent { // note, that the order defines the actions defined below
  ue_Keyboard_Green  = 0,
  ue_Keyboard_Red    = 1,
  ue_Keyboard_BShort = 2,
  ue_Keyboard_BLong  = 3,
  // insert new states here
  ue_STATE_COUNT // this has to be the last, it gives the number of states
};
const event UntimedEvent_Actions[ue_STATE_COUNT] = {
  GUI::ControlUp,
  GUI::ControlDown,
  GUI::ControlOK,
  GUI::ControlSafe
};

#endif /* SRC_EVENTS_H_ */
