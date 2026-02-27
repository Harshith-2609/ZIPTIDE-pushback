#include "motion.h"
#include "pid.h"
#include "main.h"
#include <cmath>
#include <algorithm>
#include "PTO.h"
#include "pros/rtos.hpp"




const double wheelTrack = 11.75; // in inches (left-right distance)

// PID class values (Existing values)
Praj distPID(0.07, 0, 0.2);
Praj distPIDnew(0.13, 0, 0.9);
Praj fastTurnPID(0.03, 0, 0.23);

Praj slowTurnPID(0.03, 0, 0.28);

Praj arcPID(0.15, 0, 0);
Praj sweepPID(0.05, 0, 0.5);

Praj drivePID(0.05, 0, 0.6);
Praj headingPID(0.03, 0.0001, 0.23);

/**
 * @brief Clamps a value between a minimum and maximum.
 */
template <typename T>
T clamp(T value, T minVal, T maxVal)
{
    if (value < minVal)
        return minVal;
    if (value > maxVal)
        return maxVal;
    return value;
}



// Global or external PTO instance
extern PTOManager pto;

// PTO–aware drive function
void setDrivePTO(double left, double right) {
    left = clamp(left, -12.0, 12.0);
    right = clamp(right, -12.0, 12.0);

    // Get only motors engaged in the current configuration
    auto leftMotors = pto.getActiveLeftMotors();
    auto rightMotors = pto.getActiveRightMotors();

    for (auto* m : leftMotors)
        m->move_voltage(left * 100); // Convert volts to mV

    for (auto* m : rightMotors)
        m->move_voltage(right * 120); // Convert volts to mV
}

void stopsPTO() {
    auto leftMotors = pto.getActiveLeftMotors();
    auto rightMotors = pto.getActiveRightMotors();

    for (auto* m : leftMotors)
        m->brake();

    for (auto* m : rightMotors)
        m->brake();
}


void stopsPTOhold() {
    auto leftMotors = pto.getActiveLeftMotors();
    auto rightMotors = pto.getActiveRightMotors();

    for (auto* m : leftMotors)
        m->brake();

    for (auto* m : rightMotors)
        m->brake();
}

/**
 * @brief Sets left and right motor voltages.
 */
void setDrive(double left, double right)
{
    // Clamp values for safety
    left = clamp(left, -12.0, 12.0);
    right = clamp(right, -12.0, 12.0);

    // Send voltage to motors (volt units)
    L1.move_voltage(left * 120);
    L2.move_voltage(left * 120);
    PTOL3.move_voltage(left * 120);

    R6.move_voltage(right * 120);
    R7.move_voltage(right * 120);
    PTOR8.move_voltage(right * 120);
}


/**
 * @brief Stops all drive motors with brake mode.
 */
void stops()
{
    // Stop all motors
    L1.brake();
    L2.brake();
    PTOL3.brake();
    R6.brake();
    R7.brake();
    PTOR8.brake();
}

/**
 * @brief Applies a minimum voltage threshold to overcome motor friction.
 */
double minVolt(double v)
{
    const double MIN_V = 2.0;
    if (v > -MIN_V && v < 0)
        return -MIN_V;
    if (v > 0 && v < MIN_V)
        return MIN_V;
    return v;
}

double minVoltturn(double v)
{
    const double MIN_V = 3.0;
    if (v > -MIN_V && v < 0)
        return -MIN_V;
    if (v > 0 && v < MIN_V)
        return MIN_V;
    return v;
}

double wrapAngle(double error) {
    while (error > 180) error -= 360;
    while (error < -180) error += 360;
    return error;
}

const float WHEEL_CIRCUMFERENCE = M_PI * 3.25;              // ~12.09 inches
const float INCHES_PER_MOTOR_TURN = WHEEL_CIRCUMFERENCE * 0.8; // Gear ratio is 48:60, so multiply by 0.8

/**
 * @brief Calculates the average distance traveled based on motor rotations.
 */
