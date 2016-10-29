/*
 * System.h
 *
 *  Created on: 02.07.2016
 *      Author: patrick
 */

#ifndef SRC_SYSTEM_H_
#define SRC_SYSTEM_H_

#include <avr/eeprom.h>

#include "configurations.h"

class System {
private:
  static SystemConfiguration_Array values;
  static SystemConfiguration_Array EEMEM initialValues; // EEPROM Variables
  static uint8_t nextFlicker; // remaining ticks until next flicker
  static uint8_t rand_shift;
  static uint8_t rand_minimalBitMask;
  static uint8_t rand_missedRange;
  static uint8_t validate(const SystemConfiguration aSystemKonfiguration, const uint8_t aValue);
  static void initializeRand();
  static uint8_t rangedRand();
  static void updateLEDOutput();
public:
  static void initialize();
  static void flicker();
  static uint8_t getKonfiguration(const SystemConfiguration aSystemKonfiguration);
  static void setKonfiguration(const SystemConfiguration aSystemKonfiguration, const uint8_t aNewValue);
  static uint8_t getInitValue(const SystemConfiguration aSystemKonfiguration);
  static void setInitValue(const SystemConfiguration aSystemKonfiguration, const uint8_t aNewValue);
};

#endif /* SRC_SYSTEM_H_ */
