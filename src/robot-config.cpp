#include "main.h"
#include "pros/ai_vision.hpp"
#include "pros/distance.hpp"
using namespace pros;

// Controller definitions
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller slave(pros::E_CONTROLLER_PARTNER);

// Note: Gearsets are ==== pros::E_MOTOR_GEAR_600 (6:1) -- pros::E_MOTOR_GEAR_200 (18:1) -- pros::E_MOTOR_GEAR_100 (36:1)

// Motor definitions
//left side motors
pros::Motor L1(-12, pros::MotorGears::blue);
pros::Motor L2(-11, pros::MotorGears::blue);
pros::Motor PTOL3(-13, pros::MotorGears::blue);
pros::Motor LIntake(-15, pros::MotorGears::blue);
//right side motors
pros::Motor R6(16, pros::MotorGears::blue);
pros::Motor R7(18, pros::MotorGears::blue);
pros::Motor PTOR8(19, pros::MotorGears::blue);
pros::Motor RIntake(20, pros::MotorGears::blue);


pros::MotorGroup L({-12, -11, 13}, pros::MotorGears::blue); //L1, L2, PTOL3
pros::MotorGroup R({16, 18, -19}, pros::MotorGears::blue); //R6, R7, PTOR8
pros::MotorGroup DrivePTO({-13, 19}, pros::MotorGears::blue); //PTOL3, PTOR8
pros::MotorGroup IntakePTO({-15, 20}, pros::MotorGears::blue); //LIntake, RIntake
pros::MotorGroup Drivetrain({-12, -11, 16, 18}, pros::MotorGears::blue); //L1, L2, R6, R7
pros::MotorGroup DrivetrainL({-12, -11, 13, 15}, pros::MotorGears::blue); //L1, L2, PTOL3, LIntake
pros::MotorGroup DrivetrainR({16, 18, -19, -20}, pros::MotorGears::blue); //R6, R7, PTOR8, RIntake
pros::MotorGroup Drivetrainall({-12, -11, 16, 18, 13, -19, 15, -20}, pros::MotorGears::blue); //L1, L2, R6, R7, PTOL3, PTOR8, LIntake, RIntake
pros::MotorGroup Left({-12, -11}, pros::MotorGears::blue); //L1, L2
pros::MotorGroup Right({18, 16}, pros::MotorGears::blue); //R6, R7
pros::MotorGroup Intake2({-15, 20}, pros::MotorGears::blue); //LIntake, RIntake
pros::MotorGroup Intake4({-15, 20, 19, -13}, pros::MotorGears::blue); //LIntake, RIntake, PTOR8, PTOL3
// Sensor definitions
pros::Imu inertial19(6);
pros::Rotation Yaxis(14);
pros::Rotation Xaxis(-17);

Distance distF(5);
Distance distR(9);
Distance distL(4);
Distance distB(3);


// Pneumatic definitions
pros::adi::Pneumatics DrivePTOPiston('B', false);
pros::adi::Pneumatics IntakePTOPiston('F', false);
pros::adi::Pneumatics Midgoal('A', false);
pros::adi::Pneumatics Loader('G', false);
pros::adi::Pneumatics Hook('H', false);
pros::adi::Pneumatics Low('E', false);
