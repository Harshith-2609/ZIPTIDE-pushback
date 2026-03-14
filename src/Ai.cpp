/*#include "main.h"

void vision_align(int targetID, int driveSpeed, int timeout) {
    uint32_t startTime = pros::millis();
    float kP = 0.6; 
    int targetX = 0; 
    int deadzone = 5;

    while (pros::millis() - startTime < timeout) {
        // CORRECT: Change the type of 'obj' to 'pros::aivision_object_s_t'
        // Also use the correct method 'get_object_by_id'
        pros::aivision_object_s_t obj = ai_sensor.get_object_by_id(targetID);

        // CORRECT: Use the .exists boolean property
        if (obj.exists) { 
            
            // CORRECT: Use 'x_middle_coord' for AI Vision
            int currentX = obj.x_middle_coord; 
            int error = targetX - currentX;

            if (abs(error) < deadzone) {
                chassis.tank(driveSpeed, driveSpeed);
            } else {
                float correction = error * kP;
                chassis.tank(driveSpeed + correction, driveSpeed - correction);
            }
        } else {
            chassis.tank(0, 0); 
        }

        pros::delay(20);
    }
    chassis.tank(0, 0); 
}*/