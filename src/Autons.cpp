#include "Autons.h"
#include "Motion.h"
#include "PTO.h"
#include "main.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cmath>
using namespace pros;

/// Intake ptos are front ones, and driveptos are back ones
/// Intake2 and IntakePto are the same motors
/// Intake4 is all of the PTOS
//drivepto is the outake

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

void skills(){
  Intake2.move(127);
  chassis.moveToPoint(0, -36, 1000, {.forwards = false}, true);
  pros::delay(450);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);

  /////////////////////// MATCH LOADER//////////////////////////////////
  chassis.moveToPoint(-12, -38, 1000, {.forwards = true, .maxSpeed = 55},
                      false); /// into match loader
  pros::Task::delay(1000);
  chassis.moveToPoint(-12.5, -39, 800, {.forwards = true},
                      false); /// into match loader
  pros::delay(300);
  // chassis.moveToPoint(0, -38, 1500, {.forwards = false}, false);
  // Intake2.brake();
  // chassis.turnToHeading(315, 1000);
  chassis.moveToPoint(
      13, -54.5, 1500,
      {.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5}, false);

  ///////////////////////////ACROSS FIELD//////////////////////////////
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  Intake2.brake();
  chassis.moveToPoint(73, -53.5, 1800, {.forwards = false}, false);
  chassis.moveToPoint(88, -35, 1000, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(58, -35, 1100, {.forwards = false}, false); //-31.5
  pros::delay(400);
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
  pros::delay(2500);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  // chassis.setPose(65, -34, 90);

  ///////////////////////////MATCH LOADER 2/////////////////////////////////////
  // chassis.moveToPoint(80, -30, 1500, {.forwards = true, .minSpeed =90,
  // .earlyExitRange = 9.5}, false);//////AT LONG GOAL SIDE
  // chassis.turnToHeading(90, 700, {.maxSpeed =127}, false);

  chassis.moveToPoint(97, yhere, 1500, {.forwards = true, .maxSpeed = 65},
                      false); //////AT LONG GOAL SIDE //-31
  chassis.moveToPoint(102, yhere, 1500, {.forwards = true},
                      false); //////AT LONG GOAL SIDE //-31
  pros::delay(500);
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
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(3000);
  DrivePTO.brake();
  Intake2.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);

  /////////////////////GOING TO THE NEXT MATCH LOADER
  /// 3//////////////////////////
  chassis.moveToPoint(82, yhere, 1500, {.forwards = true}, false);
  chassis.turnToHeading(190, 1500, {.maxSpeed = 127}, false);
  float xhere = chassis.getPose().x;
  //chassis.moveToPoint(81, 59, 2500, {.forwards = false}, false);
  chassis.moveToPoint(xhere, 59, 2500, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(60, 59, 1500, {.forwards = false}, false); 
  yhere = chassis.getPose().y;
  Intake2.move(127);
  chassis.moveToPoint(99, yhere, 1000, {.forwards = true, .maxSpeed = 65},
                      false); ////into match loader
  pros::delay(800);
  chassis.moveToPoint(104, yhere, 700, {.forwards = true},
                      false); ////into match loader
  pros::delay(3000);

  //////////////////////////SET UP TO OTHER SIDE//////////////////////////////
  chassis.moveToPoint(80, 75, 1000, {.forwards = false}, false);
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  Loader.retract();
  chassis.moveToPoint(12, 77, 1000, {.forwards = false}, false);
  chassis.moveToPoint(8, 51, 2500, {.forwards = false}, false);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(37, yhere - 10, 1500, {.forwards = false}, ///// note make the y a numerical value
                      false); ////long goal side
  yhere = chassis.getPose().y;
  Loader.extend();
  // yhere = chassis.getPose().y;

  // /////////////////////////SCORE LONG GOAL 6
  // BLOCKS//////////////////////////////

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

  // ///////////////////////////MATCH LOADER 4
  // /////////////////////////////////////
  chassis.moveToPoint(-6, yhere, 1500, {.forwards = true, .maxSpeed = 70},
                      false); ////long goal side
  pros::delay(500);
  chassis.moveToPoint(-11, yhere, 1500, {.forwards = true},
                      false); ////long goal side
  pros::delay(1000);
  chassis.moveToPoint(34, yhere, 1500, {.forwards = false},
                      false); ////long goal side

  ////////////////////Score////////////////
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

  ////////////////////////////over park barriar//////////////////////////////
  chassis.moveToPoint(28, yhere, 1500, {.forwards = true}, false);
  chassis.moveToPoint(-18, 25, 1500, {.forwards = true}, false);
  Drivetrain.move(127);
  pros::delay(1000);
  Drivetrain.brake();


}

void SAWP(){
  ///////////////////////////PUSH//////////////////////////////
  chassis.moveToPoint(0, -35, 1000, {.forwards = false}, true);
  Intake2.move(127);
  pros::delay(300);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);


/////////////////////// MATCH LOADER//////////////////////////////////

  chassis.moveToPoint(-15, -35, 1000); /// into match loader
  pros::Task::delay(800);
  chassis.moveToPoint(25, -35, 1500, {.forwards = false}, false); /// long goal
  

  ///////////////////////////LONG GOAL 4 BLOCKS//////////////////////////////
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();


  ///////////////////////////FIRST 3 BLOCKS//////////////////////////////
  chassis.swingToHeading(20, lemlib::DriveSide::RIGHT, 1500, {.maxSpeed = 127});
  chassis.moveToPoint(27, -20, 1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5}, true); // 3 bloacks
  pros::delay(600);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(0, 1000, {.maxSpeed = 127}, false);
  Loader.retract();


  ///////////////////////////SECOND 3 BLOCKS//////////////////////////////
  chassis.moveToPoint(25, 22, 1500, {.forwards = true, .minSpeed = 90, .earlyExitRange = 9.5},true); 
  pros::delay(800);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(315, 1000, {.maxSpeed = 127}, false);



  //////////////////////////MID GOAL 2 BLOCKS//////////////////////////////
  chassis.moveToPoint(35, 10, 1200, {.forwards = false},false); 
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  Intake2.move(-127);
  DrivePTO.move(-127);
  pros::delay(200);
  Midgoal.retract();
  IntakePTO.move(75);
  DrivePTO.move(-55); // outakes into far long goal 3 blocks
  pros::delay(900);
  IntakePTO.brake();  
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();



 
  chassis.moveToPoint(4, 48, 1000, {.forwards = true}, true);
  Midgoal.extend();
  pros::delay(300);
  IntakePTO.move(127);
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);


  ///////////SECOND LONG GOAL 4 BLOCKS///////////////////////
  chassis.moveToPoint(25, 47, 1500, {.forwards = false}, false); /// long goal
  chassis.cancelMotion();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(1000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);
  Loader.retract();

}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

