#include "Autons.h"
#include "Motion.h"
#include "PTO.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cmath>
using namespace pros;

/// Intake ptos are front ones, and driveptos are back ones
/// Intake2 and IntakePto are the same motors
/// Intake4 is all of the PTOS
//drivepto is the outake
void test() {
  //driveForwardPID8(24, 2000, 8, 0, 20);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
}

void wingRIGHT() {

  Intake2.move(127);
  chassis.moveToPoint(8, 22, 1000, {.forwards = true}, true);
  delay(550);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(315, 1000, {.maxSpeed = 127}, false);

  chassis.moveToPoint(30, 0, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 5.5}, true);

  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false);

  chassis.moveToPoint(35, 27, 1000, {.forwards = false}, false);//, .minSpeed = 90, .earlyExitRange = 9.5
  
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();
  
  chassis.swingToHeading(20, lemlib::DriveSide::LEFT, 1500, {.maxSpeed = 127});
  chassis.turnToHeading(345, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(40, 49, 1000);
  chassis.turnToHeading(15, 500);

}

void wingLEFT() {
  Intake2.move(127);

  chassis.moveToPoint(-8, 22, 1000, {.forwards = true}, true);
  delay(550);
  Loader.extend();
  chassis.waitUntilDone();

  chassis.turnToHeading(45, 1000, {.maxSpeed = 127}, false); // 315 -> 45

  chassis.moveToPoint(-30, 0, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 5.5}, true);

  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false); // 180 -> 180

  chassis.moveToPoint(-35, 27, 1000, {.forwards = false}, false);

  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); 
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

  chassis.swingToHeading(340, lemlib::DriveSide::RIGHT, 1500, {.maxSpeed = 127}); // 20 -> 340, LEFT -> RIGHT

  chassis.turnToHeading(15, 1000, {.maxSpeed = 127}, false); // 345 -> 15

  chassis.moveToPoint(-40, 49, 1000);

  chassis.turnToHeading(345, 500); 
}

void suck()// 3x4 blocks mid and long goal
{
    chassis.setPose(0,0,0);
    ///////////////////////////FIRST 3 BLOCKS//////////////////////////////
    Intake2.move(127);
    chassis.moveToPoint(-7, 37, 2000, {.forwards = true}, true);
    delay(700);//800
    Loader.extend();
    chassis.waitUntilDone();
    delay(500);

    chassis.turnToHeading(315, 1000, {.maxSpeed = 127}, false);/////turning to face the midgoal
    chassis.moveToPoint(6, 52, 2000, {.forwards = false}, false);///(40,10)
    //chassis.moveToPoint(35, 10, 1200, {.forwards = false},false); 
    chassis.cancelMotion();
    pto.setDriveMode(DRIVE_4_MOTOR);
    //Intake2.move(-127);
    //DrivePTO.move(-127);
    //delay(200);
    Midgoal.retract();
    IntakePTO.move(75);
    DrivePTO.move(-55); // outakes into far long goal 3 blocks
    delay(900);
    IntakePTO.brake();  
    DrivePTO.brake();
    pto.setDriveMode(DRIVE_6_MOTOR);


    chassis.moveToPoint(-31, 14, 2000, {.forwards = true}, false);//(6, 48)

    chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
    chassis.moveToPoint(-31.6, -7.6, 3000, {.forwards = true}, false);//(-16.7,50.5)
    chassis.moveToPoint(-31, 36, 2000, {.forwards = false}, false);///(28,50)
    chassis.cancelMotion();
    pto.setDriveMode(DRIVE_4_MOTOR);
    DrivePTO.move(127); // outakes into far long goal 3 blocks
    delay(1000);
    DrivePTO.brake();
    pto.setDriveMode(DRIVE_6_MOTOR);
    Loader.retract();

}

