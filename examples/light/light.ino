/*
 *  led.ino - Light Sensor sample application for Koov
 */

#include "KoovControl.h"

/**
 * @brief Initialize Koov.
 */
void setup() {

  Koov.begin();

  /* sleep 1s */
  sleep(1);
}

/**
 * @brief Main loop.
 */
void loop() {
  /* put your main code here, to run repeatedly: */

  int val = Koov.light(KoovInSlow0);
  printf("light = %d\n", val);

  /* sleep 1s */
  sleep(1);

}
