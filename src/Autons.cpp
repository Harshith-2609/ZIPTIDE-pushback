#include "Autons.h"
// #include "Motion.h"
#include "PTO.h"
#include "main.h"
#include "motion.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cmath>
#include <istream>

void testing() {
  chassis.setPose(0, -6.5, 270);
  Intake2.move(127);
  chassis.moveToPose(0, -33.5, 90 + 270, 1100,
                     {.forwards = false, .horizontalDrift = 8, .lead = 0},
                     true);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  double yhere = chassis.getPose().y;
  chassis2.moveToPoint(12, yhere, 750, {.forwards = true}, true);
  pto.setDriveMode(DRIVE_4_MOTOR);
  chassis.waitUntilDone();
  chassis2.moveToPoint(-27.5, yhere - 1, 1000, {.forwards = false}, false);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(850);
  Drivetrain.brake();
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.moveToPoint(-12, yhere - 7, 1500, {.forwards = true}, false);
  chassis.turnToHeading(90 + 270, 900);
  chassis.moveToPoint(-35, yhere - 7, 1500,
                      {.forwards = false, .minSpeed = 100, .earlyExitRange = 5},
                      false);
  chassis.turnToHeading(60 + 270, 1000);
}

void splitLeft() {
  chassis.setPose(0, -6.5, 0);
  Intake2.move(127);
  chassis.moveToPose(0, -33.5, 90, 1100,
                     {.forwards = false, .horizontalDrift = 7.5, .lead = 0},
                     true);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  double yhere = chassis.getPose().y;
  chassis2.moveToPoint(12, yhere, 750, {.forwards = true}, true);
  pto.setDriveMode(DRIVE_4_MOTOR);
  chassis.waitUntilDone();
  chassis2.moveToPoint(-29, yhere, 1000, {.forwards = false}, false);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(1000);
  Drivetrain.brake();
  DrivePTO.brake();
  Intake2.brake();
  // resetRight();
  pto.setDriveMode(DRIVE_6_MOTOR);
  // chassis.moveToPose(-4, -33, 315,1500, {.forwards = true,.horizontalDrift =
  // 8, .lead = 0, .minSpeed = 100, .earlyExitRange = 18}, false);
  chassis.turnToHeading(0, 1000, {.maxSpeed = 127}, false);
  float x = chassis.getPose().x;
  chassis.moveToPose(x - 4, -10, 315 - 180, 1300,
                     {.forwards = true,
                      .horizontalDrift = 8,
                      .lead = 0,
                      .minSpeed = 90,
                      .earlyExitRange = 23},
                     true);
  IntakePTO.move(127);
  pros::delay(350);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.moveToPoint(-26, -5, 700, {.forwards = false}, false);
  // driveM6(-10, 1000, 4, 2);
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  Midgoal.extend();
  DrivePTO.move(-127);
  IntakePTO.move(85);
  pros::delay(800);
  Loader.retract();
  DrivePTO.brake();
  IntakePTO.move(127);
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.moveToPoint(
      0, yhere, 1500,
      {.forwards = true, .minSpeed = 100, .earlyExitRange = 9.7}, false);
  // delay(700);
  chassis.turnToHeading(270, 900);
  // chassis.cancelMotion();
  chassis.moveToPoint(-35, yhere + 4, 1500,
                      {.forwards = true, .minSpeed = 100, .earlyExitRange = 5},
                      false);
  chassis.turnToHeading(60 - 180, 1000);
}

void splitRight() {
  chassis.setPose(0, -6.5, 0);
  Intake2.move(127);
  chassis.moveToPose(0, -33.1, 270, 1100,
                     {.forwards = false, .horizontalDrift = 8, .lead = 0},
                     true);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  double yhere = chassis.getPose().y;
  chassis.moveToPoint(-12, -33, 750, {.forwards = true}, true);
  pto.setDriveMode(DRIVE_4_MOTOR);
  chassis.waitUntilDone();
  chassis2.moveToPoint(27.5, -33.1, 1000, {.forwards = false}, false);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(800);
  Drivetrain.brake();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.swingToHeading(
      30, lemlib::DriveSide::RIGHT, 1500,
      {.maxSpeed = 127, .minSpeed = 90, .earlyExitRange = 10.5});
  chassis.moveToPoint(40, 0, 1500,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 8.5},
                      false); // 3 bloacks
  pros::delay(350);
  Low.retract();
  chassis.waitUntilDone();
  Intake2.move(-107);
}

