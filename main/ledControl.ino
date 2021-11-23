
// Pin diagram stoplichten -------------------------------

const int LEDPINS_SIZE = 6;
const int LEDPINS [] = {13, 8, 7, 4, 3, 2};

// Kleuren
const int RED = 0;
const int AMBER = 1;
const int GREEN = 2;

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

void setLedOn(const int color) {
  switch (color) {
    case RED:
      if (stoplichtKnoppenState[LINKERSTOPLICHT]) {
        ledControlSetLedOn(getLinker_RoodLicht());
      } else if (stoplichtKnoppenState[RECHTERSTOPLICHT]) {
        ledControlSetLedOn(getRechter_RoodLicht());
      }
      break;
    case AMBER:
      if (stoplichtKnoppenState[LINKERSTOPLICHT]) {
        ledControlSetLedOn(getLinker_OranjeLicht());
      } else if (stoplichtKnoppenState[RECHTERSTOPLICHT]) {
        ledControlSetLedOn(getRechter_OranjeLicht());
      }
      break;
    case GREEN:
      if (stoplichtKnoppenState[LINKERSTOPLICHT]) {
        ledControlSetLedOn(getLinker_GroenLicht());
      } else if (stoplichtKnoppenState[RECHTERSTOPLICHT]) {
        ledControlSetLedOn(getRechter_GroenLicht());
      }
      break;
  }
}

void setLedOff(const int color) {
  switch (color) {
    case RED:
      if (stoplichtKnoppenState[LINKERSTOPLICHT]) {
        ledControlSetLedOff(getLinker_RoodLicht());
      } else if (stoplichtKnoppenState[RECHTERSTOPLICHT]) {
        ledControlSetLedOff(getRechter_RoodLicht());
      }
      break;
    case AMBER:
      if (stoplichtKnoppenState[LINKERSTOPLICHT]) {
        ledControlSetLedOff(getLinker_OranjeLicht());
      } else if (stoplichtKnoppenState[RECHTERSTOPLICHT]) {
        ledControlSetLedOff(getRechter_OranjeLicht());
      }
      break;
    case GREEN:
      if (stoplichtKnoppenState[LINKERSTOPLICHT]) {
        ledControlSetLedOff(getLinker_GroenLicht());
      } else if (stoplichtKnoppenState[RECHTERSTOPLICHT]) {
        ledControlSetLedOff(getRechter_GroenLicht());
      }
      break;
  }
}

void setStoplichtenOpRood() {
  ledControlSetLedOn(getLinker_RoodLicht());
  ledControlSetLedOn(getRechter_RoodLicht());
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

//Kleuren

const int getRed() {
  return RED;
}

const int getAmber() {
  return AMBER;
}

const int getGreen() {
  return GREEN;
}
