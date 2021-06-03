/*
   Yellow is the interrupt
*/
// Motor encoder output pulse per rotation (change as required)
#define ENC_COUNT_REV 410.0

// Encoder output to Arduino Interrupt pin
#define ENC_IN 3

// MD10C PWM connected to pin 10
#define PWM 8
// MD10C DIR connected to pin 12
#define DIR1 48
#define DIR2 49

bool reachedRPM=false;

// Analog pin for potentiometer
int speedcontrol = 0;

// Pulse count from encoder
volatile long encoderValue = 0;

// One-second interval for measurements
int interval = 100;
#define SECTOMIN 600
// their product should be 60'000
// max speed: 70 RPM

// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

// Variable for RPM measuerment
float rpm = 0;

// Variable for PWM motor speed output
int inputVolt = 15;
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
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);

  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);

  // Setup initial values for timer
  previousMillis = millis();
}

int RPM = 0;
void loop()
{
  setRPM(RPM);
  // Control motor with potentiometer
  while (Serial.available())
  {
    int temp = Serial.parseInt(); // 0:93

    if (temp == 0)
      continue;
    if(temp != RPM)
      {
        reachedRPM=false;
        RPM = temp;
        rpm = RPM;
      } 
       
    Serial.print("RPM ");
    Serial.println(RPM);

    // Write PWM to controller
    if (RPM > 0)
    {
      digitalWrite(DIR1, LOW);
      digitalWrite(DIR2, HIGH);
    }
    else
    {
      digitalWrite(DIR1, HIGH);
      digitalWrite(DIR2, LOW);
    }
    setRPM(RPM);
  }
}

void updateEncoder()
{
  // Increment value for each pulse from encoder
  encoderValue++;
}
void setRPM(int rpmReq)
{
  if (rpmReq == 0)
      return;
  // Update RPM value every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
   if(!reachedRPM){
    // Calculate RPM
    int currRPM = (float)(encoderValue * SECTOMIN / ENC_COUNT_REV);
    if(abs(currRPM-rpmReq)>threshold ){
      if (currRPM < rpmReq){
          inputVolt+= INCVAL;}
        else if (currRPM > rpmReq){
         
          inputVolt-= INCVAL;}

        if (inputVolt >= 255){
          
          inputVolt = 255;}
        else if (inputVolt <= 0){
        
          inputVolt = 0;}
    }else{
      reachedRPM=true;
      }
      Serial.print("INPUT VOLT: ");
      Serial.print(inputVolt);
      Serial.print('\t');
      Serial.print(" PULSES: ");
      Serial.print(encoderValue);
      Serial.print('\t');
      Serial.print(" rpm: ");
      Serial.print(currRPM);
      Serial.print("\tRPM Required: ");
      Serial.println(rpmReq);
      //
      Serial.print("rotations: ");
      Serial.print(encoderValue / ENC_COUNT_REV * 100);
      Serial.println(" %\n");
    //
      analogWrite(PWM, inputVolt);
      encoderValue = 0;
      }
    
   
    //
      
  
  }
}
