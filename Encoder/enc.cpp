#include "enc.h"

motorEnc::motorEnc(int dir1, int dir2, int pwm)
{
    DIR1 = dir1;
    DIR2 = dir2;
    PWM = pwm;
    interval = 100;
    SECTOMIN = 600;
    inputVolt = 128;
    INCVAL = 5;
    threshold = 1;
    reachedRequired = false;
    ENC_COUNT_REV = 410.0;
    pinMode(PWM, OUTPUT);
    pinMode(DIR1, OUTPUT);
    pinMode(DIR2, OUTPUT);
}
void motorEnc::setRPM(int rpmReq)
{
    if (rpmReq == 0)
        return;
    // Update RPM value every second
    currentMillis = millis();
    if (currentMillis - previousMillis > interval)
    {
        previousMillis = currentMillis;

        if (!reachedRequired)
        {
            // Calculate RPM
            rpm = (float)(encoderValue * SECTOMIN / ENC_COUNT_REV);
            if (abs(rpm - rpmReq) > threshold)
            {

                if (rpm < rpmReq)
                {
                    inputVolt += INCVAL;
                }
                else if (rpm > rpmReq)
                {
                    inputVolt -= INCVAL;
                }
                if (inputVolt >= 255)
                    inputVolt = 255;
                if (inputVolt <= 0)
                    inputVolt = 0;
            }
            else
            {
                reachedRequired = true;
            }
        }
        //
        Serial.print("INPUT VOLT: ");
        Serial.print(inputVolt);
        Serial.print('\t');
        Serial.print(" PULSES: ");
        Serial.print(encoderValue);
        Serial.print('\t');
        Serial.print(" rpm: ");
        Serial.print(rpm);
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
}

    void motorEnc::CCW()
    {
        digitalWrite(DIR1, LOW);
        digitalWrite(DIR2, HIGH);
    }

    void motorEnc::CW()
    {
        digitalWrite(DIR1, HIGH);
        digitalWrite(DIR2, LOW);
    }

    void motorEnc::setPrev(long prev)
    {
        previousMillis = prev;
    }
    void motorEnc::setCurr(long Curr)
    {
        currentMillis = Curr;
    }
