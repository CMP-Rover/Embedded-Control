#include "PID_Control.h"
//----------------------------------------------------------------------------------------------
/*
 * Encoder_A and Encoder_B pins are used to read the encoder data from the microcontroller
 * data comes so fast so these two pins have to interrupt enabled pins
 */
/*-------------------Motor 1------------------*/
#define ENCODER_A_1 2
#define ENCODER_B_1 34
/*-------------------Motor 2------------------*/
#define ENCODER_A_2 3
#define ENCODER_B_2 35
/*-------------------Motor 3------------------*/
#define ENCODER_A_3 18
#define ENCODER_B_3 36
/*-------------------Motor 4------------------*/
#define ENCODER_A_4 19
#define ENCODER_B_4 37
/*-------------------Motor 5------------------*/
#define ENCODER_A_5 20
#define ENCODER_B_5 38
/*-------------------Motor 6------------------*/
#define ENCODER_A_6 21
#define ENCODER_B_6 39
/* The next variables are for Motor Driver
 * They are used to control motor speed and direction
 * We control the direction by the H-bridge
 * An H-bridge is an electronic circuit that switches the polarity of a voltage applied to a load. 
 * These circuits are often used in robotics and other applications 
 * to allow DC motors to run forwards or backwards
*/
//Driver 1   Motor 1 & 2
#define PWM_1 4             //Motor Driver PWM input
#define IN2_1 41             //Motor Driver input
#define IN1_1 40             //Motor Driver input
#define EN_1 A1

#define PWM_2 5             //Motor Driver PWM input
#define IN2_2 43            //Motor Driver input
#define IN1_2 42           //Motor Driver input
#define EN_2 A2

////////////////////////////////////////////
//Driver 2   Motor 3 & 4
#define PWM_3 6             //Motor Driver PWM input
#define IN2_3 45             //Motor Driver input
#define IN1_3 44             //Motor Driver input
#define EN_3 A3

#define PWM_4 7             //Motor Driver PWM input
#define IN2_4 47            //Motor Driver input
#define IN1_4 46           //Motor Driver input
#define EN_4 A4
////////////////////////////////////////////
//Driver 3   Motor 5 & 6
#define PWM_5 8             //Motor Driver PWM input
#define IN2_5 49             //Motor Driver input
#define IN1_5 48             //Motor Driver input
#define EN_5 A5

#define PWM_6 9             //Motor Driver PWM input
#define IN2_6 51            //Motor Driver input
#define IN1_6 50           //Motor Driver input
#define EN_6 A6

////////////////////////////////////////////
/*
 * This Fucntion is used to set the motor direction and speed
 * it takes Parameters (rotation direction , PWM Speed , PWM Pin ,in1 pin , in2 Pin)
 */

