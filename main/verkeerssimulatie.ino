
void vsSetup() {
    serialSetup();
    buttonSetup();
    buzzerSetup();
    ledControlSetup();
    servoSetup();
    shiftRegisterSetup();
    kruispunt_setup();
}

void vsLoop() {
  buttonLoop();
  kruispunt();
}
