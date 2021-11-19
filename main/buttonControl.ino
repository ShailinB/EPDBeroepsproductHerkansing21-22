
// ------------------------------------------------

const int BUTTON_PIN_COUNT = 4;
const int BUTTON_PIN[BUTTON_PIN_COUNT] = {10, 11, 9, A3};

const int VOETGANGER = 0;
const int STOPLICHT1 = 1;
const int STOPLICHT2 =  2;
const int TESTKNOP = 3;

boolean isButtonClicked[BUTTON_PIN_COUNT];

// States button ----------------------------------

const int BUTTON_STATE_RELEASED = 0;
const int BUTTON_STATE_CHECK_PRESSED = 1;
const int BUTTON_STATE_PRESSED = 2;
const int BUTTON_STATE_CHECK_RELEASED = 3;
int buttonState[BUTTON_PIN_COUNT];

// timer gegevens button

unsigned long previousTime[BUTTON_PIN_COUNT];
int interval = 10; //ms brug bouncing

void buttonSetup() {
  for (int button = 0; button < BUTTON_PIN_COUNT; button++) {
    pinMode(BUTTON_PIN[button], INPUT_PULLUP);
    isButtonClicked[button] = false;
    previousTime[button] = timerSetup(interval);
    buttonState[button] = BUTTON_STATE_RELEASED;
    button_Released_Entry(button);
  }
}

boolean buttonDown(int button) {
  return digitalRead(BUTTON_PIN[button]) == LOW;
}

boolean buttonUp(int button) {
  return !buttonDown(button);
}

boolean buttonClicked(int button) {
  boolean result = isButtonClicked[button];
  isButtonClicked[button] = false;
  return result;
}

void buttonLoop() {
  for (int button = 0; button < BUTTON_PIN_COUNT; button++) {
    switch (buttonState[button]) {
      case BUTTON_STATE_RELEASED :
        button_Released_Do(button);
        if (buttonDown(button)) {
          button_Released_Exit(button);
          buttonState[button] = BUTTON_STATE_CHECK_PRESSED;
          button_Check_Pressed_Entry(button);
        }
        break;

      case BUTTON_STATE_CHECK_PRESSED :
        button_Check_Pressed_Do(button);
        if (buttonUp(button)) {
          button_Check_Pressed_Exit(button);
          buttonState[button] = BUTTON_STATE_RELEASED;
          button_Released_Entry(button);
        } else if (buttonDown(button) && timerIsPassed(previousTime[button], interval)) {
          button_Check_Pressed_Exit(button);
          buttonState[button] = BUTTON_STATE_PRESSED;
          button_Pressed_Entry(button);
        }
        break;


      case BUTTON_STATE_PRESSED :
        button_Pressed_Do(button);
        if (buttonUp(button)) {
          button_Pressed_Exit(button);
          buttonState[button] = BUTTON_STATE_CHECK_RELEASED;
          button_Check_Released_Entry(button);
        }
        break;

      case BUTTON_STATE_CHECK_RELEASED :
        button_Check_Released_Do(button);
        if (buttonDown(button)) {
          button_Check_Released_Exit(button);
          buttonState[button] = BUTTON_STATE_PRESSED;
          button_Pressed_Entry(button);
        } else if (buttonUp(button) && timerIsPassed(previousTime[button], interval)) {
          button_Check_Released_Exit(button);
          buttonState[button] = BUTTON_STATE_RELEASED;
          isButtonClicked[button] = true;
          button_Released_Entry(button);
        }
        break;
    }
  }
}

void button_Released_Entry(int button) {}
void button_Released_Do(int button) {}
void button_Released_Exit(int button) {}

void button_Check_Pressed_Entry(int button) {
  previousTime[button] = timerReset();
}

void button_Check_Pressed_Do(int button) {}
void button_Check_Pressed_Exit(int button) {}
void button_Pressed_Entry(int button) {}
void button_Pressed_Do(int button) {}
void button_Pressed_Exit(int button) {}

void button_Check_Released_Entry(int button) {
  previousTime[button] = timerReset();
}

void button_Check_Released_Do(int button) {}
void button_Check_Released_Exit(int button) {}

const int getVoetganger() {
  return VOETGANGER;
}

const int getSTOPLICHT1() {
  return STOPLICHT1;
}

const int getSTOPLICHT2() {
  return STOPLICHT2;
}

const int getTESTKNOP() {
  return TESTKNOP;
}

boolean IsButtonClicked(const int button) {
  return isButtonClicked[button];
}
