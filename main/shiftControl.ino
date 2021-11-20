

//Magic Numbers
const int LED_COUNT = 8;
const int PIN_ST_CP = A1;
const int PIN_SH_CP = A2;
const int PIN_DS = A0;

const int FONT_COUNT = 7;
const byte FONTS_OVERSTEEKPLAATS_AFTELLEN[FONT_COUNT] = {
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110 //6
};
const byte FONT_OVERSTEEKPLAATS_NIETLOPEN = B01101110; //H voor halt
const byte FONT_OVERSTEEKPLAATS_LOPEN = B00011100; //L voor lopen

int counterDisplay = FONT_COUNT - 1;

// Timer openen
unsigned long prev_countdown;
const int INTERVAL_COUNTDOWN = 1000;

//Functions
void shiftRegisterSetup() {
  pinMode(PIN_ST_CP, OUTPUT);
  pinMode(PIN_SH_CP, OUTPUT);
  pinMode(PIN_DS, OUTPUT);

  // Init timer
  prev_countdown = timerSetup(INTERVAL_COUNTDOWN);
}

void shiftSetPattern(byte pattern) {
  digitalWrite(PIN_ST_CP, LOW);
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(PIN_SH_CP, LOW);
    digitalWrite(PIN_DS, bitRead(pattern, i));
    digitalWrite(PIN_SH_CP, HIGH);
  }
  digitalWrite(PIN_ST_CP, HIGH);
  digitalWrite(PIN_ST_CP, LOW);
}

void shiftSetAllOn() {
  digitalWrite(PIN_ST_CP, LOW);
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(PIN_SH_CP, LOW);
    digitalWrite(PIN_DS, HIGH);
    digitalWrite(PIN_SH_CP, HIGH);
  }
  digitalWrite(PIN_ST_CP, HIGH);
  digitalWrite(PIN_ST_CP, LOW);
}

void shiftSetAllOff() {
  digitalWrite(PIN_ST_CP, LOW);
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(PIN_SH_CP, LOW);
    digitalWrite(PIN_DS, LOW);
    digitalWrite(PIN_SH_CP, HIGH);
  }
  digitalWrite(PIN_ST_CP, HIGH);
  digitalWrite(PIN_ST_CP, LOW);
}

//Oversteek licht functions
void displayNietLopen() {
  shiftSetPattern(FONT_OVERSTEEKPLAATS_NIETLOPEN);
}

void displayLopen() {
  shiftSetPattern(FONT_OVERSTEEKPLAATS_LOPEN);
}

void displayAftellen() {
  if (timerIsPassed(prev_countdown, INTERVAL_COUNTDOWN)) {
    shiftSetPattern(FONTS_OVERSTEEKPLAATS_AFTELLEN[counterDisplay]);
    Serial.println(counterDisplay);
    counterDisplay--;
    prev_countdown = timerReset();
  }
}

int getCounter() {
  return counterDisplay;
}

void resetCounter() {
  counterDisplay = FONT_COUNT - 1;
}
