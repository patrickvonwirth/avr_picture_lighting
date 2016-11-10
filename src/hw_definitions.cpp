/*
 * hw_definitions.cpp
 *
 *  Created on: 24.02.2016
 *      Author: patrick
 */

#include "hw_definitions.h"

#include <avr/io.h>
#include <avr/interrupt.h>

//#include "avr_lib/avrp/TWISlave.h"

void initialize_controller(){

// Sleep and external interrupts
  MCUCR = MCUCR_SYSTEM_FULLACTIVE;

// I/O-Pins
  DDRB = DDRB_HWDEF;
  //default: PORTB = 0b00000000;
  DDRD = DDRD_HWDEF;
  PORTD = PORTD_HWDEF;

// External Interrupts enabled
  GICR = GICR_KEYBOARD_ENABLED;

// Timer/Counter 0
  TCCR0 = TCCR0_EVENTS_DOWN;

// Timer/Counter 1
  TCCR1A = TCCR1A_PWM_Inactive;
  TCCR1B = TCCR1B_PWM_Inactive;
  ICR1 = ICR1_HWDEF;

// Timer/Counter 2
  TCCR2 = TCCR2_LCD_DOWN;
  OCR2 = OCR2_HWDEF;

// Timer Interrupts
  TIMSK = TIMSK_HWDEF;

// Enable global interrupt system later in the main program right before start
}
