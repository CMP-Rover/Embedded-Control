# 1 "e:\\CMP 2\\encoder\\code\\MostafaWael_227.ino"
# 1 "e:\\CMP 2\\encoder\\code\\MostafaWael_227.ino"

// Motor encoder output pulses per 360 degree revolution (measured manually)


// Encoder output to Arduino Interrupt pin. Tracks the pulse count.


// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.


// Keep track of the number of right wheel pulses
volatile long wheel_pulse_count = 0;

// One-second interval for measurements
int interval = 1000;

// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

// Variable for RPM measuerment
float rpm = 0;

// ain shams
float rpmReq = 43;
float tolerance = 3;
int inputVolt = 255;

void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);

    // Set pin states of the encoder
    pinMode(3, 0x2);
    pinMode(12, 0x0);

    // Every time the pin goes high, this is a pulse
    attachInterrupt(((3) == 2 ? 0 : ((3) == 3 ? 1 : -1)), wheel_pulse, 3);
    pinMode(7, 0x1);
    pinMode(6, 0x1);
    pinMode(11, 0x1);
    //
    digitalWrite(6, 0x0);
    digitalWrite(7, 0x1);
}
void loop()
{
    if (currentMillis - previousMillis > 0.5 * interval)
    {
        if (((rpm - rpmReq)>0?(rpm - rpmReq):-(rpm - rpmReq)) > tolerance)
        {
            Serial.print("RPM: ");
            Serial.print(rpm);
            Serial.println(" adabting...");
            if ((rpm - rpmReq) > 0)
            {
                Serial.print("dec..   ");
                if (--inputVolt <= 0)
                    inputVolt = 0;
            }
            else
            {
                Serial.print("inc..   ");
                if (++inputVolt >= 255)
                    inputVolt = 255;
            }
            Serial.print("Volt:");
            Serial.println(inputVolt);
        }
        else
        {
            Serial.println("Manga Done!!!!!!!!!!!!");
        }
        analogWrite(11, inputVolt);
    }

    // Record the time
    currentMillis = millis();

    // If one second has passed, print the number of pulses
    if (currentMillis - previousMillis > interval)
    {
        previousMillis = currentMillis;

        // Calculate revolutions per minute
        rpm = (float)(wheel_pulse_count * 60 / 24); // RPM

        Serial.print(" Pulses: ");
        Serial.println(wheel_pulse_count);
        Serial.print(" inputVolt: ");
        Serial.println(rpm);
        Serial.println(" RPM");

        wheel_pulse_count = 0;
    }
}

// Increment the number of pulses by 1
void wheel_pulse()
{
    // Read the value for the encoder for the wheel
    if (digitalRead(12))
    {
        wheel_pulse_count--; // Reverse
    }
    else
    {
        wheel_pulse_count++; // Forward
    }
}
