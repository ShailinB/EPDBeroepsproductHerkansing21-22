
const int BUTTON_COUNT = 4;
const int BUTTON_PIN[BUTTON_COUNT] = {10,9,6,5};

// Stoplicht knoppen
const int LINKERSTOPLICHT = 0;
const int RECHTERSTOPLICHT = 1;
const int AANTAL_STOPLICHTEN = 2;
boolean stoplichtKnoppenState[AANTAL_STOPLICHTEN];

const int BUTTON_STATE_RELEASED = 0;
const int BUTTON_STATE_CHECK_PRESSED = 1;
const int BUTTON_STATE_PRESSED = 2;
const int BUTTON_STATE_CHECK_RELEASED = 3;

int buttonState [BUTTON_COUNT];
boolean buttonIsClicked [BUTTON_COUNT];
unsigned long buttonTimer [BUTTON_COUNT];
const unsigned long BUTTON_INTERVAL = 10;

void buttonSetup() {
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(BUTTON_PIN[i], INPUT);
    buttonTimer[i] = timerSetup(BUTTON_INTERVAL);
    buttonIsClicked[i] = false;
    buttonState[i] = BUTTON_STATE_RELEASED;
    button_Released_Entry(i);
  }
  resetStoplichtenStates();
}

boolean buttonDown(int button) {
  return digitalRead(BUTTON_PIN[button]) == LOW;
}

boolean buttonUp(int button) {
  return !buttonDown(button);
}

boolean buttonClicked(int button) {
  boolean result = buttonIsClicked[button];
  buttonIsClicked[button] = false;
  return result;
}

void buttonLoop() {
  for (int button = 0; button < BUTTON_COUNT; button++) {
    switch (buttonState[button]) {
      case BUTTON_STATE_RELEASED:
        button_Released_Do(button);
        if (buttonDown(button)) {
          button_Released_Exit(button);
          buttonState[button] = BUTTON_STATE_CHECK_PRESSED;
          button_CheckPressed_Entry(button);
        }
        break;

      case BUTTON_STATE_CHECK_PRESSED:
        button_CheckPressed_Do(button);
        if (buttonUp(button)) {
          button_CheckPressed_Exit(button);
          buttonState[button] = BUTTON_STATE_RELEASED;
          button_Released_Entry(button);
        } else if (buttonDown(button) && timerIsPassed(buttonTimer[button], BUTTON_INTERVAL)) {
          button_CheckPressed_Exit(button);
          buttonState[button] = BUTTON_STATE_PRESSED;
          button_Pressed_Entry(button);
        }
        break;

      case BUTTON_STATE_PRESSED:
        button_Pressed_Do(button);
        if (buttonUp(button)) {
          button_Pressed_Exit(button);
          buttonState[button] = BUTTON_STATE_CHECK_RELEASED;
          button_CheckReleased_Entry(button);
        }
        break;

      case BUTTON_STATE_CHECK_RELEASED:
        button_CheckReleased_Do(button);
        if (buttonDown(button)) {
          button_CheckReleased_Exit(button);
          buttonState[button] = BUTTON_STATE_PRESSED;
          button_Pressed_Entry(button);
        } else if (buttonUp(button) && timerIsPassed(buttonTimer[button], BUTTON_INTERVAL)) {
          button_CheckReleased_Exit(button);
          buttonState[button] = BUTTON_STATE_RELEASED;
          buttonIsClicked[button] = true;
          button_Released_Entry(button);
        }
        break;
    }
  }
}

//Getters 
const int getOversteekKnop() {
  return 0;
}

const int getLinkerStoplicht() {
  return 3;
}

const int getRechterStoplicht() {
  return 2;
}

const int getTestknop() {
  return 1;
}

// Setters

void resetStoplichtenStates() {
  for (int i = 0; i< AANTAL_STOPLICHTEN; i++) {
    stoplichtKnoppenState[i] = false;
  }
}

//----------------------------------------------------------------------------
void button_Released_Entry(int button) {}
void button_Released_Do(int button) {}
void button_Released_Exit(int button) {}

void button_CheckPressed_Entry(int button) {
  buttonTimer[button] = timerReset();
}
void button_CheckPressed_Do(int button) {}
void button_CheckPressed_Exit(int button) {}

void button_Pressed_Entry(int button) {}
void button_Pressed_Do(int button) {}
void button_Pressed_Exit(int button) {}

void button_CheckReleased_Entry(int button) {
  buttonTimer[button] = timerReset();
}
void button_CheckReleased_Do(int button) {}
void button_CheckReleased_Exit(int button) {}

//Getters
boolean getRechterVerkeersLichtIngedrukt() {
  return buttonDown(BUTTON_PIN[0]);
}

boolean getLinkerVerkeersLichtIngedrukt() {
  return buttonDown(BUTTON_PIN[1]);
}
