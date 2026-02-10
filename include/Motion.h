#pragma once

// existing functions
void drive(double distInches, double timeout);
void driveheading(double distInches, double timeout, double targetHeading);
void drivehold(double distInches, double timeout);
void turn(double targetHeading);
void arc(double radiusInches, double angleDeg);
void Sweep(double targetAngleDeg, bool left);
void driveMF(float targetvalue, float timeout, float kP = 0.15, float kD = 0.9);
