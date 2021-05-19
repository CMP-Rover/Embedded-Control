#include "PID_Control.h"
#define WHEEL_R 6
/*
  PID Algorithm it automatically applies an accurate and responsive correction to a control function
  Is a control loop mechanism employing feedback
*/

/*
   This Fucntion is used to set the motor direction and speed
   it takes Parameters (rotation direction , PWM Speed , PWM Pin ,in1 pin , in2 Pin)
*/

MotorSheild:: MotorSheild(int pwm , int in1 , int in2)
{
  PWM = pwm;
  IN1 = in1;
  IN2 = in2;
   

}
void  MotorSheild:: setPIDParameters(double Kpp , double Kii , double Kdd)
{
  Kp = Kpp;
  Ki = Kii;
  Kd = Kdd;
}
void
MotorSheild:: setMotor(int dir , int pwmVal)
{
  analogWrite(PWM, pwmVal);            //Setting the Speed
  if (dir == 1)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (dir == -1)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
}
double
MotorSheild:: computePID(double inp)
{

  currentTime = millis();                              //get the current time
  elapsedTime = (double) (currentTime - previousTime); //Calculate ElapsedTime
  error = setPoint - inp;                              //Calculate the error by get the difference between target and measured value
  cumError += error * elapsedTime;                     // compute integral
  rateError = (error - lastError) / elapsedTime;       // compute derivative
  double out = Kp * error + Ki * cumError + Kd * rateError;
  lastError = error;                                   //Remember Current error
  previousTime = currentTime;                          //Remember Current time
  return out;                                          //This signal tells us the direction and speed to turn the motor
}
/*
  The signal that comes from PID Algorithm we need to convert it to speed and direction
*/
void
MotorSheild::convertSignal(float outSignal)
{
  float pwr =  fabs(outSignal);
  if (pwr > 255)
    pwr = 255;
  int dir = 1;
  if (outSignal < 0)
    dir = -1;
  setMotor(dir , pwr);
}
//Get the position of the motor


void
MotorSheild::setPIDTarget(double target)
{
  setPoint = target;
}

double
MotorSheild:: getCurrentPosition()
{
  return pos;
}


void
MotorSheild:: setMotorEncoders(int encoder_a , int encoder_b)
{
  ENCODER_A = encoder_a;
  ENCODER_B = encoder_b;
}


void
MotorSheild:: setMotorAngularVelocity(float av)
{

  //int v = fabs(av * WHEEL_R);
  float aav = fabs(av);
  int v = map(aav, 0, 84, 0, 255);
  int dir;
  if (av > 0)
  {
    dir = 1;
  } else
  {
    dir = -1;
  }
  if (v > 255)   v = 255;
  Serial.print("Velocity: ");
  Serial.println(v);
  setMotor(dir, v);

}
void MotorSheild::readEncoder()
{
  int b = digitalRead(ENCODER_B);
  if (b > 0)
  {
    pos++;

  }
  else
  {
    pos--;

  }

}
