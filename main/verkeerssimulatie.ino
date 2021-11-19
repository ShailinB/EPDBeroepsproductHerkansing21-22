
void vsSetup() {
    serialSetup();
    buttonSetup();
    buzzerSetup();
    ledControlSetup();
    servoSetup();
    shiftRegisterSetup();
    initTimers();
}

void vsLoop() {
    kruispunt();
}
