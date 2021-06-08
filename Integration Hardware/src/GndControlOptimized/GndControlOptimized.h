#define BRAKE 0
#define dir_CW 2
#define dir_CCW 1
/*
  5  6
  3  4
  1  2
*/
// add Arrays
// 3 and 4 are switched
const int MOTOR_A[] = {0,40, 42, 46, 44, 48, 50};
const int MOTOR_B[] = {0,41, 43, 47, 45, 49, 51};

const int PWM_MOTOR[] = {0, 4, 5, 7, 6, 8, 9};


#define MOTOR_NUM 6 
#define MOTOR_1 0
#define MOTOR_2 1
#define MOTOR_3 3
#define MOTOR_4 2
#define MOTOR_5 4
#define MOTOR_6 5

short usSpeed = 225; //default motor speed
unsigned short usMotor_Status = BRAKE;
int MAX_PWM = 128;
int MAX_ANGLE = 90;

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm);

// void setup()
// {
//   for (int i = 40; i <= 51; i++)
//   {
//     pinMode(i, OUTPUT);
//   }
//   for (int i = 4; i <= 9; i++)
//   {
//     pinMode(i, OUTPUT);
//   }

//   Serial.begin(9600); // Initiates the serial to do the monitoring
//   Serial.println("Begin motor control");
//   Serial.println(); //Print function list for user selection
// }

// void loop()
// {
//   int user_input;

//   while (Serial.available())
//   {
//     user_input = Serial.parseInt(); //Read user input and trigger appropriate function
//     if (user_input != 0)
//       if (user_input == 5)
//         Stop();
//       else
//         turn(user_input);
//   }
// }

void Stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  for(int i=0; i<=MOTOR_NUM; i++)
  {
   motorGo(i, usMotor_Status, 0); 
  }
}
void turn(int deg, float speed)
{
  // Serial.print("Turn by: ");
  // Serial.println(deg);
  int VL = MAX_PWM, VR = MAX_PWM;
  if (deg >= 0 && deg <= 90)
  {
    VR -= deg * MAX_PWM / MAX_ANGLE;
    usMotor_Status = dir_CW;
  }
  else if (deg >= 270)
  {
    deg -= 270;
    int temp = MAX_PWM - deg * MAX_PWM / MAX_ANGLE;
    VL -= temp;
    usMotor_Status = dir_CW;
  }
  else if (deg > 90 && deg <= 180)
  {
    deg -= 90;
    int temp = MAX_PWM - deg * MAX_PWM / MAX_ANGLE;
    VR -= temp;
    usMotor_Status = dir_CCW;
  }
  else
  {
    deg -= 180;
    VL -= deg * MAX_PWM / MAX_ANGLE;
    usMotor_Status = dir_CCW;
  } 
   for(int i=1; i<=MOTOR_NUM; i++)
  {
    if(i%2 == 0)
      motorGo(i, usMotor_Status, VR * speed); 
     else
      motorGo(i, usMotor_Status, VL * speed); 
  }


  // Serial.println(VL);
  // Serial.println(VR);
}
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if (direct == dir_CW)
  {
    digitalWrite(MOTOR_A[motor], LOW);
    digitalWrite(MOTOR_B[motor], HIGH);
  }
  else if (direct == dir_CCW)
  {
    digitalWrite(MOTOR_A[motor], HIGH);
    digitalWrite(MOTOR_B[motor], LOW);
  }

    analogWrite(PWM_MOTOR[motor], pwm);
  }
  
