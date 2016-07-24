/*
 * LED.h
 *
 *  Created on: 12.06.2016
 *      Author: patrick
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_

#include <avr/io.h>

class LED {
private:
  static void startPWM();
  static void stopPWM();
  static uint16_t percentToPWM(const uint8_t aPercent);
public:
  static void setPWM(const uint8_t aPercent);
};

#endif /* SRC_LED_H_ */
