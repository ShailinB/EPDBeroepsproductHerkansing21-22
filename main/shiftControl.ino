
// State
int displayState;

const int STATE_DISPLAY_HALT = 0;
const int STATE_DISPLAY_LOPEN = 1;
const int STATE_DISPLAY_AFTELLEN = 2;

// Pin diagram
const int PIN_ST_CP = A1;
const int PIN_SH_CP = A2;
const int PIN_DS = A0;

// Led:Font ratio
const int LED_COUNT = 8;
const int FONT_COUNT = 7;

// Fonts
const byte FONTS_AFTELLEN[FONT_COUNT] = {
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110 //6
};
const byte FONT_HALT = B01101110; 
const byte FONT_LOPEN = B00011100; 

// Variables for countdown
int currentNumber = FONT_COUNT - 1;

// Timer for countdown
unsigned long timer_countdown;
const int INTERVAL_COUNTDOWN = 1000;

//Functions
void shiftRegisterSetup() {
  pinMode(PIN_ST_CP, OUTPUT);
  pinMode(PIN_SH_CP, OUTPUT);
  pinMode(PIN_DS, OUTPUT);

  // Init timer
  timer_countdown = timerSetup(INTERVAL_COUNTDOWN);
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
void segmentedDisplay_halt() {
  displayState = STATE_DISPLAY_HALT;
  shiftSetPattern(FONT_HALT);
}

void segmentedDisplay_lopen() {
  displayState = STATE_DISPLAY_LOPEN;
  shiftSetPattern(FONT_LOPEN);
}

void segmentedDisplay_aftellen() {
  displayState = STATE_DISPLAY_AFTELLEN;
  if (timerIsPassed(timer_countdown, INTERVAL_COUNTDOWN)) {
    shiftSetPattern(FONTS_AFTELLEN[currentNumber]);
    Serial.println(currentNumber);
    currentNumber--;
    timer_countdown = timerReset();
  }
}

void segmentedDisplay_test() {
  while(timerIsPassed(timer_displayTesting, INTERVAL_DISPLAYTESTING)) {
   shiftSetAllOn(); 
  }
}

int getCurrentNumber() {
  return currentNumber;
}

void resetCounter() {
  currentNumber = FONT_COUNT - 1;
}

// Display state

boolean isDisplayOnHalt() {
  return displayState == STATE_DISPLAY_HALT;
}
