#include "main.h"
/*
void vision_align(int targetSignature, int driveSpeed, int timeout) {
    uint32_t startTime = pros::millis();
    float kP = 0.6; // Tune this: higher = sharper turns, lower = smoother
    int targetX = 160; // Center of the AI Vision Sensor
    int deadzone = 5;

    while (pros::millis() - startTime < timeout) {
        // Take snapshot of the specific signature
        pros::vision_object_s_t object = ai_sensor.get_by_id(0);

        if (ai_sensor.objectCount > 0) {
            // Use the largest object (index 0)
            int currentX = ai_sensor.objects[0].centerX;
            int error = targetX - currentX;

            // If we are "close enough," just drive straight
            if (abs(error) < deadzone) {
                chassis.tank(driveSpeed, driveSpeed);
            } else {
                float correction = error * kP;
                // LemLib tank takes (left, right) voltages/velocities
                chassis.tank(driveSpeed + correction, driveSpeed - correction);
            }
        } else {
            // If lost, stop motors to avoid drifting off
            chassis.tank(0, 0);
        }

        pros::delay(20);
    }
    chassis.setPose(0, 0, 0); // Optional: Reset local coords if needed
    chassis.tank(0, 0);       // Brake at the end
}*/