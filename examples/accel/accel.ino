/*
 *  accel.ino - Accelerometer sample application for Koov
 */

#include "KoovControl.h"

/**
 * @brief Initialize Koov.
 */
void setup() {

  Serial.begin(115200);

  Koov.begin();

  /* sleep 1s */
  sleep(1);
}

/**
 * @brief Main loop.
 */
void loop() {

  int x, y, z;

  x = Koov.accelX();
  y = Koov.accelY();
  z = Koov.accelZ();

  Serial.print("x=");
  Serial.print(x);
  Serial.print(", y=");
  Serial.print(y);
  Serial.print(", z=");
  Serial.print(z);
  Serial.println();

  sleep(1);

}
