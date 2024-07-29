/*
 *  reflector.ino - IR Photo Reflector sample application for Koov
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

  int val0 = Koov.reflector(KoovInSlow0);
  int val1 = Koov.reflector(KoovInSlow1);
  printf("reflector0 = %d\n", val0);
  printf("reflector1 = %d\n", val1);

  /* sleep 1s */
  sleep(1);

}
