//Includes
#include <Servo.h>

//Magic Numbers
const int SERVO_PIN = 11;
const int SERVO_MIN_ANGLE = 0;
const int SERVO_MAX_ANGLE = 90;

//Variables
Servo servo;
int servoDirection = 1;

//Functions
void servoSetup() {
  servo.attach(SERVO_PIN);
  writeServo(SERVO_MIN_ANGLE);
}

void writeServo (int hoek) {
  servo.write(hoek);
}