float getAverageDistance()
{
    // Get positions from all motors (in turns/rotations)
    float left1_pos = L1.get_position();
    float left2_pos = L2.get_position();
    float right1_pos = R6.get_position();
    float right2_pos = R7.get_position();

    // Calculate average motor rotations
    float avg_rotations = (left1_pos + left2_pos +
                           right1_pos + right2_pos) /
                          4.0;

    // Convert average motor rotations to inches traveled
    float distance_inches = avg_rotations * INCHES_PER_MOTOR_TURN;

    return distance_inches;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
    //TUNE HERE// TUNE HERE// TUNE HERE// TUNE HERE// TUNE HERE// TUNE HERE//
//-----------------------------------------------------------------------------------------//
float error = 0 ; // sensor - desired
float prevError = 0; // position from last loop (previous error)
float derivative = 0;
float output = 0; 
float integral = 0;
float prevoutput = 0;
bool enabledrivepid;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 float averageposition;

void driveMF(float targetvalue, float timeout, float kP , float kD){

  float elapsedtime = 0;
  Yaxis.reset_position();
  enabledrivepid = true;
  while(enabledrivepid) {
    averageposition = chassis.getPose().y;//((Yaxis.get_position()/360.0 )* (2 * M_PI));

    error = targetvalue - averageposition;
    derivative = (error - prevError);
    

    output = (kP*error) + (kD*derivative);// kD = 3, Kp = 7

    if (output > 127) output = 127;
    if (output < -127) output = -127;

    L.move(output);
    R.move(output);

    if ((fabs(error) < 1) || (elapsedtime >= timeout)) {
      break;
    }

    elapsedtime += 10;
    prevError = error;
    delay(10);
  }
    L1.brake();
    L2.brake();
    PTOL3.brake();
    R6.brake();
    R7.brake();
    PTOR8.brake();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 



/**
 * @brief Drives forward using an 8-motor drivetrain (4 left, 4 right) with PD control.
 */
void driveForwardPID8(float distInches, float timeoutMs, float kP, float kD, float minSpeed) {
    Yaxis.reset_position();

    float prevErr = 0;
    float elapsed = 0;

    while (elapsed <= timeoutMs) {
        // Rotation sensor is in degrees. Convert to linear inches.
        const float wheelDiameterIn = 3.25f;
        const float gearRatio = 0.8f; // wheel turns per motor turn (48:60)
        float currentInches = (Yaxis.get_position() / 360.0f) * (static_cast<float>(M_PI) * wheelDiameterIn) * gearRatio;

        float err = distInches - currentInches;
        float deriv = err - prevErr;

        float output = (kP * err) + (kD * deriv);
        output = clamp(output, -127.0f, 127.0f);

        // keep enough power to overcome stiction while still preserving sign
        if (fabs(output) > 0.01f && fabs(output) < minSpeed) {
            output = (output > 0) ? minSpeed : -minSpeed;
        }

        // 4 motors left + 4 motors right
        DrivetrainL.move(output);
        DrivetrainR.move(output);

        if (fabs(err) < 0.75f) {
            break;
        }

        prevErr = err;
        elapsed += 10;
        pros::delay(10);
    }

    DrivetrainL.brake();
    DrivetrainR.brake();
}
float restrain(float num, float min, float max){
  if (num > max) num -= (max-min);
  if (num < min) num += (max-min);
  return num;
}








/**
 * @brief Drives the robot a linear distance using motor encoders and IMU heading stabilization.
 */
void drive(double distInches, double timeout)
{
    distPID.reset();
    double target = distInches-0.5;
    double start = getAverageDistance();
    double lastError = 0;
    int elapsed = 0;

    while (true)
    {
        // Current pose and distance traveled
        double current= getAverageDistance();
        double traveled = current-start;
        
        if (distInches < 0)
        {
            traveled = traveled; 
        }

        double error = target - traveled;
        // Compute linear output (PID)
        double linearOut = distPID.compute(target, traveled);
        // Clamp output between -1 and 1
        linearOut = clamp(linearOut, -1.0, 1.0);
        // Scale to volts
        linearOut = linearOut * 12.0;
        linearOut = minVolt(linearOut);
        double leftVolt = linearOut;
        double rightVolt = linearOut;
        setDrivePTO(leftVolt, rightVolt);
        // Exit conditions
        if ((fabs(error) < 1 && fabs(error - lastError) < 0.1) || elapsed > timeout)
            break;
        lastError = error;
        elapsed += 10;
        pros::delay(10);
    }

    stopsPTO();
}

void driveheading(double distInches, double timeout, double targetHeading)
{
    distPID.reset();
    headingPID.reset();

    double targetDist = distInches + 1;
    double startDist = getAverageDistance();

    double lastError = 0;
    int elapsed = 0;

    while (true)
    {
        double currentDist = getAverageDistance();
        double traveled = currentDist - startDist;

        double distError = targetDist - traveled;

        // ----- Distance PID -----
        double linearOut = distPID.compute(targetDist, traveled);
        linearOut = clamp(linearOut, -1.0, 1.0);
        linearOut *= 12.0;
        linearOut = minVolt(linearOut);

        // ----- Heading PID -----
        double currentHeading = inertial19.get_heading();
        double headingError = wrapAngle(targetHeading - currentHeading);

        double turnOut = headingPID.compute(0, headingError);

        // Scale heading correction to 5%
        turnOut *= 0.05;

        // Convert to volts and clamp
        turnOut = clamp(turnOut, -12.0, 12.0);

        // ----- Combine outputs -----
        double leftVolt  = linearOut + turnOut;
        double rightVolt = linearOut - turnOut;

        setDrivePTO(leftVolt, rightVolt);

        // Exit condition
        if ((fabs(distError) < 1 && fabs(distError - lastError) < 0.1) ||
            elapsed > timeout)
            break;

        lastError = distError;
        elapsed += 10;
        pros::delay(10);
    }

    stopsPTO();
}


void drivehold(double distInches, double timeout)
{
    distPID.reset();
    double target = distInches + 1; 
    double start = getAverageDistance();
    double lastError = 0;
    int elapsed = 0;

    while (true)
    {
        // Current pose and distance traveled
        double current= getAverageDistance();
        double traveled = current-start;
        
        if (distInches < 0)
        {
            traveled = traveled; 
        }

        double error = target - traveled;
        // Compute linear output (PID)
        double linearOut = distPID.compute(target, traveled);
        // Clamp output between -1 and 1
        linearOut = clamp(linearOut, -1.0, 1.0);
        // Scale to volts
        linearOut = linearOut * 12.0;
        linearOut = minVolt(linearOut);
        double leftVolt = linearOut;
        double rightVolt = linearOut;
        setDrivePTO(leftVolt, rightVolt);
        // Exit conditions
        if ((fabs(error) < 1 && fabs(error - lastError) < 0.1) || elapsed > timeout)
            break;
        lastError = error;
        elapsed += 10;
        pros::delay(10);
    }

    stopsPTOhold();
}



/**
 * @brief Turns the robot to a target absolute heading.
 */
void turn(double targetHeading)
{
    fastTurnPID.reset();
    slowTurnPID.reset();
    double elapsedTime = 0;
    const double timeout = 1500; // ms timeout
    double startheading = inertial19.get_heading(); 
    double turnAmount = targetHeading - startheading;
    if (turnAmount > 360)
        turnAmount -= 360;
    if (turnAmount < 0)
        turnAmount += 360;

     // Normalize target heading to [-180, 180]

    while (true)
    {
        // Assuming inertial19 is defined in robot-config.h
        double heading = inertial19.get_heading(); 

        // Proper angle difference calculation
        double remaining = targetHeading - heading;
        while (remaining > 180)
            remaining -= 360;
        while (remaining < -180)
            remaining += 360;

        double turnOutput;
        // Use the normalized remaining angle for PID
        if(turnAmount > 139)
        {
            turnOutput = slowTurnPID.compute(targetHeading, heading, true);
        }
        else
        {
            turnOutput = fastTurnPID.compute(targetHeading, heading, true);
        }

        // Clamp output between -1 and 1, then scale to volts
        turnOutput = clamp(turnOutput, -1.0, 1.0);

        double leftVolt = 12 * turnOutput;
        double rightVolt = -12 * turnOutput;

        // Apply minimum voltage
        leftVolt = minVoltturn(leftVolt);
        rightVolt = minVoltturn(rightVolt);

        // Exit conditions
        if (fabs(remaining) < 2.0 || elapsedTime >= timeout)
            break;

        setDrivePTO(leftVolt, rightVolt);

        elapsedTime += 10;
        pros::delay(10);
    }

    stopsPTO();
}

// /**
//  * @brief Executes a wide, smooth arc path.
//  */
// void arc(double radiusInches, double angleDeg)
// {
//     arcPID.reset();
//     double elapsedTime = 0;
//     const double maxTime = 3000;       // ms timeout
//     const double distTolerance = 0.5;  // inches
//     const double angleTolerance = 1.0; // degrees

//     bool arcLeft = (radiusInches < 0);
//     double absRadius = fabs(radiusInches);

//     double arcLength = 2.0 * M_PI * absRadius * (fabs(angleDeg) / 360.0);
//     Odom::Pose startPose = Odom::getPose();

//     // Calculate target heading and normalize to [-180, 180]
//     double targetHeading = startPose.theta + angleDeg;
//     while (targetHeading > 180)
//         targetHeading -= 360;
//     while (targetHeading < -180)
//         targetHeading += 360;

//     // Calculate wheel speed ratio
//     double innerRadius = absRadius - (wheelTrack / 2.0);
//     double outerRadius = absRadius + (wheelTrack / 2.0);
//     double speedRatio = innerRadius / outerRadius;

//     while (true)
//     {
//         Odom::Pose pose = Odom::getPose();

//         // Calculate traveled distance as Euclidean distance
//         double dx = pose.x - startPose.x;
//         double dy = pose.y - startPose.y;
//         double traveled = sqrt(dx * dx + dy * dy);

//         traveled = traveled / 2;
//         // Calculate heading error normalized to [-180, 180]
//         double headingError = targetHeading - pose.theta;
//         while (headingError > 180)
//             headingError -= 360;
//         while (headingError < -180)
//             headingError += 360;

//         // Exit conditions
//         if ((fabs(traveled - arcLength) <= distTolerance && fabs(headingError) <= angleTolerance) ||
//             elapsedTime >= maxTime)
//             break;

//         // PID output for linear distance
//         double linearOut = arcPID.compute(arcLength, traveled);
//         linearOut *= 12.0; // convert to volts

//         // Determine direction (forward or reverse) from sign of angleDeg
//         linearOut *= (angleDeg >= 0) ? 1.0 : -1.0;

//         double leftVolt = linearOut;
//         double rightVolt = linearOut;

//         // Correct arc direction logic
//         if (arcLeft)
//         {
//             // Left arc: right wheel is inner (slower), left wheel is outer (faster)
//             rightVolt *= speedRatio;
//         }
//         else
//         {
//             // Right arc: left wheel is inner (slower), right wheel is outer (faster)
//             leftVolt *= speedRatio;
//         }

//         setDrive(leftVolt, rightVolt);

//         elapsedTime += 10;
//         pros::delay(10);
//     }

//     stops();
// }

// /**
//  * @brief Performs a sweep turn (pivots one side only).
//  */
// void Sweep(double targetAngleDeg, bool left)
// {
//     sweepPID.reset();
//     double elapsedTime = 0;
//     const double timeout = 2000; // ms timeout

//     while (true)
//     {
//         // Current pose and heading
//         Odom::Pose pose = Odom::getPose();
//         double heading = pose.theta;

//         // PID output for turning
//         double turnOutput = sweepPID.compute(targetAngleDeg, heading, true);

//         double remaining = targetAngleDeg - heading;
//         if (remaining < -180)
//             remaining += 360;
//         if (remaining > 180)
//             remaining -= 360;

//         // Exit conditions
//         if (fabs(remaining) < 1.0 || elapsedTime >= timeout)
//             break;

//         // Clamp turn output and convert to volts
//         turnOutput = clamp(turnOutput, -1.0, 1.0);
//         double Volts = minVolt(turnOutput * 12.0);

//         // Set voltages based on turn direction
//         if (left)
//             setDrive(Volts, 0);
//         else
//             setDrive(0, Volts);

//         elapsedTime += 10;
//        pros::delay(10);
//     }

//     stops();
// }
