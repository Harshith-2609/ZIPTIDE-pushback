#pragma once
#include "main.h"

void driveM6(float targetvalue, float timeout, float kP, float kD);
void driveM8(float targetvalue, float timeout, float kP, float kD);

void resetPositionWithSensor(pros::Distance& sensor, double sensor_offset, double sensor_angle_deg, double field_half_size = 72);
void resetFront();
void resetBack();
void resetLeft();
void resetRight();