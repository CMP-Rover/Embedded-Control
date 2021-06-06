#include <ros.h>
#include <Rover_msgs/sensors_data.h>
#include <Rover_msgs/motor_movment.h>

#define BRAKE 0
#define CW 2
#define CCW 1
#define INITIAL_SPEED 50
/*
  5  6
  3  4
  1  2
*/
//MOTOR 1
#define MOTOR_A1_PIN 40
#define MOTOR_B1_PIN 41

//MOTOR 2
#define MOTOR_A2_PIN 42
#define MOTOR_B2_PIN 43

//MOTOR 3
#define MOTOR_A3_PIN 45
#define MOTOR_B3_PIN 44

//MOTOR 4
#define MOTOR_A4_PIN 47
#define MOTOR_B4_PIN 44

//MOTOR 5
#define MOTOR_A5_PIN 48
#define MOTOR_B5_PIN 49

//MOTOR 6
#define MOTOR_A6_PIN 50
#define MOTOR_B6_PIN 51

#define PWM_MOTOR_1 4
#define PWM_MOTOR_2 5
#define PWM_MOTOR_3 6
#define PWM_MOTOR_4 7
#define PWM_MOTOR_5 8
#define PWM_MOTOR_6 9

#define CURRENT_MOTOR_1 A4
#define CURRENT_MOTOR_2 A5
#define CURRENT_MOTOR_3 A6
#define CURRENT_MOTOR_4 A7
#define CURRENT_MOTOR_5 A8
#define CURRENT_MOTOR_6 A9

#define MOTOR_1 0
#define MOTOR_2 1
#define MOTOR_3 3
#define MOTOR_4 2
#define MOTOR_5 4
#define MOTOR_6 5

short usSpeed = 225; //default motor speed
unsigned short usMotor_Status = BRAKE;
//#define ratioDegSpeed 255 / 90
int MAX_PWM = 255;
int MAX_ANGLE = 90;

float motor_speed = 0;
int motor_angle = 0;


void messageCb( const Rover_msgs::motor_movment &movemnt_msg){
  if (movemnt_msg.speed != motor_speed || movemnt_msg.angle != motor_angle)
  {
    motor_speed = movemnt_msg.speed;
    motor_angle = movemnt_msg.angle;

    turn(motor_angle, motor_speed);
  }
 }

ros::NodeHandle nh;
ros::Subscriber<Rover_msgs::motor_movment> sub("motor_action", &messageCb);



void setup()
{
  for (int i = 40; i <= 51; i++)
  {
    pinMode(i, OUTPUT);
  }
  for (int i = 4; i <= 9; i++)
  {
    pinMode(i, OUTPUT);
  }

  nh.initNode();
  nh.subscribe(sub);
 
}

void loop()
{
  nh.spinOnce();
  delay(1);
}



void turn(int deg, float motorSpeed)
{
 
  int VL = MAX_PWM, VR = MAX_PWM;
  if (deg >= 0 && deg <= 90)
  {
    VR -= deg * MAX_PWM/MAX_ANGLE;
      usMotor_Status = CW;
    VR*=motorSpeed;
    VL*=motorSpeed;

  motorGo(MOTOR_1, CCW, VL);
  motorGo(MOTOR_2, usMotor_Status, VR);

  motorGo(MOTOR_3, usMotor_Status, VL);
  motorGo(MOTOR_4, CCW, VR);

  motorGo(MOTOR_5, usMotor_Status, VL);
  motorGo(MOTOR_6, usMotor_Status, VR);
  }
  else if (deg >= 270)
  {
    deg -= 270;
    int temp = MAX_PWM - deg * MAX_PWM/MAX_ANGLE;
    VL -= temp;
      usMotor_Status = CW;

  motorGo(MOTOR_1, CCW, VL);
  motorGo(MOTOR_2, usMotor_Status, VR);

  motorGo(MOTOR_3, usMotor_Status, VL);
  motorGo(MOTOR_4, CCW, VR);

  motorGo(MOTOR_5, usMotor_Status, VL);
  motorGo(MOTOR_6, usMotor_Status, VR);
      VR*=motorSpeed;
    VL*=motorSpeed;
  }
  else if(deg >90 && deg <= 180)
  {
    deg -= 90;
    int temp = MAX_PWM - deg * MAX_PWM/MAX_ANGLE;
    VR -= temp;
      usMotor_Status = CCW;

  motorGo(MOTOR_1, CW, VL);
  motorGo(MOTOR_2, usMotor_Status, VR);

  motorGo(MOTOR_3, usMotor_Status, VL);
  motorGo(MOTOR_4, CW, VR);

  motorGo(MOTOR_5, usMotor_Status, VL);
  motorGo(MOTOR_6, usMotor_Status, VR);
      VR*=motorSpeed;
    VL*=motorSpeed;
    }
    else 
    {
      deg-=180;
VL -= deg * MAX_PWM/MAX_ANGLE;
       usMotor_Status = CCW;

  motorGo(MOTOR_1, CW, VL);
  motorGo(MOTOR_2, usMotor_Status, VR);

  motorGo(MOTOR_3, usMotor_Status, VL);
  motorGo(MOTOR_4, CW, VR);

  motorGo(MOTOR_5, usMotor_Status, VL);
  motorGo(MOTOR_6, usMotor_Status, VR);
      VR*=motorSpeed;
    VL*=motorSpeed;
      }


}
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if (direct == CW)
  {
    digitalWrite(motor * 2 + 40, LOW);
    digitalWrite(motor * 2 + 41, HIGH);
  }
  else if (direct == CCW)
  {
    digitalWrite(motor * 2 + 40, HIGH);
    digitalWrite(motor * 2 + 41, LOW);
  }

  analogWrite(motor + 4, pwm);
}
