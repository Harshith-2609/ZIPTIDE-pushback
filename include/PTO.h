#pragma once
#include "api.h"

using namespace pros;

enum DriveMode {
    DRIVE_4_MOTOR,
    DRIVE_6_MOTOR,
    DRIVE_8_MOTOR
};

class PTOManager {
private:
    std::vector<Motor*> leftAll;
    std::vector<Motor*> rightAll;
    adi::DigitalOut drivePiston;
    adi::DigitalOut intakePiston;
    DriveMode currentDriveMode;

public:
    PTOManager(std::vector<Motor*> leftMotors,
               std::vector<Motor*> rightMotors,
               uint8_t drivePTOPort,
               uint8_t intakePTOPort);
    
    DriveMode setDriveMode(DriveMode targetMode);
    DriveMode getCurrentDriveMode() const;
    
    std::vector<Motor*> getActiveLeftMotors() const;
    std::vector<Motor*> getActiveRightMotors() const;
};
