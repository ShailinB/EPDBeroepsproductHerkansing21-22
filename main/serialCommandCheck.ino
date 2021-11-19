//
//// Serial command variabelen ----------------------
//
//char ontv_karakter = 'n';
//
//void catchSerialCommand() {
//  if ( Serial.available() > 0) {
//
//    int catched = Serial.read();
//
//    switch (catched) {
//      case 'n':
//
//        ontv_karakter = 'n';
//        SMLOGGER();
//
//        break;
//
//      case 'd':
//
//        ontv_karakter = 'd';
//        SMLOGGER();
//
//        break;
//
//      case 'o':
//
//        ontv_karakter = 'o';
//        SMLOGGER();
//
//        break;
//      case 'l':
//
//        SMLOGGER();
//
//        break;
//    }
//
//  }
//}
//
//char getOntv_karakter() {
//  return ontv_karakter;
//}
