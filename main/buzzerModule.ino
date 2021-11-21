
// Buzzer setup
const int BUZZER_PIN = 12;
const int VOLUME = 1000;

// Intervals
const int INTERVAL_DOORLOPEN = 200;
const int INTERVAL_DOORLOPEN_PAUZE = 1500;
const int INTERVAL_LOPEN = 750;
const int INTERVAL_HALT = 1500;

// Timers
unsigned long timer_buzzer;

// Rhythm variables
int buzzCount;

void buzzerSetup() {
  pinMode(BUZZER_PIN, OUTPUT);
  timer_buzzer = timerSetup(INTERVAL_DOORLOPEN);
  resetBuzzerCount();
}

void buzzer_doorlopen(int wantedTicks) {
  if (buzzCount >= wantedTicks) {
    noTone(BUZZER_PIN);
    if (timerIsPassed(timer_buzzer, INTERVAL_DOORLOPEN_PAUZE)) {
      resetBuzzerCount();
      timer_buzzer = timerReset();
    }
  }
  noTone(BUZZER_PIN);
  if (timerIsPassed(timer_buzzer, INTERVAL_DOORLOPEN) && buzzCount < wantedTicks) {
    tone(BUZZER_PIN, VOLUME);
    buzzCount++;
    timer_buzzer = timerReset();
  }
}

void buzzer_halt() {
  noTone(BUZZER_PIN);
  if (timerIsPassed(timer_buzzer, INTERVAL_HALT)) {
    tone(BUZZER_PIN, VOLUME);
    timer_buzzer = timerReset();
  }
}

void buzzer_lopen() {
  noTone(BUZZER_PIN);
  if (timerIsPassed(timer_buzzer, INTERVAL_LOPEN)) {
    tone(BUZZER_PIN, VOLUME);
    timer_buzzer = timerReset();
  }
}

void resetBuzzerCount() {
  buzzCount = 0;
}
