/*
 * konfigurations.h
 *
 *  Created on: 02.07.2016
 *      Author: patrick
 */

#ifndef SRC_CONFIGURATIONS_H_
#define SRC_CONFIGURATIONS_H_

#include <avr/io.h>

enum SystemConfiguration { // note, that the order is important
  sk_brightness = 0,
  sk_variance = 1,
  // insert new states here
  sk_STATE_COUNT // this has to be the last, it gives the number of states
};
typedef uint8_t SystemConfiguration_Array[sk_STATE_COUNT];
#define SystemConfiguration_Array_ZEROS {0, 0} // define a zero vector for initialization

const uint8_t SystemConfiguration_MinValues[sk_STATE_COUNT] = {
  0,
  0
};

const uint8_t SystemConfiguration_MaxValues[sk_STATE_COUNT] = {
  100,
  38  // brightness (=100) + 4* variance (=38) <= 255 | 4 = number of added random numbers
};

// initial EEPROM-VALUES
#define SystemConfiguration_Array_EEPROM_INITIAL_VALUES { \
  30, \
  0   \
}

#endif /* SRC_CONFIGURATIONS_H_ */