void LeftWing() {
  chassis.setPose(0, -6.5, 0);
  Intake2.move(127);
  chassis.moveToPose(0, -33.5, 90, 1100,
                     {.forwards = false, .horizontalDrift = 8, .lead = 0},
                     true);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  double yhere = chassis.getPose().y;
  chassis2.moveToPoint(12, yhere, 750, {.forwards = true}, true);
  pto.setDriveMode(DRIVE_4_MOTOR);
  chassis.waitUntilDone();
  chassis2.moveToPoint(-27.5, yhere - 1, 1000, {.forwards = false}, false);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(850);
  Drivetrain.brake();
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.moveToPoint(-12, yhere - 7, 1500, {.forwards = true}, false);
  chassis.turnToHeading(90, 900);
  chassis.moveToPoint(-35, yhere - 7, 1500,
                      {.forwards = false, .minSpeed = 100, .earlyExitRange = 5},
                      false);
  chassis.turnToHeading(60, 1000);
}


void RightWing() {
  chassis.setPose(0, -6.5, 0);
  Intake2.move(127);
  chassis.moveToPoint(-12, -33, 750, {.forwards = true}, true);
  pto.setDriveMode(DRIVE_4_MOTOR);
  chassis.waitUntilDone();
  chassis2.moveToPoint(27.5, -33, 1000, {.forwards = false}, false);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  IntakePTO.move(127);
  Loader.retract();
  pros::delay(800);
  Drivetrain.brake();
  DrivePTO.brake();
  Intake2.brake();
  // resetLeft();
  pto.setDriveMode(DRIVE_6_MOTOR);
  chassis.moveToPoint(14, -26, 1500,
                      {.forwards = true, .minSpeed = 100, .earlyExitRange = 4},
                      false);
  chassis.turnToHeading(275, 900);
  chassis.moveToPoint(39, -26.5, 1500,
                      {.forwards = false, .minSpeed = 100, .earlyExitRange = 5},
                      false);
  chassis.turnToHeading(225, 1000);
}


void SAWP() {
  ///////////////////////////PUSH//////////////////////////////
  chassis.setPose(0, 7, 0);
  Intake2.move(127);
  chassis.moveToPoint(0, 12, 1000, {.forwards = true}, false);
  chassis.moveToPose(0, -33.5, 270, 1500,{.forwards = false, .horizontalDrift = 8, .lead = 0},true);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  double yhere = chassis.getPose().y;

  ////Into Loader/////
  chassis2.moveToPoint(-12, yhere, 750, {.forwards = true}, true);
  pto.setDriveMode(DRIVE_4_MOTOR);
  chassis.waitUntilDone();

  // Into Long Goal/////
  chassis2.moveToPoint(28, yhere-1, 1000, {.forwards = false, .minSpeed =90, .earlyExitRange = 9}, false);
  DrivePTO.move(127); // outakes into far long goal 3
  Drivetrain.move(-127);
  Loader.retract();
  pros::delay(1000);
  Drivetrain.brake();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  ///////////////////////////ALL MIDDLE BLOCKS//////////////////////////////
  chassis.turnToHeading(10, 1000, {.maxSpeed = 127, .minSpeed = 90, .earlyExitRange = 15}, false);
  chassis.setPose(-36, 0, chassis.getPose().theta-90);
  
  chassis.moveToPoint(24, 1, 3000, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9}, true);
  pros::delay(250);
  Loader.extend();
  pros::delay(350);
  Loader.retract();
  pros::delay(400);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading( 280-90, 1000, {.maxSpeed = 127}, false);


  //moving to long goal 2
  chassis.moveToPose(36 , -24,270-90, 1500, {.forwards = true, .horizontalDrift = 8, .lead = 0, . minSpeed = 90, .earlyExitRange =15}, false);

  double yhere2 = chassis.getPose().y;
  ///////////SECOND LONG GOAL 4 BLOCKS///////////////////////
  chassis.moveToPoint(0, yhere2, 1000, {.forwards = false, .minSpeed = 100, .earlyExitRange = 6},false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 6 blocks
  pros::delay(1300);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  
  ///into loader
  chassis.moveToPoint(-38, yhere2, 1000, {.forwards = true}, false);
  pros::delay(300);
  Intake2.brake();


  //   //////////////////////////MID GOAL 3 BLOCKS//////////////////////////////
  chassis.moveToPoint(10, 45, 2500, {.forwards = false, .minSpeed = 120, .earlyExitRange = 13},false);
  pto.setDriveMode(DRIVE_4_MOTOR);
  Midgoal.extend();
  DrivePTO.move(-127);
  IntakePTO.move(85);
  pros::delay(2000);
  Midgoal.retract();
  IntakePTO.brake();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
}


