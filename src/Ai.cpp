/*#include "main.h"
struct VisionAlignConfig {
    float kP = 0.6;
    float kD = 0.1;
    int deadzone = 5;
    int maxSpeed = 127;
    int minSpeed = 20;
    int settleTime = 300; // ms inside deadzone before finishing
};
int clamp(int value, int minVal, int maxVal) {
    if (value > maxVal) return maxVal;
    if (value < minVal) return minVal;
    return value;
}
float applyMinSpeed(float value, int minSpeed) {
    if (value > 0 && value < minSpeed) return minSpeed;
    if (value < 0 && value > -minSpeed) return -minSpeed;
    return value;
}
void vision_align_advanced(int targetID, int baseSpeed, int timeout) {
    VisionAlignConfig config;
    int startTime = pros::millis();
    int lastTime = startTime;
    int targetX = 0; // center of screen
    int lastError = 0;
    uint32_t inDeadzoneStart = 0;
    bool inDeadzone = false;
    while (pros::millis() - startTime < timeout) {
        uint32_t currentTime = pros::millis();
        float deltaTime = (currentTime - lastTime) / 1000.0;
        pros::aivision_object_s_t obj = ai_sensor.get_object_by_id(targetID);
        if (obj.exists) {
            int currentX = obj.x_middle_coord;
            int error = targetX - currentX;
            if (abs(error) < config.deadzone) {
                if (!inDeadzone) {
                    inDeadzone = true;
                    inDeadzoneStart = currentTime;
                }
                if (currentTime - inDeadzoneStart > config.settleTime) {
                    break;
                }

                chassis.tank(baseSpeed, baseSpeed);
            } 
            else {
                inDeadzone = false;
                float derivative = (error - lastError) / deltaTime;
                float correction = (error * config.kP) + (derivative * config.kD);
                correction = clamp(correction, -config.maxSpeed, config.maxSpeed);
                correction = applyMinSpeed(correction, config.minSpeed);

                int leftPower  = clamp(baseSpeed + correction, -127, 127);
                int rightPower = clamp(baseSpeed - correction, -127, 127);

                chassis.tank(leftPower, rightPower);

                lastError = error;
            }
        } 
        else {
            chassis.tank(0, 0);
            chassis.tank(30, -30);
        }
        lastTime = currentTime;
        pros::delay(20);
    }
    chassis.tank(0, 0);
}*/