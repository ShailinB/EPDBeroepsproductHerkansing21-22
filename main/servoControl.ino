//Includes
#include <Servo.h>

//Magic Numbers
const int SERVO_PIN = 11;
const int SERVO_MIN_ANGLE = 0;
const int SERVO_MAX_ANGLE = 90;

//Variables
Servo servo;
//int servoDirection = 1;

//Variables for opening/closing slagboom
int servoCurrentAngle;

// Timer dode tijd
unsigned long slagboomTimer;
const int STEPSPEED = 20;

void servoSetup() {

  // Init timers
  slagboomTimer = timerSetup(STEPSPEED);
  slagboomTimer = timerReset();

  servoStart();
  servoWrite(SERVO_MIN_ANGLE);
//  servoStop();
}

void servoWrite(int angle) {
  servo.write(angle);
}

void servoStop() {
  servo.detach();
}

void servoStart() {
  servo.attach(SERVO_PIN);
}

boolean isServoOpen() {
  return servoCurrentAngle == SERVO_MAX_ANGLE;
}

boolean isServoClosed() {
  return servoCurrentAngle == SERVO_MIN_ANGLE;
}

void servoOpen() {
  if (timerIsPassed(slagboomTimer, STEPSPEED)) {
    slagboomTimer = timerReset();
    servoWrite(servoCurrentAngle);
    servoCurrentAngle++;
  }
}

void servoClose() {
  if (timerIsPassed(slagboomTimer, STEPSPEED)) {
    slagboomTimer = timerReset();
    servoWrite(servoCurrentAngle);
    servoCurrentAngle--;
  }
}

int getServoAngle() {
  return servo.read();
}
