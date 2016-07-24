/*
 * Keyboard.cpp
 *
 *  Created on: 06.03.2016
 *      Author: patrick
 */

#include "Keyboard.h"

#include <avr/io.h>

#include "hw_definitions.h"
#include "TimedEventsManagement.h"
#include "UntimedEventsManagement.h"

//assume, buttons not pressed at initialization
RGState Keyboard::keyboardState = rg_None;
RGState Keyboard::lastMeasurement = rg_Invalid;
uint8_t Keyboard::remainingSteps = HW_DEBOUNCE_STEPS;

RGState Keyboard::readHardware() {
  return (RGState)(ConvertActiveLowToBitOnMask ^ (Keyboard_BothKeys::getState() >> PortD_RGState_ShiftRight));
}

void Keyboard::invalidate() {
  keyboardState = rg_Invalid;
  setNewRemainingSteps(HW_DEBOUNCE_STEPS);
}

void Keyboard::resetToKeyInterrupt() {
  keyboardState = rg_None;
  remainingSteps = HW_DEBOUNCE_STEPS;
  GICR = GICR_KEYBOARD_ENABLED;
}

void Keyboard::setNewRemainingSteps(const uint8_t aRemainingSteps) {
  remainingSteps = aRemainingSteps;
  TimedEventsManagement::activateEvent(te_sample_buttons);
}

void Keyboard::startSampling() {
  GICR = GICR_KEYBOARD_DISABLED;
  TimedEventsManagement::activateEvent(te_sample_buttons);
}

void Keyboard::sampleButtons() {
  // get a new button measurement
  RGState currentButtons = readHardware();

  // validate against last measurement
  bool unchanged = (currentButtons == lastMeasurement);
  remainingSteps -= unchanged; // true = 1 ; false = 0

  if (remainingSteps == 0) { // some point of planned state transition is reached
    switch (keyboardState) {
    case rg_None:
      keyboardState = currentButtons;
      switch (currentButtons) {
      case rg_None:
        resetToKeyInterrupt();
        break;
      case rg_R:
        setNewRemainingSteps(HW_BUTTON_HOLD_STEPS);
        UntimedEventsManagement::addEvent(ue_Keyboard_Red);
        break;
      case rg_G:
        setNewRemainingSteps(HW_BUTTON_HOLD_STEPS);
        UntimedEventsManagement::addEvent(ue_Keyboard_Green);
        break;
      case rg_Both:
        setNewRemainingSteps(HW_BUTTON_HOLD_STEPS);
        break;
      case rg_Invalid:
        // impossible to occur, just to avoid the compiler warning
        break;
      }
      break;
    case rg_R:
      setNewRemainingSteps(HW_BUTTON_REPEAT_STEPS);
      UntimedEventsManagement::addEvent(ue_Keyboard_Red);
      break;
    case rg_G:
      setNewRemainingSteps(HW_BUTTON_REPEAT_STEPS);
      UntimedEventsManagement::addEvent(ue_Keyboard_Green);
      break;
    case rg_Both:
      UntimedEventsManagement::addEvent(ue_Keyboard_BLong); // both long pressed
      invalidate();
      break;
    case rg_Invalid:
      if (currentButtons == rg_None) {
        resetToKeyInterrupt();
      } else { // retry, should never happen, but for safety
        setNewRemainingSteps(HW_DEBOUNCE_STEPS);
      }
    }
  } else if (unchanged) { // planned steps left -> resample
    TimedEventsManagement::activateEvent(te_sample_buttons);
  } else { // measurement changed
    switch (keyboardState) {
    case rg_None:
      setNewRemainingSteps(HW_DEBOUNCE_STEPS);
      break;
    case rg_R:
    case rg_G:
      invalidate();
      break;
    case rg_Both:
      UntimedEventsManagement::addEvent(ue_Keyboard_BShort); // both short pressed
      invalidate();
      break;
    case rg_Invalid:
      invalidate();
      break;
    }
  }

  // store as new last measurement for next time
  lastMeasurement = currentButtons;
}
