
#include <LiquidCrystal.h>
#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"


LiquidCrystal lcd(12, 11, 10,  5,  4,  3 , 2);
//                RS, RW, En, d4, d5, d6, d7


// DcsBios::RotaryEncoder enc_04("UNDEF", "DEC", "INC", 48, 49, 2); //RotEnc4
DcsBios::RotaryEncoder fr22InnerRightKnob("FR22_INNER_RIGHT_KNOB", "-3200", "+3200", 48, 49);


String ajs37MasterModes[] = { 
  "Maintenance",
  "Beredskap  ",
  "Navigering ",
  "Anflygning ",
  "Spaning    ",
  "Landing NAV",
  "Landing P/O"
};


void onMasterModeSelectChange(unsigned int masterPos) {
  lcd.setCursor(0, 0);
  lcd.print(ajs37MasterModes[masterPos]);
}
DcsBios::IntegerBuffer masterModeSelectBuffer(0x4614, 0xe000, 13, onMasterModeSelectChange);


void setup() {
  lcd.begin(16, 2);
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
