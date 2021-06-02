#pragma once
float mapfloat(long x, long in_min, long in_max, long out_min, long out_max);

// Low threshold, medium threshold, high threshold
static const int MQSensitivityThresholds[] = {0,384,768};
enum MQThresholds{Low, Med, Hi};