#include "main.h"
#include "Autons.h"
#include "Motion.h"
#include "liblvgl/llemu.h"
#include "pros/distance.hpp"
#include "pros/motors.h"

// ----------------- GLOBALS -----------------


// Tasks
pros::Task* odomTask = nullptr;
// PTO Manager
PTOManager pto(
    {&L1, &L2, &PTOL3, &LIntake},
    {&R6, &R7, &PTOR8, &RIntake},
    'B',
    'F'
    
);


pros::MotorGroup* leftSide;
pros::MotorGroup* rightSide;

void initialize_drivetrain_selection(bool Drivetrain_Motors) {
    if(pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        Drivetrain_Motors = false;
    } else {
        Drivetrain_Motors = true;
    }
    
    if (Drivetrain_Motors) {
        leftSide = &L;     // Use the 3-motor groups
        rightSide = &R;
    } else {
        leftSide = &Left;  // Use the 2-motor groups
        rightSide = &Right;
    }
}

// Drivetrain / LemLib config
lemlib::Drivetrain drivetrain(&L, &R, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);
lemlib::Drivetrain drivetrain2(&Left, &Right, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);
lemlib::Drivetrain drivetrain3(&DrivetrainL, &DrivetrainR, 12.25, lemlib::Omniwheel::NEW_325, 480, 0);
// Odom wheels
lemlib::TrackingWheel horizontal_tracking_wheel(&Xaxis, 2, 1.8);//1.8
lemlib::TrackingWheel vertical_tracking_wheel(&Yaxis, 2, 0.8);//0.3

// Odom sensors
lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr, &horizontal_tracking_wheel, nullptr, &inertial19);

//pid constants for auton
lemlib::ControllerSettings lateral_controller(10, 0, 55, 0, 1,100, 3, 500,
                                              0); // slew-80


lemlib::ControllerSettings angular_controller(4.15, 0, 34, 0, 2, 20, 10, 200,
                                              0);

// Chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
lemlib::Chassis chassis2(drivetrain2, lateral_controller, angular_controller, sensors);
lemlib::Chassis chassis3(drivetrain3, lateral_controller, angular_controller, sensors);

// ----------------- ODOM DEBUG TASK -----------------
void odomDebug(void*) {
    master.clear();
    while(true) {
        lemlib::Pose pose = chassis.getPose();
        pros::lcd::print(1, "X: %.2f", pose.x);
        pros::lcd::print(2, "Y: %.2f", pose.y);
        pros::lcd::print(3, "H: %.2f", pose.theta);
        pros::lcd::print(4, "X true: %.2f", Xaxis.get_position());
        pros::lcd::print(5, "Y true: %.2f", Yaxis.get_position());

        master.print(0, 0, "X:%5.1f Y:%5.1f", pose.x, pose.y);
        master.print(1, 0, "H:%5.1f", pose.theta);
        master.print(2, 0, "X true:%5.1f Y true:%5.1f", Xaxis.get_position(), Yaxis.get_position());
        pros::delay(50);
    }
}

// ----------------- INITIALIZE -----------------
void initialize() {
    

    // Sensors reset
    // inertial19.reset();
    // while(inertial19.is_calibrating()) pros::delay(10);
    // Xaxis.reset_position();
    // Yaxis.reset_position();
    chassis.calibrate(true);
    c::lcd_initialize();
    DrivetrainL.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    DrivetrainR.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.setPose(0,0,0);

    // Start Odom debug task
    odomTask = new pros::Task(odomDebug);


}

// ----------------- DISABLED -----------------
void disabled() {}

// ----------------- COMPETITION INIT -----------------
void competition_initialize() {}

// ----------------- AUTONOMOUS -----------------
void autonomous() { 
    SAWP();
    //splitLeft();
    //LeftWing();
    //RightWing();
}

// ----------------- OPERATOR CONTROL -----------------
void opcontrol() {
  new pros::Task(DriveTrainControls);
  new pros::Task(OutakeControls);
  new pros::Task(IntakeRevControls);
  new pros::Task(MidControls);
  new pros::Task(IntakeControls);
  new pros::Task(DrivePTOcontrols);
  new pros::Task(Loadercontrols);
  new pros::Task(Hookcontrols);
  new pros::Task(skillsMidControls);
  new pros::Task(odomDebug);

  lemlib::Pose pose = chassis.getPose();
        pros::lcd::print(0, "X: %.2f", pose.x);
        pros::lcd::print(1, "Y: %.2f", pose.y);
        pros::lcd::print(2, "Theta: %.2f", pose.theta);

  while (true) {

    pros::delay(20);
  }
}