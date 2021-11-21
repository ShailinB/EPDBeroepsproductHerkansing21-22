
// Stateholder
int state = 0;

// Oversteekknop
boolean verzoekOversteken;

// States
const int STATE_DODE_TIJD = 0;
const int STATE_WACHT = 1;
const int STATE_OPENEN = 2;
const int STATE_OPEN = 3;
const int STATE_SLUITEN = 4;
const int STATE_ROOD_ORANJE_LICHT = 5;
const int STATE_GROEN_LICHT = 6;
const int STATE_GROEN_KNIPPERLICHT = 7;
const int STATE_ORANJE_LICHT = 8;

// Timer dode tijd
unsigned long timer_dodetijd;
const int INTERVAL_DODETIJD = 5000;

// Timer wacht
unsigned long timer_wacht;
const int INTERVAL_WACHT = 5000;

// Timer openen
unsigned long timer_openen;
const int INTERVAL_OPENEN = 5000;

// Timer openen
unsigned long timer_open;
const int INTERVAL_OPEN = 6000;

// Buzzer variables
const int AMOUNTOFBEEPS = 4;

void kruispunt_setup() {

  // Init timer
  timer_dodetijd = timerSetup(INTERVAL_DODETIJD);
  timer_dodetijd = timerReset();

  // Init oversteekknop
  verzoekOversteken = false;
}

// Event trigger conditions =================================================================

// Only when the dead time has passed, the system should listen to events again.
boolean isSafetyProtocolCompleted() {
  return timerIsPassed(timer_dodetijd, INTERVAL_DODETIJD);
}

// Its only allowed/save to cross the road, if barrier is closed and someone requested to cross the road.
boolean isSafeToCrossRoad() {
  return verzoekOversteken && isServoClosed();
}

// Its only save/allowed to start walking, if the barrier has fully opened.
boolean isSafeToStartWalking() {
  return isServoOpen();
}

// Only when the time to cross the road has passed, the barrier should start closing down.
boolean crossingTimeHasPassed() {
  return getCurrentNumber() <= -2;
}

// Only when the barrier has been fully closed again, the crosswalk sequence is fully completed.
boolean isSequenceCompleted() {
  return isServoClosed();
}

// Event trigger conditions ==================================================================

void kruispunt() {
  switch (state) {

    case STATE_DODE_TIJD:
      state_dode_tijd_do();

      if (isSafetyProtocolCompleted()) {
        state_dode_tijd_exit();
        state = STATE_WACHT;
        state_wacht_entry();
      }

      break;
    case STATE_WACHT:
      state_wacht_do();

      if (isSafeToCrossRoad()) {
        state_wacht_exit();
        state = STATE_OPENEN;
        state_openen_entry();
      }

      break;
    case STATE_OPENEN:
      state_openen_do();

      if (isSafeToStartWalking()) {
        state_openen_exit();
        state = STATE_OPEN;
        state_open_entry();
      }

      break;
    case STATE_OPEN:
      state_open_do();

      if (crossingTimeHasPassed()) {
        state_open_exit();
        state = STATE_SLUITEN;
        state_sluiten_entry();
      }

      break;
    case STATE_SLUITEN:
      state_sluiten_do();

      if (isSequenceCompleted()) {
        state_wacht_exit();
        state = STATE_DODE_TIJD;
        state_dode_tijd_entry();
      }
      break;
      //
      //        case STATE_ROOD_ORANJE_LICHT:
      //        case STATE_GROEN_LICHT:
      //        case STATE_GROEN_KNIPPERLICHT:
      //        case STATE_ORANJE_LICHT:

  }
}

// Entry-Do-Exit methods ========================================================

// STATE_DODE_TIJD
void state_dode_tijd_entry() {
  servoStop();
  timer_dodetijd = timerReset();
};
void state_dode_tijd_do() {
  segmentedDisplay_halt();
  buzzer_halt();
};
void state_dode_tijd_exit() {};

// STATE_WACHT
void state_wacht_entry() {
  timer_wacht = timerReset();
};
void state_wacht_do() {
  if (buttonClicked(getOversteekKnop())) {
    verzoekOversteken = true;
  }
  segmentedDisplay_halt();
  buzzer_halt();
};
void state_wacht_exit() {
  verzoekOversteken = false;
};

// STATE_OPENEN
void state_openen_entry() {
  servoStart();
  timer_openen = timerReset();
};
void state_openen_do() {
  segmentedDisplay_halt();
  servoOpen();
  buzzer_halt();
};
void state_openen_exit() {
  servoStop();
};

// STATE_OPEN
void state_open_entry() {
  timer_open = timerReset();
};
void state_open_do() {
  segmentedDisplay_aftellen();
  buzzer_lopen();
};
void state_open_exit() {
  resetCounter();
};

// STATE_SLUITEN
void state_sluiten_entry() {
  servoStart();
};
void state_sluiten_do() {
  segmentedDisplay_halt();
  servoClose();
  buzzer_doorlopen(AMOUNTOFBEEPS);
};
void state_sluiten_exit() {
  servoStop();
};

// STATE_ROOD_ORANJE_LICHT
void state_rood_oranje_entry() {};
void state_rood_oranje_do() {};
void state_rood_oranje_exit() {};

// STATE_GROEN
void state_groen_entry() {};
void state_groen_do() {};
void state_groen_exit() {};

// STATE_GROEN_KNIPPERLICHT
void state_groen_knipperlicht_entry() {};
void state_groen_knipperlicht_do() {};
void state_groen_knipperlicht_exit() {};

// STATE_ORANJE_LICHT
void state_oranje_entry() {};
void state_oranje_do() {};
void state_oranje_exit() {};

// Entry-Do-Exit methods ========================================================
