
unsigned long timerSetup(int interval) {
  return 0 - interval;
}

boolean timerIsPassed(unsigned long previous, int interval) {
  return millis() - previous >= interval;
}

unsigned long timerReset() {
  return millis();
}
