#include "PID.h"
#include "main.h"
#include <cmath>
#include <algorithm>

template <typename T>
T clamp(T value, T minVal, T maxVal)
{
    if (value < minVal)
        return minVal;
    if (value > maxVal)
        return maxVal;
    return value;
}

Praj::Praj(double p, double i, double d)
{
    kP = p;
    kI = i;
    kD = d;
    integral = 0;
    prevError = 0;
    prevDerivative = 0;
}

void Praj::reset()
{
    integral = 0;
    prevError = 0;
    prevDerivative = 0;
}

double Praj::compute(double target, double current, bool turn)
{
    double error = target - current;

    if (turn)
    {
        // Wrap angle error to [-180, 180]
        if (error < -180)
            error += 360;
        if (error > 180)
            error -= 360;
        if (fabs(error) < 5)
        {
            integral += error;
            integral = clamp(integral, -100.0, 100.0);
        }
    }
    else
    {
        if (fabs(error) < 3)
        {
            integral += error;
            integral = clamp(integral, -100.0, 100.0);
        }
    }

    double derivative = error - prevError;
    //derivative = 0.8 * derivative + 0.2 * prevDerivative; // low-pass filter
    prevDerivative = derivative;
    prevError = error;

    double output = (error * kP) + (integral * kI) + (derivative * kD);

    return output;
}