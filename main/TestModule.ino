
// State tracker
int state;

// States
const int STATE_VERKEERSLICHTEN = 0;
const int STATE_OVERSTEEKDISPLAY = 1;
const int STATE_BUZZER = 2;
const int STATE_SLAGBOOM_OPENEN = 3;
const int STATE_SLAGBOOM_SLUITEN = 4;

// Sequence tracker
boolean isSequenceDone = false;

void testSequence() {
  switch(state) {
    case STATE_VERKEERSLICHTEN:
      state_verkeerslichten_do();

      if() {
        state_verkeerslichten_exit();
        state = STATE_OVERSTEEKDISPLAY;
        state_oversteekdisplay_entry();
      }
      break;
    case STATE_OVERSTEEKDISPLAY:
      state_oversteekdisplay_do();

      if() {
        state_oversteekdisplay_exit();
        state = STATE_BUZZER;
        state_buzzer_entry();
      }
      break;
    case STATE_BUZZER:
      state_buzzer_do();

      if() {
        state_buzzer_exit();
        state = STATE_SLAGBOOM_OPENEN;
        state_slagboom_openen_entry();
      }
      
      break;
    case STATE_SLAGBOOM_OPENEN:
      state_slagboom_openen_do();

      if(isServoOpen()) {
        state_slagboom_openen_exit();
        state = STATE_SLAGBOOM_SLUITEN;
        state_slagboom_sluiten_entry();
      }
      break;
    case STATE_SLAGBOOM_SLUITEN:
      state_slagboom_sluiten_do();
      
      if(isServoClosed()) {
        isSequeneDone = true;
      }
      break;
  }
}

// Entry-Do-Exit methods

// Verkeerslichten
void state_verkeerslichten_entry() {}
void state_verkeerslichten_do() {}
void state_verkeerslichten_exit() {}

// Oversteekdisplay
void state_oversteekdisplay_entry() {}
void state_oversteekdisplay_do() {}
void state_oversteekdisplay_exit() {}

// Buzzer
void state_buzzer_entry() {}
void state_buzzer_do() {}
void state_buzzer_exit() {}

// Slagboom openen
void state_slagboom_openen_entry() {}
void state_slagboom_openen_do() {}
void state_slagboom_openen_exit() {}

// Slagboom sluiten
void state_slagboom_sluiten_entry() {}
void state_slagboom_sluiten_do() {}
void state_slagboom_sluiten_exit() {}
