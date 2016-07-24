/*
 * LCDSegment.h
 *
 *  Created on: 23.11.2014
 *      Author: patrick
 */

#ifndef SRC_LCDSEGMENT_H_
#define SRC_LCDSEGMENT_H_

#include <avr/io.h>

enum LCDSegment {
	ls_0 = 0,
	ls_1 = 1,
	ls_2 = 2,
	ls_3 = 3,
	ls_4 = 4,
	ls_5 = 5,
	ls_6 = 6,
	ls_7 = 7,
	ls_8 = 8,
	ls_9 = 9, // all digital numbers have to be equal to their number representation
	ls_F = 10,
	ls_I = 11,
	ls_L = 12,
	ls_Non = 13,
	ls_STATE_COUNT = 14 // this has to be the last, it gives the number of states
};

// Bit-Segment-Assignment
// for left LCD Digit
// ##############
// #     ___    #
// #    | 7 |   #
// #   1|   |2  #
// #    |___|   #
// #    | 5 |   #
// #   6|   |0  #
// #   _|___|   #
// #  |_| 3     #
// #   4        #
// #            #
// ##############
const uint8_t LeftLCDPattern[ls_STATE_COUNT] = {
  0b11001111, // ls_0
  0b00000101, // ls_1
  0b11101100, // ls_2
  0b10101101, // ls_3
  0b00100111, // ls_4
  0b10101011, // ls_5
  0b11101011, // ls_6
  0b10000101, // ls_7
  0b11101111, // ls_8
  0b10101111, // ls_9
  0b11100010, // ls_F
  0b01000010, // ls_I
  0b01001010, // ls_L
  0b00000000 // ls_Non
};
#define LeftLCDDot 0b00010000;

// Bit-Segment-Assignment
// for right LCD Digit
// ##############
// #     ___    #
// #    | 0 |   #
// #   2|   |5  #
// #    |___|   #
// #    | 7 |   #
// #   1|   |6  #
// #   _|___|   #
// #  |_| 3     #
// #   4        #
// #            #
// ##############
const uint8_t RightLCDPattern[ls_STATE_COUNT] = {
  0b01101111, // ls_0
  0b01100000, // ls_1
  0b10101011, // ls_2
  0b11101001, // ls_3
  0b11100100, // ls_4
  0b11001101, // ls_5
  0b11001111, // ls_6
  0b01100001, // ls_7
  0b11101111, // ls_8
  0b11101101, // ls_9
  0b10000111, // ls_F
  0b00000110, // ls_I
  0b00001110, // ls_L
  0b00000000 // ls_Non
};
#define RightLCDDot 0b00010000;

#endif /* SRC_LCDSEGMENT_H_ */
