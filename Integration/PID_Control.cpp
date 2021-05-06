#include "PID_Control.h"

/*
 PID Algorithm it automatically applies an accurate and responsive correction to a control function
 Is a control loop mechanism employing feedback
*/

/*
 * This Fucntion is used to set the motor direction and speed
 * it takes Parameters (rotation direction , PWM Speed , PWM Pin ,in1 pin , in2 Pin)
 */

double Kp;         // is the proportional gain, a tuning parameter
double Ki;       //is the integral gain, a tuning parameter
double Kd;      //is the derivative gain, a tuning parameter,
                     //Tuning a control loop is the adjustment of its control parameters ,
                     //to the optimum values for the desired control response
unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output;
double setPoint;        //Target Value;
double cumError, rateError;
double pos;
int ENCODER_A ;
int  ENCODER_B ;
void setPIDParameters(double Kpp , double Kii , double Kdd)
{
  Kp = Kpp;
  Ki = Kii;
  Kd = Kdd;
}
void setMotor(int dir , int pwmVal , int pwm , int in1 ,int in2)
{
  analogWrite(pwm,pwmVal);             //Setting the Speed
  if(dir==1)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if (dir == -1)
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    }
    else
    {
      digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
      }
  }
double computePID(double inp)
{
  
  currentTime = millis();                              //get the current time
  elapsedTime = (double) (currentTime-previousTime);   //Calculate ElapsedTime
  error = setPoint - inp;                              //Calculate the error by get the difference between target and measured value
  cumError += error * elapsedTime;                     // compute integral
  rateError = (error - lastError)/elapsedTime;         // compute derivative
  double out = Kp*error + Ki*cumError + Kd*rateError;
  lastError = error;                                   //Remember Current error
  previousTime = currentTime;                          //Remember Current time
  return out;                                          //This signal tells us the direction and speed to turn the motor
}
/*
* The signal that comes from PID Algorithm we need to convert it to speed and direction
*/
void convertSignal(float outSignal , int PWM , int IN1 , int IN2)
{
  float pwr =  fabs(outSignal);
  if(pwr > 255)
    pwr =255;
  int dir = 1;
  if(outSignal < 0)
    dir = -1;
    setMotor(dir , pwr ,PWM,IN1,IN2);
  }
  //Get the position of the motor
void readEncoder()
{
  int b = digitalRead(ENCODER_B);
  if(b >0)
  {
    pos++;
    
    }
    else
    {
      pos--;
      
    }
   
}

void setPIDTarget(double target)
{
  setPoint = target;
  }

  double getCurrentPosition()
  {
    return pos;
    }


  void setMotorEncoders(int encoder_a ,int encoder_b)
  {
    ENCODER_A = encoder_a;
    ENCODER_B = encoder_b; 
    }
