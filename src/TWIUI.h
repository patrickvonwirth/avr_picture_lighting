/*
 * TWIUI.h
 *
 *  Created on: 09.11.2016
 *      Author: patrick
 */

#ifndef SRC_TWIUI_H_
#define SRC_TWIUI_H_

class TWI_UI {
private:
  static void onDataReceive();
  static void onDataRequest();
public:
  static void initialize();
  static void onInterrupt();
};

#endif /* SRC_TWIUI_H_ */