MotorSheild m1(PWM_1,IN1_1,IN2_1);
MotorSheild m2(PWM_2,IN1_2,IN2_2);
MotorSheild m3(PWM_3,IN1_3,IN2_3);
MotorSheild m4(PWM_4,IN1_4,IN2_4);
MotorSheild m5(PWM_5,IN1_5,IN2_5);
MotorSheild m6(PWM_6,IN1_6,IN2_6);
void setup() {
 
  Serial.begin(9600);
  pinMode(ENCODER_A_1, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B_1, INPUT); // ENCODER_B as Input
  pinMode(ENCODER_A_2, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B_2, INPUT); // ENCODER_B as Input
  pinMode(ENCODER_A_3, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B_3, INPUT); // ENCODER_B as Input
  pinMode(ENCODER_A_4, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B_4, INPUT); // ENCODER_B as Input
  pinMode(ENCODER_A_5, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B_5, INPUT); // ENCODER_B as Input
  pinMode(ENCODER_A_6, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B_6, INPUT); // ENCODER_B as Input
  pinMode(IN2_1, OUTPUT); // MOTOR_CW as Output
  pinMode(IN1_1, OUTPUT); // MOTOR_CW as Output
  pinMode(PWM_1, OUTPUT); // MOTOR_CW as Output
  pinMode(IN2_2, OUTPUT); // MOTOR_CW as Output
  pinMode(IN1_2, OUTPUT); // MOTOR_CW as Output
  pinMode(PWM_2, OUTPUT); // MOTOR_CW as Output
  pinMode(IN2_3, OUTPUT); // MOTOR_CW as Output
  pinMode(IN1_3, OUTPUT); // MOTOR_CW as Output
  pinMode(PWM_3, OUTPUT); // MOTOR_CW as Output
  pinMode(IN2_4, OUTPUT); // MOTOR_CW as Output
  pinMode(IN1_4, OUTPUT); // MOTOR_CW as Output
  pinMode(PWM_4, OUTPUT); // MOTOR_CW as Output
  pinMode(IN2_5, OUTPUT); // MOTOR_CW as Output
  pinMode(IN1_5, OUTPUT); // MOTOR_CW as Output
  pinMode(PWM_5, OUTPUT); // MOTOR_CW as Output
  pinMode(IN2_6, OUTPUT); // MOTOR_CW as Output
  pinMode(IN1_6, OUTPUT); // MOTOR_CW as Output
  pinMode(PWM_6, OUTPUT); // MOTOR_CW as Output
//  pinMode(EN_1 , OUTPUT);
//  digitalWrite(EN_1,HIGH);
//  pinMode(EN_2 , OUTPUT);
//  digitalWrite(EN_2,HIGH);
//  pinMode(EN_3 , OUTPUT);
//  digitalWrite(EN_3,HIGH);
//  pinMode(EN_4 , OUTPUT);
//  digitalWrite(EN_4,HIGH);
//  pinMode(EN_5 , OUTPUT);
//  digitalWrite(EN_5,HIGH);
//  pinMode(EN_6 , OUTPUT);
//  digitalWrite(EN_6,HIGH);
//  setPIDTarget(300);
//  setPIDParameters (24,0,16);
 m1.setMotorEncoders(ENCODER_A_1,ENCODER_B_1);
 m2.setMotorEncoders(ENCODER_A_2,ENCODER_B_2);
 m3.setMotorEncoders(ENCODER_A_3,ENCODER_B_3);
 m4.setMotorEncoders(ENCODER_A_4,ENCODER_B_4);
 m5.setMotorEncoders(ENCODER_A_5,ENCODER_B_5);
 m6.setMotorEncoders(ENCODER_A_6,ENCODER_B_6);
  /* attach an interrupt to pin ENCODER_A of the Arduino, 
   *  and when the pulse is in the RISING edge called the function -----.
   *  
*/

}

void loop() {
m1.setMotorAngularVelocity(-84);
m2.setMotorAngularVelocity(-84);
m3.setMotorAngularVelocity(-84);
m4.setMotorAngularVelocity(-84);
m5.setMotorAngularVelocity(-84);
m6.setMotorAngularVelocity(-84);
delay(3000);
m1.setMotorAngularVelocity(-64);
m2.setMotorAngularVelocity(-64);
m3.setMotorAngularVelocity(-64);
m4.setMotorAngularVelocity(-64);
m5.setMotorAngularVelocity(-64);
m6.setMotorAngularVelocity(-64);
delay(3000);
m1.setMotorAngularVelocity(-24);
m2.setMotorAngularVelocity(-24);
m3.setMotorAngularVelocity(-24);
m4.setMotorAngularVelocity(-24);
m5.setMotorAngularVelocity(-24);
m6.setMotorAngularVelocity(-24);
delay(3000);
m1.setMotorAngularVelocity(-14);
m2.setMotorAngularVelocity(-14);
m3.setMotorAngularVelocity(-14);
m4.setMotorAngularVelocity(-14);
m5.setMotorAngularVelocity(-14);
m6.setMotorAngularVelocity(-14);
delay(3000);
}
