
// Pin diagram stoplichten -------------------------------

const int LEDPINS_SIZE = 6;
const int LEDPINS [] = {13, 8, 7, 4, 3, 2};

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

// Getters

//Linker stoplicht
const int getLinker_RoodLicht() {
  return 13;
}

const int getLinker_OranjeLicht() {
  return 8;
}

const int getLinker_GroenLicht() {
  return 7;
}

//Rechter stoplicht
const int getRechter_RoodLicht() {
  return 4;
}

const int getRechter_OranjeLicht() {
  return 3;
}

const int getRechter_GroenLicht() {
  return 2;
}
