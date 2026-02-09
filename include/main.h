/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * \copyright Copyright (c) 2017-2024, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convenient for most student programmers.
 */
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * extern pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

#include "drivetrain.h"
#include "PTO.h"

#include "lemlib/api.hpp" // lemlib
#include "liblvgl/misc/lv_types.h"
#include "liblvgl/llemu.hpp"
#include "liblvgl/lvgl.h"


/**
 * You should add more #includes here
 */
// #include "okapi/api.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <chrono>
#include <functional>
#include <memory>
#include <limits>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <fstream>

/**
 * robot configurations
 */

extern pros::Controller master;
extern pros::Controller slave;
extern pros::Motor L1;
extern pros::Motor L2;
extern pros::Motor PTOL3;
extern pros::Motor LIntake;
extern pros::Motor R6;
extern pros::Motor R7;
extern pros::Motor PTOR8;
extern pros::Motor RIntake;
extern pros::MotorGroup L;
extern pros::MotorGroup R;
extern pros::MotorGroup DrivePTO;
extern pros::MotorGroup IntakePTO;
extern pros::MotorGroup Drivetrain;
extern pros::MotorGroup DrivetrainL;
extern pros::MotorGroup DrivetrainR;
extern pros::MotorGroup Left;
extern pros::MotorGroup Right;
extern pros::MotorGroup Intake2;
extern pros::MotorGroup Intake4;
extern pros::Imu inertial19;
extern pros::Rotation Yaxis;
extern pros::Rotation Xaxis;
extern pros::adi::Pneumatics DrivePTOPiston;
extern pros::adi::Pneumatics IntakePTOPiston;
extern pros::adi::Pneumatics Midgoal;
extern pros::adi::Pneumatics Loader;
extern pros::adi::Pneumatics Hook;
extern Distance distX;
extern Distance distY;

// declarations for classes
extern PTOManager pto;
// lemlib declarations for classes
extern lemlib::Chassis chassis;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;


/**
 * If you find doing extern pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
using namespace pros;
// using namespace extern pros::literals;
// using namespace okapi;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C"
{
#endif
  void autonomous(void);
  void initialize(void);
  void disabled(void);
  void competition_initialize(void);
  void opcontrol(void);
  void reset(float zero);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
// #include <iostream>
#endif
#endif // _PROS_MAIN_H_