void skills() {
  Intake2.move(127);
  float startx = chassis.getPose().x;
  chassis.moveToPoint(0, -36, 1000, {.forwards = false}, true);
  pros::delay(450);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);

  /////////////////////// MATCH LOADER//////////////////////////////////
  chassis.moveToPoint(-12, -39.5, 1000, {.forwards = true, .maxSpeed = 55},
                      false); /// into match loader
  pros::Task::delay(950);
  chassis.moveToPoint(-14, -39.5, 800, {.forwards = true},
                      false); /// into match loader
  pros::delay(300);
  // chassis.moveToPoint(0, -38, 1500, {.forwards = false}, false);
  // Intake2.brake();
  // chassis.turnToHeading(315, 1000);
  chassis.moveToPoint(
      13, -55.5, 1500,
      {.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5}, false);

  ///////////////////////////ACROSS FIELD//////////////////////////////
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  Intake2.brake();
  chassis.moveToPoint(73, -53.5, 1800, {.forwards = false}, false);
  chassis.moveToPoint(88, -37.5, 1700, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(58, -34, 1100, {.forwards = false}, false); //-31.5
  // pros::delay(200);
  float yhere = chassis.getPose().y;
  // chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);

  /////////////////////////SCORE LONG GOAL 7
  /// BLOCKS//////////////////////////////
  chassis.cancelMotion();
  Loader.extend();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(2200);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  // chassis.setPose(65, -34, 90);

  ///////////////////////////MATCH LOADER 2/////////////////////////////////////
  // chassis.moveToPoint(80, -30, 1500, {.forwards = true, .minSpeed =90,
  // .earlyExitRange = 9.5}, false);//////AT LONG GOAL SIDE
  // chassis.turnToHeading(90, 700, {.maxSpeed =127}, false);

  chassis.moveToPoint(101, yhere + 0.3, 1500,
                      {.forwards = true, .maxSpeed = 60},
                      false); //////AT LONG GOAL SIDE //-31
  chassis.moveToPoint(108.5, yhere, 1500, {.forwards = true, .maxSpeed = 127},
                      false); //////AT LONG GOAL SIDE //-31
  pros::delay(450);
  chassis.moveToPoint(64, yhere, 1500, {.forwards = false},
                      false); //////AT LONG GOAL SIDE // -31.5

  /////////////////////////SCORE LONG GOAL 6
  /// BLOCKS//////////////////////////////
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(80); // outakes into far long goal 3 blocks
  pros::delay(2500);
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  /////////////////////GOING TO THE NEXT MATCH LOADER 3///across field////
  /// 3//////////////////////////
  chassis.moveToPoint(80, yhere, 900, {.forwards = true}, false);
  chassis.turnToHeading(180, 800, {.maxSpeed = 127}, false);
  float xhere = chassis.getPose().x;
  // chassis.moveToPoint(81, 59, 2500, {.forwards = false}, false);
  chassis.moveToPoint(xhere, 60, 2500, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(60, 59, 1500, {.forwards = false}, false);
  yhere = chassis.getPose().y;
  Intake2.move(127);

  ////////////////////Match Loader 3/////////////////////////////
  chassis.moveToPoint(106, yhere - 2, 1000, {.forwards = true, .maxSpeed = 55},
                      false); ////into match loader
  chassis.moveToPoint(118, yhere, 1000, {.forwards = true, .maxSpeed = 60},
                      false); ////into match loader
  pros::delay(950);
  chassis.moveToPoint(120, yhere, 800, {.forwards = true},
                      false); ////into match loader

  //////////////////////////SET UP TO OTHER SIDE//////////////////////////////
  chassis.moveToPoint(80, 78, 1100, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  chassis.moveToPoint(15, 83, 1800, {.forwards = false}, false);
  chassis.moveToPoint(startx + 6, 69, 1500, {.forwards = false}, false);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(
      37.5, yhere - 1, 1500,
      {.forwards = false}, ///// note make the y a numerical value
      false);              ////long goal side
  yhere = chassis.getPose().y;
  Loader.extend();
  // yhere = chassis.getPose().y;

  // /////////////////////////SCORE LONG GOAL
  // 6//////////////////////////////////////
  // BLOCKS//////////////////////////////

  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(2400);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  // ///////////////////////////MATCH LOADER 4
  // /////////////////////////////////////
  chassis.moveToPoint(-10.5, yhere, 1500, {.forwards = true, .maxSpeed = 60},
                      false); ////long goal side
  pros::delay(500);
  chassis.moveToPoint(-15, yhere, 1500, {.forwards = true, .maxSpeed = 60},
                      false); ////long goal side
  pros::delay(950);
  chassis.moveToPoint(36.5, yhere - 0.5, 1500, {.forwards = false},
                      false); ////long goal side

  ////////////////////Score////////////////
  Loader.retract();
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(80); // outakes into far long goal 3 blocks
  pros::delay(2400);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  ////////////////////////////over park barriar//////////////////////////////
  chassis.moveToPoint(4, yhere, 800,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 9},
                      false);
  chassis.turnToHeading(225, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPose(-20, 25, 360, 1100,
                     {.forwards = true, .lead = 0.8, .minSpeed = 110}, true);
  pros::delay(700);
  Loader.extend();
  chassis.waitUntilDone();
  DrivePTO.brake();
  IntakePTO.brake();
  pto.setDriveMode(DRIVE_8_MOTOR);
  Drivetrainall.move(127);
  pros::delay(700);
  Drivetrainall.brake();
  Loader.retract();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Intake2.move(127);
}