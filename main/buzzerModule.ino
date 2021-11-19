
// Buzzer setup
const int PIN_BUZZER = 12;
const int VOLUME = 1000000; //KHz

// Intervals
const int INTERVAL_TIK_LOPEN = 200;
const int INTERVAL_STILTE_LOPEN = 1500;
const int INTERVAL_LOPEN = 750;
const int INTERVAL_NIET_LOPEN = 1.5 * 1000;//1.5sec

// Timers
unsigned long buzzerTimer;

// Rhythm variables
int buzzCount;

void buzzerSetup() {
  pinMode(PIN_BUZZER, OUTPUT);
  buzzerTimer = timerSetup(INTERVAL_TIK_LOPEN);
  resetBuzzerCount();
}

void buzzer_doorlopen(int wantedTicks) {
  if (buzzCount >= wantedTicks) {
    noTone(PIN_BUZZER);
    if (timerIsPassed(buzzerTimer, INTERVAL_STILTE_LOPEN)) {
      resetBuzzerCount();
      buzzerTimer = timerReset();
    }
  }
  noTone(PIN_BUZZER);
  if (timerIsPassed(buzzerTimer, INTERVAL_TIK_LOPEN) && buzzCount < wantedTicks) {
//    Serial.print("Tick: ");
//    Serial.println(buzzCount);
    tone(PIN_BUZZER, VOLUME);
    buzzCount++;
    buzzerTimer = timerReset();
  }
}

void buzzer_halt() {
  noTone(PIN_BUZZER);
  if (timerIsPassed(buzzerTimer, INTERVAL_NIET_LOPEN)) {
    tone(PIN_BUZZER, VOLUME);
    buzzerTimer = timerReset();
  }
}

void buzzer_lopen() {
  noTone(PIN_BUZZER);
  if (timerIsPassed(buzzerTimer, INTERVAL_LOPEN)) {
    tone(PIN_BUZZER, VOLUME);
    buzzerTimer = timerReset();
  }
}

void resetBuzzerCount() {
  buzzCount = 0;
}
