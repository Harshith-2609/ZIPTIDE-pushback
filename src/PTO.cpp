
#include "main.h"
#include "PTO.h"

PTOManager::PTOManager(std::vector<pros::Motor*> leftMotors,
                       std::vector<pros::Motor*> rightMotors,
                       uint8_t drivePTOPort,
                       uint8_t intakePTOPort)
    : leftAll(leftMotors), 
      rightAll(rightMotors),
      drivePiston(drivePTOPort), 
      intakePiston(intakePTOPort),
      currentDriveMode(DRIVE_6_MOTOR) {}

DriveMode PTOManager::setDriveMode(DriveMode targetMode) {
    if(targetMode == currentDriveMode) return currentDriveMode;

    switch(targetMode) {
        case DRIVE_4_MOTOR:
            drivePiston.set_value(true);   // retract drive PTO
            intakePiston.set_value(false); // retract intake PTO
            break;
        case DRIVE_6_MOTOR:
            drivePiston.set_value(false);  // extend drive PTO
            intakePiston.set_value(false);
            break;
        case DRIVE_8_MOTOR:
            drivePiston.set_value(false);
            intakePiston.set_value(true);  // extend intake PTO
            break;
    }
    
    pros::delay(100);  // Wait for pistons to actuate
    currentDriveMode = targetMode;
    return currentDriveMode;
}

DriveMode PTOManager::getCurrentDriveMode() const {
    return currentDriveMode;
}

std::vector<pros::Motor*> PTOManager::getActiveLeftMotors() const {
    switch(currentDriveMode) {
        case DRIVE_4_MOTOR:
            return {leftAll[0], leftAll[1]};
        case DRIVE_6_MOTOR:
            return {leftAll[0], leftAll[1], leftAll[2]};
        case DRIVE_8_MOTOR:
            return {leftAll[0], leftAll[1], leftAll[2], leftAll[3]}; 
    }
    return {leftAll[0], leftAll[1]}; // fallback
}

std::vector<pros::Motor*> PTOManager::getActiveRightMotors() const {
    switch(currentDriveMode) {
        case DRIVE_4_MOTOR:
            return {rightAll[0], rightAll[1]};
        case DRIVE_6_MOTOR:
            return {rightAll[0], rightAll[1], rightAll[2]};
        case DRIVE_8_MOTOR:
            return {rightAll[0], rightAll[1], rightAll[2], rightAll[3]}; 
    }
    return {rightAll[0], rightAll[1]}; // fallback
}