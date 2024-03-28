/*
 *  servo.ino - Servo sample application for Koov
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

  /* Set the servo motor angle to 90 degrees */
  Koov.servo(KoovServo0,90);

  /* sleep 1s */
  sleep(1);

  /* Set the servo motor angle to 0 degrees */
  Koov.servo(KoovServo0,0);

  /* sleep 1s */
  sleep(1);

  /* Set the servo motor angle to 180 degrees */
  Koov.servo(KoovServo0,180);

  /* sleep 1s */
  sleep(1);
}
