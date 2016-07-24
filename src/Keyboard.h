/*
 * Keyboard.h
 *
 *  Created on: 06.03.2016
 *      Author: patrick
 */

#ifndef SRC_KEYBOARD_H_
#define SRC_KEYBOARD_H_

#include <avr/io.h>

enum RGState { // these values are directly derived from the PIND-Port shifting the bits to the right end
  rg_None = 0, //////////////////////////////////////////////////////
  rg_R    = 1, //  DO NOT  //  these numbers are chosen to equal   //
  rg_G    = 2, //  CHANGE  //  the shifted and inverted Port-Bits  //
  rg_Both = 3, //////////////////////////////////////////////////////
  rg_Invalid = 4
};

class Keyboard {
private:
  static RGState keyboardState;   // the state of the keyboard itself
  static RGState lastMeasurement; // the last button measurement
  static uint8_t remainingSteps;  // remaining steps for events [used by all states, but different]

  static RGState readHardware();
  static void invalidate();
  static void resetToKeyInterrupt();
  static void setNewRemainingSteps(const uint8_t aRemainingSteps);
public:
  static void startSampling();
  static void sampleButtons();
};

#endif /* SRC_KEYBOARD_H_ */
