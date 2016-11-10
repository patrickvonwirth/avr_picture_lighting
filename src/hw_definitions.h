/*
 * hw_definitions.h
 *
 *  Created on: 18.02.2016
 *      Author: patrick
 */

#ifndef SRC_HW_DEFINITIONS_H_
#define SRC_HW_DEFINITIONS_H_

#include "avr_lib/avrp/PinOut.h"
#include "avr_lib/avrp/PortIn.h"

// DEFINE PORTS

  // LCD_Display
  typedef avrp::PinOut_PortB<0> LCD_VCC;
  typedef avrp::PinOut_PortB<3> LCD_Comm; // OC2Pin
  typedef avrp::PinOut_PortD<7> LCD_LeftSDIPin;
  typedef avrp::PinOut_PortB<7> LCD_RightSDIPin;
  typedef avrp::PinOut_PortD<6> LCD_ShiftPin;
  typedef avrp::PinOut_PortD<5> LCD_StoragePin;
  // LED-PWM_Output
  typedef avrp::PinOut_PortB<1> LED_PWM; // OC1APin
  // Keyboard_Input
  typedef avrp::PortIn_PortD<0b00001100> Keyboard_BothKeys;
  #define PortD_RGState_ShiftRight 2
  #define ConvertActiveLowToBitOnMask 0b00000011

// DEFINE TWI PROPERTIES
  #define TWI_ADDRESS 0b00001010 // define 7bit TWI address = 10
  #define TWI_GENERALCALL_ENABLE true // activate general call reaction
  #define TWI_BUFFER_SIZE 2 // TWI data buffer(transmit/receive) size = 2 byte

// DEFINE CONTROLLER SFR (= Special Function Register) and related constants

  // CPU-Clock: 1 MHz

  // Sleep and External Interrupt management
  #define MCUCR_SYSTEM_FULLACTIVE  0b00000000 // sleep disabled                   | ext interrupts set to low-level LEVEL interrupt, managed by the GICR enable flags
  #define MCUCR_SYSTEM_ACTIVETIMER 0b10000000 // sleep enabled to IDLE mode       | ext interrupts set to low-level LEVEL interrupt, managed by the GICR enable flags
  #define MCUCR_SYSTEM_POWERDOWN   0b10100000 // sleep enabled to POWER DOWN mode | ext interrupts set to low-level LEVEL interrupt to be able to wake up from POWER DOWN

  // I/O-Pins ( 1 = OUTPUT | 0 = Input )
  #define DDRB_HWDEF 0b10001011 // [LCD_RightSDI | …3… | LCD_Comm | … | LED_PWM | LCD_VCC]
  //default: PORTB = 0b00000000 // initialize as Tri-State or Pegel-Low
  #define DDRD_HWDEF 0b11100000 // [LCD_LeftSDI | LCD_ShiftPin | LCD_StoragePin | … | Keyboard_GreenKey | Keyboard_RedKey | …2… ]
  #define PORTD_HWDEF 0b00001100 // initialize Out-Pins as Pegel-Low, activate internal Pull-Up resistors of In-Pins and set all unused pins as tri-stated

  // I-Pins interrupts
  // external interrupt types defined in the MCUCR-Register defined above
  #define GICR_KEYBOARD_ENABLED  0b11000000 // both external pin interrupts active
  #define GICR_KEYBOARD_DISABLED 0b00000000 // both external pin interrupts disabled

  // Timer/Counter 0
  #define TCCR0_EVENTS_UP 0b00000011 // Timer0 active, used to process a time step (interrupt) every ~16.66 ms (~60Hz)
    // - Prescaler = 64
  #define TCCR0_EVENTS_DOWN 0b00000000 // Timer0 inactive to reduce power consumption
    // - Prescaler = Non -> Timer stopped
  #define HW_DEBOUNCE_STEPS 3      //  3 steps ~ 50ms  to debounce the hardware buttons
  #define HW_BUTTON_HOLD_STEPS 60  // 60 steps ~  1s   as button hold threshold
  #define HW_BUTTON_REPEAT_STEPS 6 //  6 steps ~ 100ms as button repeat threshold, when continuously pressed

  // Timer/Counter 1
  #define TCCR1A_PWM_Inactive 0b00000010
  #define TCCR1B_PWM_Inactive 0b00011000
    // Timer 1 inactive, no clock, fast PWM-mode with TOP=ICR1, OC1A/B pins normal port operation
  #define TCCR1A_PWM_Active   0b10000010
  #define TCCR1B_PWM_Active   0b00011001
    // Timer 1 active, no prescaler, fast PWM-mode with TOP=ICR1, OC1A pin at clear on compare match, OC1B pin normal port operation
  // quadratic formula for percent -> pwm calculation:
  // x -> (x^2 + x)/2
  // max result(x=100) = 5050
  #define ICR1_HWDEF 5050 // set TOP to max value

  // Timer/Counter 2
  #define TCCR2_LCD_UP 0b01110011 // Timer2 active, used to generate ~60Hz equal-length PWM pulse signal for LCD_Comm
    // - Prescaler = 32
    // - Compare-Match-Operation = Set on Up, clear on Down
    // - Timer-Mode = PhaseCorrect
  #define TCCR2_LCD_DOWN 0b01000000 // Timer2 inactive to reduce power consumption
    // - Prescaler = Non -> Timer stopped
    // - Compare-Math-Operation = Normal Port Operation
    // - Timer-Mode = PhaseCorrect (irrelevant)
  #define OCR2_HWDEF 0b10000000 // compare-match at 128 (the middle) to get equal length high/low phases

  // Timer0/1/2 interrupts
  #define TIMSK_HWDEF 0b00000001 // Timer0 overflow interrupt active, nothing else

  // Untimed Events Queue
  #define UT_EVENTSQUEUE_SIZEBITS 3 // use 3 bits -> queue size = 7 elements

// DEFINE initialization routine
void initialize_controller();

#endif /* SRC_HW_DEFINITIONS_H_ */
