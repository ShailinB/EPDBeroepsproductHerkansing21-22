
// Stateholder
int state = 0;

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

void initTimers() {
    prev_dodetijd = timerSetup(INTERVAL_DODETIJD);
    prev_dodetijd = timerReset();
}

void kruispunt() {
    switch(state) {
        
        case STATE_DODE_TIJD:
            state_dode_tijd_do();

            if(timerIsPassed(prev_dodetijd, INTERVAL_DODETIJD)) {
                Serial.println("dode tijd exit");
                state_dode_tijd_exit();
                state = STATE_WACHT;
                state_wacht_entry();
            }
            
            break;
        case STATE_WACHT:
            state_wacht_do();

            if(timerIsPassed(prev_wacht, INTERVAL_WACHT)) {
                Serial.println("wacht exit");
                state_wacht_exit();
                state = STATE_OPENEN;
                state_openen_entry();
            }
            
            break;
        case STATE_OPENEN:
            state_openen_do();

            if(timerIsPassed(prev_openen, INTERVAL_OPENEN)) {
                Serial.println("openen exit");
                state_openen_exit();
                state = STATE_DODE_TIJD;
                state_dode_tijd_entry();
            }
            
            break;
//        case STATE_OPEN:
//        case STATE_SLUITEN:
//
//        case STATE_ROOD_ORANJE_LICHT:
//        case STATE_GROEN_LICHT:
//        case STATE_GROEN_KNIPPERLICHT:
//        case STATE_ORANJE_LICHT:

    }
}

// Entry-Do-Exit methods

// STATE_DODE_TIJD
void state_dode_tijd_entry(){
  prev_dodetijd = timerReset();  
};
void state_dode_tijd_do(){
    buzzer_halt();
};
void state_dode_tijd_exit(){};

// STATE_WACHT
void state_wacht_entry(){
    prev_wacht = timerReset();
};
void state_wacht_do(){
    buzzer_lopen();
};
void state_wacht_exit(){};

// STATE_OPENEN
void state_openen_entry(){
    prev_openen = timerReset();
};
void state_openen_do(){
    buzzer_doorlopen(4);
};
void state_openen_exit(){};

// STATE_OPEN
void state_open_entry(){};
void state_open_do(){};
void state_open_exit(){};

// STATE_SLUITEN
void state_sluiten_entry(){};
void state_sluiten_do(){};
void state_sluiten_exit(){};

// STATE_ROOD_ORANJE_LICHT
void state_rood_oranje_entry(){};
void state_rood_oranje_do(){};
void state_rood_oranje_exit(){};

// STATE_GROEN
void state_groen_entry(){};
void state_groen_do(){};
void state_groen_exit(){};

// STATE_GROEN_KNIPPERLICHT
void state_groen_knipperlicht_entry(){};
void state_groen_knipperlicht_do(){};
void state_groen_knipperlicht_exit(){};

// STATE_ORANJE_LICHT
void state_oranje_entry(){};
void state_oranje_do(){};
void state_oranje_exit(){};



unsigned long timerSetup(int interval) {
  return 0 - interval;
}

boolean timerIsPassed(unsigned long previous, int interval) {
  return millis() - previous >= interval;
}

unsigned long timerReset() {
  return millis();
}
