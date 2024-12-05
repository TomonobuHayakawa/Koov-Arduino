/****************************************************************************
 *
 * KOOV Control Class
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include "KoovControl.h"


/****************************************************************************
 * This class for Spr-Koov (Arduino Shield for Koov) version 1.0
  ****************************************************************************/
#if (SPR_KOOV_VER == 1)
#include <SoftPWM.h>
/****************************************************************************
 * Koov Motor Class methods
 ****************************************************************************/
void KoovMotorClass::begin()
{
  speed = 255;

  SoftPWMSet(pin0, 0);
  SoftPWMSet(pin1, 0);
}

void KoovMotorClass::set(uint8_t sp)
{
  speed = sp;
}

void KoovMotorClass::front(uint8_t sp)
{
  speed = sp;
  front();
}

void KoovMotorClass::back(uint8_t sp)
{
  speed = sp;
  back();
}

void KoovMotorClass::front()
{
  SoftPWMSet(pin0, speed);
  SoftPWMSet(pin1, 0);
}

void KoovMotorClass::back()
{
  SoftPWMSet(pin0, 0);
  SoftPWMSet(pin1, speed);
}

void KoovMotorClass::stop()
{
  SoftPWMSet(pin0, 255);
  SoftPWMSet(pin1, 255);
}

void KoovMotorClass::slow()
{
  SoftPWMSet(pin0, 0);
  SoftPWMSet(pin1, 0);
}

/****************************************************************************
 * This class for Spr-Koov (Arduino Shield for Koov) leatest version
  ****************************************************************************/
#else // (SPR_KOOV_VER == 2)
void KoovMotorClass::begin()
{
  speed = 255;

  pinMode(pin0, OUTPUT);    // sets the digital pin as output for enable on motor0.
  pinMode(pin1, OUTPUT);    // sets the digital pin as output for phase on motor0.
  digitalWrite(pin0, LOW);
  digitalWrite(pin1, LOW);

}

void KoovMotorClass::set(uint8_t sp)
{
  speed = sp;
}

void KoovMotorClass::front(uint8_t sp)
{
  speed = sp;
  front();
}

void KoovMotorClass::back(uint8_t sp)
{
  speed = sp;
  back();
}

void KoovMotorClass::front()
{
  digitalWrite(pin1, HIGH);
  analogWrite(pin0, speed);
}

void KoovMotorClass::back()
{
  digitalWrite(pin1, LOW);
  analogWrite(pin0, speed);
}

void KoovMotorClass::stop()
{
  analogWrite(pin0, 0);
  analogWrite(pin1, 0);
}

#endif


/****************************************************************************
 * begin on Koov Class
 ****************************************************************************/
void KoovClass::begin()
{

  servo0.attach(PWM0_PIN);
  servo1.attach(PWM1_PIN);
#if (SPR_KOOV_VER == 1)
  servo2.attach(PWM2_PIN);
  servo3.attach(PWM3_PIN);
#endif

  pinMode(KoovOut0, OUTPUT);
  pinMode(KoovOut1, OUTPUT);
  pinMode(KoovOut2, OUTPUT);
  pinMode(KoovOut3, OUTPUT);
  digitalWrite(KoovOut0, LOW);
  digitalWrite(KoovOut1, LOW);
  digitalWrite(KoovOut2, LOW);
  digitalWrite(KoovOut3, LOW);

#if (SPR_KOOV_VER == 1)
  pinMode(KoovOut4, OUTPUT);
  pinMode(KoovOut5, OUTPUT);
  digitalWrite(KoovOut4, LOW);
  digitalWrite(KoovOut5, LOW);
#endif

#if (SPR_KOOV_VER == 1)
  SoftPWMBegin();
  motor0 = new KoovMotorClass(PIN_D10,PIN_D11);
  motor1 = new KoovMotorClass(PIN_D12,PIN_D13);
#else // (SPR_KOOV_VER == 2)
  pinMode(11, OUTPUT);    // sets the digital pin 11 as output for driver mode.
  digitalWrite(11, HIGH);  // set p/e mode
  motor0 = new KoovMotorClass(PIN_D09,PIN_D13);
  motor1 = new KoovMotorClass(PIN_D06,PIN_D12);
#endif

  motor0->begin();
  motor1->begin();

  Wire.begin();
  Wire.setClock(400000);

  accel0.init(MMA8653_2G_RANGE, MMA8653_8BIT_RES, MMA8653_ODR_50);
  accel0.setMODS(MMA8653_MODS_LOW_NOISE_LOW_POWER);
  accel0.begin();

}