void scoring(){
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(3000);
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
  chassis.moveToPoint(-13.5, -39.5, 800, {.forwards = true},
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
  //pros::delay(200);
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
  chassis.moveToPoint(107, yhere, 1500, {.forwards = true, .maxSpeed = 127},
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
  chassis.moveToPoint( 80, yhere, 1500, {.forwards = true}, false);
  chassis.turnToHeading(180, 1500, {.maxSpeed = 127}, false);
  float xhere = chassis.getPose().x;
  // chassis.moveToPoint(81, 59, 2500, {.forwards = false}, false);
  chassis.moveToPoint(xhere, 60, 2500, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(60, 59, 1500, {.forwards = false}, false);
  yhere = chassis.getPose().y;
  Intake2.move(127);

  ////////////////////Match Loader 3/////////////////////////////
  chassis.moveToPoint(107, yhere - 0.5, 1000,
                      {.forwards = true, .maxSpeed = 60},
                      false); ////into match loader
  chassis.moveToPoint(118, yhere, 1000, {.forwards = true, .maxSpeed = 60},
                      false); ////into match loader
  pros::delay(950);
  chassis.moveToPoint(120, yhere, 800, {.forwards = true},
                      false); ////into match loader

  //////////////////////////SET UP TO OTHER SIDE//////////////////////////////
  chassis.moveToPoint(80, 78.5, 1000, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  chassis.moveToPoint(15, 81.5, 1800, {.forwards = false}, false);
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
  chassis.moveToPoint(-10.5, yhere + 0.5, 1500,
                      {.forwards = true, .maxSpeed = 60},
                      false); ////long goal side
  pros::delay(500);
  chassis.moveToPoint(-15, yhere, 1500, {.forwards = true, .maxSpeed = 60},
                      false); ////long goal side
  pros::delay(950);
  chassis.moveToPoint(37, yhere+1, 1500, {.forwards = false},
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


  ///////////MID GOAL 4 BLOCKS maybe??//////////////////////////////
  chassis.moveToPoint(-1, yhere, 1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5}, false);
  chassis.turnToHeading(135, 1000, {.minSpeed = 90, .earlyExitRange =20}, false);
  chassis.moveToPoint(27, 26, 1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5}, true);
  pros::delay(800);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(315, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(35, 8, 1200, {.forwards = false}, false);
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  Intake2.move(-127);
  DrivePTO.move(-127);
  pros::delay(200);
  Midgoal.retract();
  IntakePTO.move(85);
  DrivePTO.move(-85); // outakes into far long goal 3 blocks
  pros::delay(900);
  IntakePTO.brake();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

  
  ////////////////////////////over park barriar//////////////////////////////
  chassis.moveToPoint(2, yhere, 800,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5},
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
  pros::delay(800);
  Drivetrainall.brake();
  Loader.retract();
}

void SAWP() {
  ///////////////////////////PUSH//////////////////////////////
  Intake2.move(127);
  chassis.moveToPoint(0, 13, 1000, {.forwards = true, .minSpeed = 90, .earlyExitRange = 5},false);
  chassis.moveToPoint(0, -37.3, 1500, {.forwards = false}, true);
  pros::delay(450);
  Loader.extend();
  chassis.waitUntilDone();
  //pros::delay(200);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  double yhere = chassis.getPose().y;

  /////////////////////// MATCH LOADER//////////////////////////////////

  chassis.moveToPoint(-13.4, yhere, 900, {.forwards = true}, false); /// into match loader
  pros::Task::delay(185);
  chassis.moveToPoint(23, yhere-1.5, 1000, {.forwards = false}, false); /// long goal
  Intake2.brake();

  ///////////////////////////LONG GOAL 5 BLOCKS//////////////////////////////
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 5 blocks
  Intake2.move(127);
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

  ///////////////////////////FIRST 3 BLOCKS//////////////////////////////
  chassis.swingToHeading(
      30, lemlib::DriveSide::RIGHT, 1500,
      {.maxSpeed = 127, .minSpeed = 90, .earlyExitRange = 10.5});
  chassis.moveToPoint(34, -22.5, 1500,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 10},
                      false); // 3 bloacks
 pros::delay(350);
 Loader.extend();
 chassis.waitUntilDone();
  chassis.turnToHeading(360, 800, {.maxSpeed = 127}, false);
 Loader.retract();
  double xhere = chassis.getPose().x;

  ///////////////////////////SECOND 3 BLOCKS//////////////////////////////
  chassis.moveToPoint(xhere-0.2, 12, 1500,
                      {.forwards = true, .minSpeed = 90, .earlyExitRange = 10},
                      true);
  pros::delay(700);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(320, 1000, {.maxSpeed = 127}, false);

  //////////////////////////MID GOAL 2 BLOCKS//////////////////////////////
  
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  Drivetrain.move(-127);
  pros::delay(500);
  Drivetrain.brake();
  Intake2.move(-127);
  DrivePTO.move(-127);
  pros::delay(100);
  Midgoal.extend();
  DrivePTO.move(-85); // outakes into far long goal 3 blocks
  IntakePTO.move(85);
  pros::delay(800);
  IntakePTO.brake();
  Midgoal.retract();
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Midgoal.extend();
  // chassis.turnToHeading(300, 1000, {.maxSpeed = 127}, false);

  chassis.moveToPoint(-8, 39, 2000, {.forwards = true, .minSpeed = 85, .earlyExitRange = 11.5}, true);
  Loader.retract();
  pros::delay(300);
  IntakePTO.move(127);
  chassis.waitUntilDone();
  pros::delay(200);
  chassis.turnToHeading(270, 900, {.maxSpeed = 127}, false);
  Intake2.brake();
  Midgoal.retract();

  ///////////SECOND LONG GOAL 4 BLOCKS///////////////////////
  pto.setDriveMode(DRIVE_4_MOTOR);
  Drivetrain.move(-127);
  pros::delay(500);
  Drivetrain.brake();
  //chassis.moveToPoint(25, 39, 800, {.forwards = false}, false); /// long goal
  chassis.cancelMotion();
  //pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  Intake2.move(127);
  pros::delay(1000);
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();
}