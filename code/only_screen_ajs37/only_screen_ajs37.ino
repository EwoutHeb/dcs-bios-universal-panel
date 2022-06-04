
#include <LiquidCrystal.h>
//#define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

LiquidCrystal lcd(12, 11, 10,  5,  4,  3 , 2);
//                RS, RW, En, d4, d5, d6, d7

String ajs37MasterModes[] = { 
  "Maintenance",
  "Beredskap  ",
  "Navigering ",
  "Anflygning ",
  "Spaning    ",
  "Landing NAV",
  "Landing P/O"
};

String ajs37WeaponModes[] = { 
  " SJO/PLAN",
  "75/MR/DYK",
  "  LUFT/RR",
  "AKAN-JAKT",
  "   ATTACK",
  "    IR-RB"
};

void onMasterModeSelectChange(unsigned int masterPos) {
  lcd.setCursor(0, 0);
  lcd.print(ajs37MasterModes[masterPos]);
}
DcsBios::IntegerBuffer masterModeSelectBuffer(0x4614, 0xe000, 13, onMasterModeSelectChange);


void onAjs37DestIndicatorData1Change(char* data) {
  lcd.setCursor(14, 00);
  lcd.print(data);
}
DcsBios::StringBuffer<1> ajs37DestIndicatorData1Buffer(0x46ae, onAjs37DestIndicatorData1Change);

void onAjs37DestIndicatorData2Change(char* data) {
  lcd.setCursor(15, 00);
  lcd.print(data);
}
DcsBios::StringBuffer<1> ajs37DestIndicatorData2Buffer(0x46b0, onAjs37DestIndicatorData2Change);


void onAjs37NavIndicatorData1Change(char* data) {
  lcd.setCursor(0, 01);
  lcd.print(data);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData1Buffer(0x46a2, onAjs37NavIndicatorData1Change);

void onAjs37NavIndicatorData2Change(char* data) {
  lcd.setCursor(1, 01);
  lcd.print(data);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData2Buffer(0x46a4, onAjs37NavIndicatorData2Change);

void onAjs37NavIndicatorData3Change(char* data) {
  lcd.setCursor(2, 01);
  lcd.print(data);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData3Buffer(0x46a6, onAjs37NavIndicatorData3Change);

void onAjs37NavIndicatorData4Change(char* data) {
  lcd.setCursor(3, 01);
  lcd.print(data);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData4Buffer(0x46a8, onAjs37NavIndicatorData4Change);

void onAjs37NavIndicatorData5Change(char* data) {
  lcd.setCursor(4, 01);
  lcd.print(data);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData5Buffer(0x46aa, onAjs37NavIndicatorData5Change);

void onAjs37NavIndicatorData6Change(char* data) {
  lcd.setCursor(5, 01);
  lcd.print(data);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData6Buffer(0x46ac, onAjs37NavIndicatorData6Change);


void onWeaponSelectChange(unsigned int weaponPos) {
  lcd.setCursor(7, 1);
  lcd.print(ajs37WeaponModes[weaponPos]);
}
DcsBios::IntegerBuffer weaponSelectBuffer(0x4600, 0x00e0, 5, onWeaponSelectChange);



void setup() {
  lcd.begin(16, 2);
  /*lcd.setCursor(0, 0);
  lcd.print("test");*/
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
