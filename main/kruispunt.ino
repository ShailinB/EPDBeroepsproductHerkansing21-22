
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
unsigned long prev_dodetijd;
const int INTERVAL_DODETIJD = 5000;

// Timer wacht
unsigned long prev_wacht;
const int INTERVAL_WACHT = 5000;

// Timer openen
unsigned long prev_openen;
const int INTERVAL_OPENEN = 5000;

// Timer openen
unsigned long prev_open;
const int INTERVAL_OPEN = 6000;

void kruispunt_setup() {

  // Init timers
  prev_dodetijd = timerSetup(INTERVAL_DODETIJD);
  prev_dodetijd = timerReset();

  // Init oversteekknop
  verzoekOversteken = false;
}

void kruispunt() {
  switch (state) {

    case STATE_DODE_TIJD:
      state_dode_tijd_do();

      if (timerIsPassed(prev_dodetijd, INTERVAL_DODETIJD)) {
        state_dode_tijd_exit();
        state = STATE_WACHT;
        state_wacht_entry();
      }

      break;
    case STATE_WACHT:
      state_wacht_do();

      if (verzoekOversteken && isServoClosed()) {
        state_wacht_exit();
        state = STATE_OPENEN;
        state_openen_entry();
      }

      break;
    case STATE_OPENEN:
      state_openen_do();

      if (isServoOpen()) {
        state_openen_exit();
        state = STATE_OPEN;
        state_open_entry();
      }

      break;
    case STATE_OPEN:
      state_open_do();

      if (getCounter() <= -2) {
        state_open_exit();
        state = STATE_SLUITEN;
        state_sluiten_entry();
      }

      break;
    case STATE_SLUITEN:
      state_sluiten_do();

      if (isServoClosed()) {
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

// Entry-Do-Exit methods

// STATE_DODE_TIJD
void state_dode_tijd_entry() {
  prev_dodetijd = timerReset();
};
void state_dode_tijd_do() {
  displayNietLopen();
  buzzer_halt();
};
void state_dode_tijd_exit() {};

// STATE_WACHT
void state_wacht_entry() {
  prev_wacht = timerReset();
};
void state_wacht_do() {
  if (buttonClicked(getOversteekKnop())) {
    verzoekOversteken = true;
  }
  displayNietLopen();
  buzzer_halt();
};
void state_wacht_exit() {
  verzoekOversteken = false;
};

// STATE_OPENEN
void state_openen_entry() {
  prev_openen = timerReset();
};
void state_openen_do() {
  displayNietLopen();
  servoOpen();
  buzzer_halt();
};
void state_openen_exit() {};

// STATE_OPEN
void state_open_entry() {
  prev_open = timerReset();
};
void state_open_do() {
  displayAftellen();
  buzzer_lopen();
};
void state_open_exit() {
  resetCounter();  
};

// STATE_SLUITEN
void state_sluiten_entry() {};
void state_sluiten_do() {
  displayNietLopen();
  servoClose();
  buzzer_doorlopen(4);
};
void state_sluiten_exit() {};

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
