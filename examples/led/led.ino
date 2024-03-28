/*
 *  led.ino - LED sample application for Koov
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

  Koov.led(KoovOut0,true);

  /* sleep 1s */
  sleep(1);

  Koov.led(KoovOut0,false);

  /* sleep 1s */
  sleep(1);

}
