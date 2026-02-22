#include "PTO.h"
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"

// Helper for voltage
float tovolt(float percentage) { return (percentage * 12000.0 / 100.0); }

bool drivetrainEnabled = true;

// --------- DRIVETRAIN ---------
int DriveTrainControls() {
  while (true) {

    if (!drivetrainEnabled) {
      // Stop all drivetrain motors
        if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
            // Handle 4-motor mode
            Left.brake();
            Right.brake();
        } else if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
            // Handle 6-motor mode
            L.brake();
            R.brake();
        } else if (pto.getCurrentDriveMode() == DRIVE_8_MOTOR) {
            // Handle 8-motor mode
            DrivetrainL.brake();
            DrivetrainR.brake();
        }

      pros::delay(10);
      continue;
    }

    int forward = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    float leftVolt = tovolt(forward + turn);
    float rightVolt = tovolt(forward - turn);

    
        if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
            // Handle 4-motor mode
            Left.move_voltage(leftVolt);
            Right.move_voltage(rightVolt);
        } else if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
            // Handle 6-motor mode
            L.move_voltage(leftVolt);
            R.move_voltage(rightVolt);
        } else if (pto.getCurrentDriveMode() == DRIVE_8_MOTOR) {
            // Handle 8-motor mode
            DrivetrainL.move_voltage(leftVolt);
            DrivetrainR.move_voltage(rightVolt);
        }

    pros::delay(10);
  }
}

// --------- PTO CONTROL ---------
int DrivePTOcontrols() {
  bool DrivePTO1 = false;
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      if (DrivePTO1) {
        DrivePTO1 = false;
      } else {
        DrivePTO1 = true;
      }
      while (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {

        pros::delay(10);
      }

      if (DrivePTO1) {
        pto.setDriveMode(DRIVE_8_MOTOR);
      } else {
    }
    }
  }
}

int IntakeControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      if (pto.getCurrentDriveMode() == DRIVE_6_MOTOR) {
        IntakePTO.move(127); // reverse like VEX code

        // wait until button released
        while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
          pros::delay(10);
        }

        IntakePTO.brake();
      } else {
        pto.setDriveMode(DRIVE_6_MOTOR);
      }
    }
    pros::delay(10);
  }
}
int IntakeRevControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        IntakePTO.move(-127);
        DrivePTO.move(-127);

        while (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
          pros::delay(10);
        }

        IntakePTO.brake();
        DrivePTO.brake();
        pto.setDriveMode(DRIVE_6_MOTOR);
      } else {
        pto.setDriveMode(DRIVE_4_MOTOR);
      }
    }
    pros::delay(10);
  }
}
int OutakeControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        IntakePTO.move(127);
        DrivePTO.move(127);

        while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
          pros::delay(10);
        }

        IntakePTO.brake();
        DrivePTO.brake();
        pto.setDriveMode(DRIVE_6_MOTOR);
      } else {
        drivetrainEnabled = false;
        pto.setDriveMode(DRIVE_4_MOTOR);
        pros::delay(50);
        drivetrainEnabled = true;
      }
    }
    pros::delay(10);
  }
}
int MidControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        Midgoal.extend();
        IntakePTO.move(85);
        DrivePTO.move(-85);

        while (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
          pros::delay(10);
        }

        IntakePTO.brake();
        DrivePTO.brake();
        Midgoal.retract();
        pto.setDriveMode(DRIVE_6_MOTOR);
      } else {
        pto.setDriveMode(DRIVE_4_MOTOR);
      }
    }
    pros::delay(10);
  }
}

int skillsMidControls() {
  while (true) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      if (pto.getCurrentDriveMode() == DRIVE_4_MOTOR) {
        Loader.extend();
        IntakePTO.move(-127);
        DrivePTO.move(-127);
        pros::delay(500);
        IntakePTO.brake();
        DrivePTO.brake();
        Midgoal.extend();

        IntakePTO.move(85);
        DrivePTO.move(-55);

        while (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
          pros::delay(10);
        }

        IntakePTO.brake();
        DrivePTO.brake();
        Midgoal.retract();
        pto.setDriveMode(DRIVE_6_MOTOR);
      } else {
        pto.setDriveMode(DRIVE_4_MOTOR);
      }
    }
    pros::delay(10);
  }
}

// --------- LOADER ---------
int Loadercontrols() {
  static bool Loader1 = false;

  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
      Loader1 = !Loader1;
      if (Loader1) {
        Loader.extend();
      } else {
        Loader.retract();
      }
    }
    pros::delay(10);
  }
}

// --------- HOOK CONTROL ---------
int Hookcontrols() {
  static bool wing = false;

  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      wing = !wing;
      if (wing)
        Hook.extend();
      else
        Hook.retract();
    }
    pros::delay(10);
  }
}