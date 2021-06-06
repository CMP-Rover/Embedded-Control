#pragma once
#include <Arduino.h>
class motorEnc
{
    public:
    int DIR1;
    int DIR2;
    int PWM;
    int RPM = 0;
    float rpm;
    long currentMillis=0, previousMillis=0;
    int interval,threshold;
    volatile long encoderValue;
    int inputVolt ,INCVAL;
    bool  reachedRequired;
    float SECTOMIN ,ENC_COUNT_REV;
    motorEnc(int dir1 , int dir2 , int pwm);
    void setRPM(int rpmReq);
    void CCW();
    void CW();
    void setPrev(long prev);
    void setCurr(long Curr);
};
