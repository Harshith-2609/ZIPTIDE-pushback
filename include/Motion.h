#pragma once

// existing functions
void drive(double distInches, double timeout);
void driveheading(double distInches, double timeout, double targetHeading);
void drivehold(double distInches, double timeout);
void turn(double targetHeading);
void arc(double radiusInches, double angleDeg);
void Sweep(double targetAngleDeg, bool left);
void driveMF(float targetvalue, float timeout, float kP, float kD);
void driveForwardPID8(float distInches, float timeoutMs, float kP, float kD, float minSpeed = 15);
