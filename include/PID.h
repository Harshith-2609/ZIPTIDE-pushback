#pragma once
#include "main.h"

class Praj
{
private:
public:
    double kP, kI, kD;
    double integral;
    double prevError;
    double error;
    double prevDerivative;
    Praj(double p, double i, double d);
    void reset();
    double compute(double target, double current, bool turn = false);
};