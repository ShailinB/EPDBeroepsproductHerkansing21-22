
// State
int buzzerState;

const int STATE_BUZZER_HALT = 0;
const int STATE_BUZZER_LOPEN = 1;
const int STATE_BUZZER_DOORLOPEN = 2;

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

// Testing
boolean buzzTest = false;
unsigned long timer_buzzTest;
const int INTERVAL_BUZZTEST = 3000;

void buzzerSetup() {
  pinMode(BUZZER_PIN, OUTPUT);
  timer_buzzer = timerSetup(INTERVAL_DOORLOPEN);
  resetBuzzerCount();
}

void buzzer_doorlopen(int wantedTicks) {
  buzzerState = STATE_BUZZER_DOORLOPEN;
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
  buzzerState = STATE_BUZZER_HALT;
  noTone(BUZZER_PIN);
  if (timerIsPassed(timer_buzzer, INTERVAL_HALT)) {
    tone(BUZZER_PIN, VOLUME);
    timer_buzzer = timerReset();
  }
}

void buzzer_lopen() {
  buzzerState = STATE_BUZZER_LOPEN;
  noTone(BUZZER_PIN);
  if (timerIsPassed(timer_buzzer, INTERVAL_LOPEN)) {
    tone(BUZZER_PIN, VOLUME);
    timer_buzzer = timerReset();
  }
}

boolean isBuzzTestCompleted() {
  return buzzTest;
}

void buzzTest_setup() {
  timer_buzzTest = timerReset();
  buzzTest = false;
  noTone(BUZZER_PIN);
}
void buzzer_test() {
  while(!buzzTest) {
    tone(BUZZER_PIN, VOLUME);
    if(timerIsPassed(timer_buzzTest, INTERVAL_BUZZTEST)) {
      Serial.println("Im here");
      timer_buzzTest = timerReset();
      buzzTest = true;
    }
  }
  noTone(BUZZER_PIN);
}

void resetBuzzerCount() {
  buzzCount = 0;
}

// Buzzer states

boolean isBuzzerOnHalt() {
  return buzzerState == STATE_BUZZER_HALT;
}
