
// State tracker
int teststate;

// States
const int STATE_VERKEERSLICHTEN = 0;
const int STATE_OVERSTEEKDISPLAY = 1;
const int STATE_BUZZER = 2;
const int STATE_SLAGBOOM_OPENEN = 3;
const int STATE_SLAGBOOM_HOLD = 4; // State zorgt ervoor dat de servo volledig open kan gaan voordat hij direct gesloten wordt.
const int STATE_SLAGBOOM_SLUITEN = 5;

// Sequence tracker
boolean isSequenceDone = false;

// WaitForBarrier
unsigned long timer_waitForBarrier;
const int INTERVAL_WAITFORBARRIER = 2000;

void testSequence() {
  switch(teststate) {
    case STATE_VERKEERSLICHTEN:
      state_verkeerslichten_do();

      if(isLedTestingDone()) {
        state_verkeerslichten_exit();
        teststate = STATE_OVERSTEEKDISPLAY;
        state_oversteekdisplay_entry();
      }
      break;
    case STATE_OVERSTEEKDISPLAY:
      state_oversteekdisplay_do();

      if(isDisplayTestingDone()) {
        state_oversteekdisplay_exit();
        teststate = STATE_BUZZER;
        state_buzzer_entry();
      }
      break;
    case STATE_BUZZER:
      state_buzzer_do();

      if(isBuzzTestCompleted()) {
        state_buzzer_exit();
        teststate = STATE_SLAGBOOM_OPENEN;
        state_slagboom_openen_entry();
      }
      
      break;
    case STATE_SLAGBOOM_OPENEN:
      state_slagboom_openen_do();

      if(isServoOpen()) {
        state_slagboom_openen_exit();
        teststate = STATE_SLAGBOOM_HOLD;
        timer_waitForBarrier = timerReset();
      }
      break;

      case STATE_SLAGBOOM_HOLD:
        if(timerIsPassed(timer_waitForBarrier, INTERVAL_WAITFORBARRIER)) {
          teststate = STATE_SLAGBOOM_SLUITEN;
        }
        break;
    case STATE_SLAGBOOM_SLUITEN:
      state_slagboom_sluiten_do();
      
      if(isServoClosed()) {
        isSequenceDone = true;
      }
      break;
  }
}

// Entry-Do-Exit methods

// Verkeerslichten
void state_verkeerslichten_entry() {
  ledTestingSetup();
}
void state_verkeerslichten_do() {
  stoplicht_test();  
}
void state_verkeerslichten_exit() {
  ledControlAllLedOff();  
}

// Oversteekdisplay
void state_oversteekdisplay_entry() {
  displayTestingSetup();  
}
void state_oversteekdisplay_do() {
  segmentedDisplay_test();  
}
void state_oversteekdisplay_exit() {
  shiftSetAllOff();  
}

// Buzzer
void state_buzzer_entry() {
  buzzTest_setup();  
}
void state_buzzer_do() {
  buzzer_test();  
}
void state_buzzer_exit() {}

// Slagboom openen
void state_slagboom_openen_entry() {
  servoStart();
  resetTimerServo();  
}
void state_slagboom_openen_do() {
  servoOpen();  
}
void state_slagboom_openen_exit() {
  servoStop();  
}

// Slagboom sluiten
void state_slagboom_sluiten_entry() {
  servoStart();  
  resetTimerServo(); 
}
void state_slagboom_sluiten_do() {
  servoClose();  
}
void state_slagboom_sluiten_exit() {
  servoStop();  
}

/////////

boolean testSequenceCompleted() {
  return isSequenceDone;
}
