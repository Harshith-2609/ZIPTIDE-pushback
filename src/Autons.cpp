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

void skills(){
  Intake2.move(127);
  chassis.moveToPoint(0, -35, 1000, {.forwards = false}, true);
  pros::delay(450);
  Loader.extend();
  chassis.waitUntilDone();
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);


  /////////////////////// MATCH LOADER//////////////////////////////////
  chassis.moveToPoint(-12, -38, 1000, {.forwards = true}, false); /// into match loader
  pros::Task::delay(2000);
  // chassis.moveToPoint(0, -38, 1500, {.forwards = false}, false); 
  // Intake2.brake();
  // chassis.turnToHeading(315, 1000);
  chassis.moveToPoint(13, -53.5, 1500, {.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5}, false);
  Intake2.brake();

  ///////////////////////////ACROSS FIELD//////////////////////////////
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.setPose(0, 0, 0);
  Loader.retract();
  chassis.moveToPoint(0, -64, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 5.5}, false);
  chassis.moveToPoint(17, -73, 1000, {.forwards = false, .minSpeed = 90, .earlyExitRange = 9.5}, false);
  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(18, -45, 1000, {.forwards = false}, false);

  /////////////////////////SCORE LONG GOAL 7 BLOCKS//////////////////////////////
  chassis.cancelMotion();
  Loader.extend();
  pto.setDriveMode(DRIVE_4_MOTOR);
  DrivePTO.move(-127); // outakes into far long goal 3 blocks
  Intake2.move(-127);
  pros::delay(100);
  Intake2.move(127);
  DrivePTO.move(127); // outakes into far long goal 3 blocks
  pros::delay(3000);
  DrivePTO.brake();
  pto.setDriveMode(DRIVE_6_MOTOR);



  ///////////////////////////MATCH LOADER 2/////////////////////////////////////
  chassis.moveToPoint(16, -84, 1500, {.forwards = true, .maxSpeed = 127}, false);//////AT LONG GOAL SIDE
  pros::delay(2000);
  chassis.moveToPoint(15, -53, 1500, {.forwards = false}, false);//////AT LONG GOAL SIDE



  /////////////////////////SCORE LONG GOAL 6 BLOCKS//////////////////////////////
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

  /////////////////////GOING TO THE NEXT MATCH LOADER 3//////////////////////////
  chassis.moveToPoint(13, -70, 1500, {.forwards = true}, false);
  chassis.turnToHeading(270, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(113, -70, 3500, {.forwards = false}, true); 
  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false);
  Intake2.move(127);
  chassis.moveToPoint(113, -85, 1000, {.forwards = true}, false);////into match loader
  pros::delay(2000);


  ///////////////////////////SET UP TO OTHER SIDE//////////////////////////////
  chassis.moveToPoint(113, -70, 1000, {.forwards = false}, false);
  chassis.turnToHeading(225, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(125, -61, 1000, {.forwards = false}, false);
  chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(125, 18, 2500, {.forwards = false}, true);
  Loader.retract();
  chassis.waitUntilDone();
  chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(107, 18, 1500, {.forwards = false}, false);////long goal side
  chassis.turnToHeading(0, 1000, {.maxSpeed = 127}, false);
  chassis.moveToPoint(107, -5, 1500, {.forwards = false}, true);////long goal side
  Loader.extend();
  chassis.waitUntilDone();

  // /////////////////////////SCORE LONG GOAL 6 BLOCKS//////////////////////////////

  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(-127); // outakes into far long goal 3 blocks
  // Intake2.move(-127);
  // pros::delay(100);
  // Intake2.move(127);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks
  // pros::delay(3000);
  // DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);

  // ///////////////////////////MATCH LOADER 4 /////////////////////////////////////
  // chassis.moveToPoint(107, 35, 1500, {.forwards = true}, false);////long goal side
  // pros::delay(2000);
  // chassis.moveToPoint(107, -5, 1500, {.forwards = false}, false);////long goal side


  // /////////////////////////SCORE LONG GOAL 6 BLOCKS//////////////////////////////
  // chassis.cancelMotion();
  // pto.setDriveMode(DRIVE_4_MOTOR);
  // DrivePTO.move(-127); // outakes into far long goal 3 blocks
  // Intake2.move(-127);
  // pros::delay(100);
  // Intake2.move(127);
  // DrivePTO.move(127); // outakes into far long goal 3 blocks
  // pros::delay(3000);
  // DrivePTO.brake();
  // pto.setDriveMode(DRIVE_6_MOTOR);

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

void QualsRight7Block()
{
    ////Going to start the robot at angle 0
    Intake2.move(127); 
    chassis.turnToHeading(43, 1000, {.maxSpeed = 127}, false);// initial turn to the 3 blocks 

    chassis.moveToPoint(13, 30, 5000, {.forwards = false}, false);

    chassis.turnToHeading(135, 1000, {.maxSpeed = 127}, false);

    chassis.moveToPoint(37, 5, 5000, {.forwards = false}, false);

    chassis.cancelMotion();
    Loader.extend();
    pto.setDriveMode(DRIVE_4_MOTOR);
    chassis.turnToHeading(180, 1000, {.maxSpeed = 127}, false); /// turns to face the match loader

    chassis.moveToPoint(38, -14, 5000, {.forwards = false}, false);
    pros::delay(800);   
    chassis.moveToPoint(37, 30, 5000, {.forwards = false}, false);
    DrivePTO.move(127); // outakes into far long goal 7 blocks

}




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

