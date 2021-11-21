//Includes
#include <Servo.h>

//Pin diagram
Servo servo;
const int SERVO_PIN = 11;

//Servo bounds
const int SERVO_MIN_ANGLE = 0;
const int SERVO_MAX_ANGLE = 90;

//Variables for opening/closing slagboom
int servoCurrentAngle;

// Timer dode tijd
unsigned long timer_slagboom;
const int STEPSPEED = 20;

void servoSetup() {

  // Init timers
  timer_slagboom = timerSetup(STEPSPEED);
  timer_slagboom = timerReset();

  servoStart();
  servoWrite(SERVO_MIN_ANGLE);
  servoStop();
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
  if (timerIsPassed(timer_slagboom, STEPSPEED)) {
    timer_slagboom = timerReset();
    servoWrite(servoCurrentAngle);
    servoCurrentAngle++;
  }
}

void servoClose() {
  if (timerIsPassed(timer_slagboom, STEPSPEED)) {
    timer_slagboom = timerReset();
    servoWrite(servoCurrentAngle);
    servoCurrentAngle--;
  }
}

int getServoAngle() {
  return servo.read();
}
