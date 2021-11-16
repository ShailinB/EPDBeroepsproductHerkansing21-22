
void setup() {
  Serial.begin(9600);
  buzzerSetup();
}

void loop() {
//  halt();
//  lopen();
  doorlopen(4);
}
