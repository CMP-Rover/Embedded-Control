#include "PID_Control.h"
//----------------------------------------------------------------------------------------------
/*
 * Encoder_A and Encoder_B pins are used to read the encoder data from the microcontroller
 * data comes so fast so these two pins have to interrupt enabled pins
 */
#define ENCODER_A 2
#define ENCODER_B 3
/* The next variables are for Motor Driver
 * They are used to control motor speed and direction
 * We control the direction by the H-bridge
 * An H-bridge is an electronic circuit that switches the polarity of a voltage applied to a load. 
 * These circuits are often used in robotics and other applications 
 * to allow DC motors to run forwards or backwards
*/
#define PWM 5             //Motor Driver PWM input
#define IN2 6             //Motor Driver input
#define IN1 7             //Motor Driver input

/*
 * This Fucntion is used to set the motor direction and speed
 * it takes Parameters (rotation direction , PWM Speed , PWM Pin ,in1 pin , in2 Pin)
 */


void setup() {
 
  Serial.begin(9600);
  pinMode(ENCODER_A, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B, INPUT); // ENCODER_B as Input
  pinMode(IN2, OUTPUT); // MOTOR_CW as Output
  pinMode(IN1, OUTPUT); // MOTOR_CW as Output
  pinMode(PWM, OUTPUT); // MOTOR_CW as Output
  setPIDTarget(800);
  setPIDParameters (24,0,16);
  setMotorEncoders(ENCODER_A,ENCODER_B);
  /* attach an interrupt to pin ENCODER_A of the Arduino, 
   *  and when the pulse is in the RISING edge called the function -----.
*/
  attachInterrupt(digitalPinToInterrupt(ENCODER_A),readEncoder,RISING);
}

void loop() {
float pos = getCurrentPosition();
float conSignal = computePID(pos);
convertSignal(conSignal , PWM ,  IN1 , IN2);
Serial.print("Pos : ");
Serial.println(pos);



}
