/*
 * LCD.cpp
 *
 *  Created on: 18.02.2016
 *      Author: patrick
 */

#include "LCD.h"

#include <avr/io.h>

#include "hw_definitions.h"
#include "PowerManagement.h"

uint8_t LCD::getLeftBitPattern(const LCDSegment a_Segment, const bool a_Dot){
  uint8_t result = LeftLCDPattern[a_Segment];
  // set the Dot
  if (a_Dot) {
    result |= LeftLCDDot;
  }
  return result;
}

uint8_t LCD::getRightBitPattern(const LCDSegment a_Segment, const bool a_Dot){
  uint8_t result = RightLCDPattern[a_Segment];
  // set the Dot
  if (a_Dot) {
    result |= RightLCDDot;
  }
  return result;
}

void LCD::activate(){
  PowerManagement::registerActiveTimer(hwt_ExternalDisplayDC);
  LCD_VCC::setActive(true);
  TCCR2 = TCCR2_LCD_UP;
}

void LCD::deactivate(){
  TCCR2 = TCCR2_LCD_DOWN;
  LCD_VCC::setActive(false);
  PowerManagement::releaseStoppedTimer(hwt_ExternalDisplayDC);
}

void LCD::clear(){
  setLCD(ls_Non, false, ls_Non, false);
}

void LCD::setLCD(const LCDSegment a_LeftSegment, const  bool a_LeftDot, const LCDSegment a_RightSegment, const bool a_RightDot){
  activate();
  uint8_t leftBits = getLeftBitPattern(a_LeftSegment, a_LeftDot);
  uint8_t rightBits = getRightBitPattern(a_RightSegment, a_RightDot);
  for (uint8_t mask = 1; mask > 0; mask = mask<<1) {
    // set inputs
    LCD_LeftSDIPin::setActive((leftBits & mask) != 0);
    LCD_RightSDIPin::setActive((rightBits & mask) != 0);
	// shift
    LCD_ShiftPin::pulse();
  }
  // clear inputs
  LCD_LeftSDIPin::setActive(false);
  LCD_RightSDIPin::setActive(false);
  // store
  LCD_StoragePin::pulse();
  // auto switch off if nothing shown, BUT do that after the display has been cleared
  if ((leftBits | rightBits) == 0) {
	  deactivate();
  }
}

void LCD::setDecimalNumber(const uint8_t a_number, const bool a_LeftDot, const bool a_RightDot){
  if (a_number >= 100) { // number too big to be displayed
    setLCD(ls_F, false, ls_F, false);
  } else {
    LCDSegment highdigit = (LCDSegment)(a_number / 10);
    LCDSegment lowdigit = (LCDSegment)(a_number % 10);
    if (highdigit == ls_0) {
      highdigit = ls_Non;
    }
    setLCD(highdigit, a_LeftDot, lowdigit, a_RightDot);
  }
}