/****************************************************************************
 * end on Koov Class
 ****************************************************************************/
void KoovClass::end()
{
  delete motor0;
  delete motor1;
}

/****************************************************************************
 * Servo on Koov Class
 ****************************************************************************/
bool KoovClass::servo(KoovServo no,int deg)
{
  if((deg<0) && (deg>180)) return false;

  switch(no){
    case KoovServo0:
      servo0.write(deg);
      break;
    case KoovServo1:
      servo1.write(deg);
      break;
#if (SPR_KOOV_VER == 1)
    case KoovServo2:
      servo2.write(deg);
      break;
    case KoovServo3:
      servo3.write(deg);
      break;
#endif
    default:
      return false;
  }

  return true;

}

/****************************************************************************
 * LED on Koov Class
 ****************************************************************************/
void KoovClass::led(KoovOut no, bool val)
{
  val ? digitalWrite(no, HIGH) : digitalWrite(no, LOW);
}

/****************************************************************************
 * DC Motor on Koov Class
 ****************************************************************************/
bool KoovClass::motorSpeed(KoovMotor no, int speed)
{
  if((speed<0) && (speed>100)) return false;

  switch(no){
    case KoovMotor0:
      motor0->set(speed * 255 / 100);
      break;
    case KoovMotor1:
      motor1->set(speed * 255 / 100);
      break;
    default:
      return false;
  }

  return true;

}

bool KoovClass::motorStart(KoovMotor no, bool dist)
{

  switch(no){
    case KoovMotor0:
      dist ? motor0->front() : motor0->back();
      break;
    case KoovMotor1:
      dist ? motor1->front() : motor1->back();
      break;
    default:
      return false;
  }

  return true;

}

bool KoovClass::motorStart(KoovMotor no, bool dist, int speed)
{
  if((speed<0) && (speed>100)) return false;

  switch(no){
    case KoovMotor0:
      dist ? motor0->front(speed) : motor0->back(speed);
      break;
    case KoovMotor1:
      dist ? motor1->front(speed) : motor1->back(speed);
      break;
    default:
      return false;
  }

  return true;

}

bool KoovClass::motorStop(KoovMotor no, bool slow)
{

#if (SPR_KOOV_VER != 1)
    (void) slow;
#endif

switch(no){
    case KoovMotor0:
#if (SPR_KOOV_VER == 1)
      slow ? motor0->slow() : motor0->stop();
#else // (SPR_KOOV_VER == 2)
      motor0->stop();
#endif
      break;
    case KoovMotor1:
#if (SPR_KOOV_VER == 1)
      slow ? motor1->slow() : motor1->stop();
#else // (SPR_KOOV_VER == 2)
      motor1->stop();
#endif
      break;
    default:
      return false;
  }

  return true;

}


/****************************************************************************
 * Light Sensor on Koov Class
 ****************************************************************************/
int KoovClass::light(KoovIn no)
{
  return  conv5v((int)no);
}

int KoovClass::light(KoovInSlow no)
{
  return  conv5v((int)no);
}

/****************************************************************************
 * IR Photo Reflector on Koov Class
 ****************************************************************************/
int KoovClass::reflector(KoovIn no)
{
  return  conv5v((int)no);
}

int KoovClass::reflector(KoovInSlow no)
{
  return  conv5v((int)no);
}

int KoovClass::reflector(KoovInHigh no)
{
  return  conv5v((int)no);
}

/****************************************************************************
 * Accelerometor on Koov Class
 ****************************************************************************/
int KoovClass::accelX()
{
  int16_t x, y, z;
  accel0.readSensor(&x, &y, &z);
  return x * 100 / 128;
}

int KoovClass::accelY()
{
  int16_t x, y, z;
  accel0.readSensor(&x, &y, &z);
  return y * 100 / 128;
}

int KoovClass::accelZ()
{
  int16_t x, y, z;
  accel0.readSensor(&x, &y, &z);
  return z * 100 / 128;
}


/****************************************************************************
 * Private method on Koov Class
 ****************************************************************************/

int KoovClass::conv5v(int no)
{
  return  analogRead(no) * 50 / 33;
}


class KoovClass Koov;

