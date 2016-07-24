/*
 * LCD.h
 *
 *  Created on: 18.02.2016
 *      Author: patrick
 */

#ifndef SRC_LCD_H_
#define SRC_LCD_H_

#include <avr/io.h>

#include "LCDSegment.h"

class LCD {
private:
  static uint8_t getLeftBitPattern(const LCDSegment a_Segment, const bool a_Dot);
  static uint8_t getRightBitPattern(const LCDSegment a_Segment, const bool a_Dot);
  static void activate();
  static void deactivate();
public:
  static void clear();
  static void setLCD(const LCDSegment a_LeftSegment, const bool a_LeftDot, const LCDSegment a_RightSegment, const bool a_RightDot);
  static void setDecimalNumber(const uint8_t a_number, const bool a_LeftDot, const bool a_RightDot);
};

#endif /* SRC_LCD_H_ */
