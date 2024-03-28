/***************************************************************************
 *
 * KOOV Control Class Header
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#ifndef _KOOV_CONTROL_H_
#define _KOOV_CONTROL_H_

#include <Arduino.h>
#include <Servo.h>
#include <MMA8653.h>

/****************************************************************************
 * definitions
 ****************************************************************************/
#define PWM0_PIN PIN_D03
#define PWM1_PIN PIN_D05
#define PWM2_PIN PIN_D06
#define PWM3_PIN PIN_D09

enum KoovServo {
  KoovServo0 = PWM0_PIN,
  KoovServo1 = PWM1_PIN,
  KoovServo2 = PWM2_PIN,
  KoovServo3 = PWM3_PIN
};

enum KoovOut {
  KoovOut0 = PIN_D00,
  KoovOut1 = PIN_D01,
  KoovOut2 = PIN_D02,
  KoovOut3 = PIN_D04,
  KoovOut4 = PIN_D07,
  KoovOut5 = PIN_D08
};

enum KoovInSlow {
  KoovInSlow0 = A0,
  KoovInSlow1 = A1,
  KoovInSlow2 = A2,
  KoovInSlow3 = A3
};

enum KoovInHigh {
  KoovInHigh0 = A4,
  KoovInHigh1 = A5
};

enum KoovIn {
  KoovIn0 = KoovInSlow0,
  KoovIn1 = KoovInSlow1,
  KoovIn2 = KoovInSlow2,
  KoovIn3 = KoovInSlow3,
  KoovIn4 = KoovInHigh0,
  KoovIn5 = KoovInHigh1

};

enum KoovMotor {
  KoovMotor0,
  KoovMotor1
};


/****************************************************************************
 * Koov Motor Class
 ****************************************************************************/
class KoovMotorClass
{
public:
  KoovMotorClass(uint8_t in0,uint8_t in1):pin0(in0),pin1(in1){};

  void begin();

  void set(uint8_t);
  void front();
  void back();
  void front(uint8_t);
  void back(uint8_t);
  void stop();
  void slow();

private:
  uint8_t pin0;
  uint8_t pin1;
  uint8_t speed;
};

/****************************************************************************
 * Koov Class
 ****************************************************************************/
class KoovClass
{
public:

  void begin();
  void end();

  bool servo(KoovServo,int);
  void led(KoovOut,bool);

  bool buzzerOn(KoovOut,int);
  void buzzerOff(KoovOut);

  bool motorSpeed(KoovMotor,int);
  bool motorStart(KoovMotor,bool);
  bool motorStart(KoovMotor,bool,int);
  bool motorStop(KoovMotor,bool);

  int  light(KoovIn);
  int  light(KoovInSlow);
  int  reflector(KoovIn);
  int  reflector(KoovInSlow);
  int  reflector(KoovInHigh);

  int  accelX();
  int  accelY();
  int  accelZ();

private:

  Servo servo0;
  Servo servo1;
  Servo servo2;
  Servo servo3;

  KoovMotorClass* motor0;
  KoovMotorClass* motor1;
  MMA8653 accel0;
	
  int  conv5v(int);

};

extern class KoovClass Koov;

#endif /*_KOOV_CONTROL_H_*/
