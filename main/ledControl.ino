
// Pin diagram stoplichten -------------------------------

const int LEDPINS [] = {13, 12, 8, 7, A5, A4};
const int LEDPINS_SIZE = 6;

void ledControlSetup() {
  for (int i = 0; i < LEDPINS_SIZE; i++) {
    pinMode(LEDPINS[i], OUTPUT);
  }
}

void ledControlAllLedOn() {
  for (int i = 0; i < LEDPINS_SIZE; i++) {
    digitalWrite(LEDPINS[i], HIGH);
  }
}

void ledControlAllLedOff() {
  for (int i = 0; i < LEDPINS_SIZE; i++) {
    digitalWrite(LEDPINS[i], LOW);
  }
}

void ledControlSetLedOn (int led) {
  for (int i = 0; i < LEDPINS_SIZE; i++) {
    if (LEDPINS[i] == led) {
      digitalWrite(LEDPINS[i], HIGH);
    }
  }
}

void ledControlSetLedOff (int led) {
  for (int i = 0; i < LEDPINS_SIZE; i++) {
    if (LEDPINS[i] == led) {
      digitalWrite(LEDPINS[i], LOW);
    }
  }
}
