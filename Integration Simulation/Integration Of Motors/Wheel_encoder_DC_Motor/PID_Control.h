#pragma once
#include <Arduino.h>
class MotorSheild
{
  public:
  

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
int PWM,IN1,IN2;
/// setPIDParameters
///
/// This function is used to set PID alorithm parameters used to control PID algorithm accuracy
/// @param Kp is the proportional gain, a tuning parameter
/// @param Ki is the integral gain, a tuning parameter
/// @param Kd is the derivative gain, a tuning parameter,
/// @note if you want to set only one of them make the others equal to zero
void setPIDParameters  ( double Kp , double Ki , double Kd);
/// setPIDTarget
///
/// This function takes the target that you want your motor reach 
/// and the algorithm tries to reach it and minimize the error in position based on passed parameters to setPIDParameters()
void setPIDTarget(double target);
/// Controlling the motor
///
/// This function controlls the motor speed and direction based on passed parameters
/// @param dir is the direction of rotation 1 or -1 for CW or CCW based on motor wiring and 0 stop rotating
/// @param pwmVal is the rotating speed and it range from 0  (0v) - 255 (5V)  
/// @param PWM is the Pin number that motor driver PWM input connectecd to 
/// @param in1 is the Pin number that motor driver input1 connectecd to 
/// @param in2 is the Pin number that motor driver input2 connectecd to 
void setMotor(int dir , int pwmVal);
/// Running PID Algorithm
///
/// This function is responsible for calculating the **Control Variable**u(t) of PID algorithm based on current position of the motor
/// that helps us to know which direction and speed to make the motor rotating with
/// @param inp is the current position of the motor we can get it using getCurrentPosition() function
/// @returns Control Variable value
double computePID(double inp);
///
/// This function takes the output of computePID() function to convert it to speed and direction
/// @param outSignal is the output from computePID() function
/// @param PWM is the Pin number that motor driver PWM input connectecd to 
/// @param in1 is the Pin number that motor driver input1 connectecd to 
/// @param in2 is the Pin number that motor driver input2 connectecd to 
void convertSignal(float outSignal);
///
/// This function should be called from interrupt command as whenever the motor rotates
/// this function calculates the new position of the motor

///
/// This function sets the pins that motor encoders connected to
/// @param encoder_a is the Pin number that motor encoder_a connected to
/// @param encoder_b is the Pin number that motor encoder_b connected to
void setMotorEncoders(int encoder_a , int encoder_b);
///
/// This function gets the current position of the motor
/// @returns current poition of the motor
double getCurrentPosition();

void setMotorAngularVelocity(float av);
MotorSheild(int pwm , int in1 , int in2);
void readEncoder();
};
