/*
 *  motor.ino - Motor sample application for Koov
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

  Koov.motorSpeed(KoovMotor0,100);
  Koov.motorStart(KoovMotor0,true);

  /* sleep 2s */
  sleep(2);

  Koov.motorStop(KoovMotor0,true);

  /* sleep 1s */
  sleep(1);

  Koov.motorSpeed(KoovMotor0,50);
  Koov.motorStart(KoovMotor0,false);

  /* sleep 2s */
  sleep(2);

  Koov.motorStop(KoovMotor0,true);

  /* sleep 1s */
  sleep(1);

  Koov.motorSpeed(KoovMotor0,25);
  Koov.motorStart(KoovMotor0,true);

  /* sleep 2s */
  sleep(2);

  Koov.motorStop(KoovMotor0,false);

  /* sleep 1s */
  sleep(1);

}
