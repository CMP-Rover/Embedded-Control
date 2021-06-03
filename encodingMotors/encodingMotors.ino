/*
   Yellow is the interrupt
*/
// Motor encoder output pulse per rotation (change as required)
#define ENC_COUNT_REV 410.0

#define MOTORNUMBER 1

// Encoder output to Arduino Interrupt pin
#define ENC_IN 2

// MD10C PWM connected to pin 10
#define PWM 4
// MD10C DIR connected to pin 12
#define DIR1 46
#define DIR2 47
int pwmAll[6]={4,5,6,7,8,9};//done
int allDIR1[6]={40,42,44,46,48,50};//done
int allDIR2[6]={41,43,45,47,49,51};//done
int allENC_IN[6]={2,18,19,20,21,3};//done

bool reachedRPM=false;
bool allreachedRPM[6]={false,false,false,false,false,false};

// Analog pin for potentiometer
int speedcontrol = 0;

// Pulse count from encoder
volatile long encoderValue = 0;
volatile long allencoderValue[6]={0,0,0,0,0,0};

// One-second interval for measurements
int interval = 100;
#define SECTOMIN 600
// their product should be 60'000
// max speed: 70 RPM

// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;
long allpreviousMillis[6]={0,0,0,0,0,0};
long allcurrentMillis[6]={0,0,0,0,0,0};

// Variable for RPM measuerment
float rpm = 0;
float allrpm[6]={0,0,0,0,0,0};

// Variable for PWM motor speed output
int inputVolt = 15;
int allinputVolt[6]={15,15,15,15,15,15};
#define INCVAL 5
#define threshold 1
void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);

  // Set encoder as input with internal pullup
  pinMode(ENC_IN, INPUT_PULLUP);

  // Set PWM and DIR connections as outputs
  pinMode(PWM, OUTPUT);
  int currTime=millis();
  for(int i=0;i<MOTORNUMBER;i++){
    pinMode(pwmAll[i], OUTPUT);
    pinMode(allDIR1[i], OUTPUT);
    pinMode(allDIR2[i], OUTPUT);
    allpreviousMillis[i]=currTime;
  }
  

  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(allENC_IN[0]), updateEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(allENC_IN[1]), updateEncoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(allENC_IN[2]), updateEncoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(allENC_IN[3]), updateEncoder4, RISING);
  attachInterrupt(digitalPinToInterrupt(allENC_IN[4]), updateEncoder5, RISING);
  attachInterrupt(digitalPinToInterrupt(allENC_IN[5]), updateEncoder6, RISING);

  // Setup initial values for timer
//  previousMillis = millis();
}

int RPM = 0;
void loop()
{
  for(int i=0;i<MOTORNUMBER;i++){
    setRPM(allrpm[i],i);
  }
  
  // Control motor with potentiometer
  while (Serial.available())
  {
    int temp = Serial.parseInt(); // 0:93
    for(int i=0;i<MOTORNUMBER;i++){
      if (temp == 0)
        continue;
      if(temp != allrpm[i])
        {
          allreachedRPM[i]=false;
          allrpm[i]=temp;
        } 
         
      Serial.print("RPM 1");
      Serial.println(allrpm[0]);
      Serial.print("RPM 2");
      Serial.println(allrpm[1]);
      Serial.print("RPM 3");
      Serial.println(allrpm[2]);
      Serial.print("RPM 4");
      Serial.println(allrpm[3]);
      Serial.print("RPM 5");
      Serial.println(allrpm[4]);
      Serial.print("RPM 6");
      Serial.println(allrpm[5]);

    // Write PWM to controller
    
      if (allrpm[i] > 0)
      {
        digitalWrite(allDIR1[i], LOW);
        digitalWrite(allDIR2[i], HIGH);
      }
      else
      {
        digitalWrite(allDIR1[i], HIGH);
        digitalWrite(allDIR2[i], LOW);
      }
      setRPM(allrpm[i],i);
    }
  }
}

void updateEncoder1()
{
  // Increment value for each pulse from encoder
  allencoderValue[0]++;
}
void updateEncoder2()
{
  // Increment value for each pulse from encoder
  allencoderValue[1]++;
}
void updateEncoder3()
{
  // Increment value for each pulse from encoder
  allencoderValue[2]++;
}
void updateEncoder4()
{
  // Increment value for each pulse from encoder
  allencoderValue[3]++;
}
void updateEncoder5()
{
  // Increment value for each pulse from encoder
  allencoderValue[4]++;
}
void updateEncoder6()
{
  // Increment value for each pulse from encoder
  allencoderValue[5]++;
}

void setRPM(int rpmReq,int motorSelector)
{
  if (rpmReq == 0)
      return;
  // Update RPM value every second
  allcurrentMillis[motorSelector] = millis();
  if (allcurrentMillis[motorSelector] - allpreviousMillis[motorSelector] > interval)
  {
    allpreviousMillis[motorSelector] = allcurrentMillis[motorSelector];
   if(!allreachedRPM[motorSelector]){
    // Calculate RPM
    int currRPM = (float)(allencoderValue[motorSelector] * SECTOMIN / ENC_COUNT_REV);
    if(abs(currRPM-rpmReq)>threshold ){
      if (currRPM < rpmReq){
          allinputVolt[motorSelector]+= INCVAL;}
        else if (currRPM > rpmReq){
         
          allinputVolt[motorSelector]-= INCVAL;}

        if (allinputVolt[motorSelector] >= 255){
          
          allinputVolt[motorSelector] = 255;}
        else if (allinputVolt[motorSelector] <= 0){
        
          allinputVolt[motorSelector] = 0;}
    }else{
      allreachedRPM[motorSelector]=true;
      }
      Serial.print("INPUT VOLT:");
      Serial.print(motorSelector);
      Serial.print("    ");
      Serial.print(allinputVolt[motorSelector]);
      Serial.print('\t');
      Serial.print(" PULSES:");
      Serial.print(motorSelector);
      Serial.print("    ");
      Serial.print(allencoderValue[motorSelector]);
      Serial.print('\t');
      Serial.print(" rpm: ");
      Serial.print(motorSelector);
      Serial.print("    ");
      Serial.print(currRPM);
      Serial.print(motorSelector);
      Serial.print("    ");
      Serial.print("\tRPM Required: ");
      Serial.println(rpmReq);
      //
      Serial.print("rotations: ");
      Serial.print(motorSelector);
      Serial.print("    ");
      Serial.print(allencoderValue[motorSelector] / ENC_COUNT_REV * 100);
      Serial.println(" %\n");
    //
      analogWrite(pwmAll[motorSelector], allinputVolt[motorSelector]);
      allencoderValue[motorSelector] = 0;
      }
    
   
    //
      
  
  }
}
