
#include <LiquidCrystal.h>
#define DCSBIOS_IRQ_SERIAL
#include "DcsBios.h"

bool g_bRun = true;    //main loop control

int planeId = 2;
int maxSubmenu = 1;

int enc5PinA = 51; // Connected to CLK on KY-040
int enc5PinB = 52; // Connected to DT on KY-040
int encoderPosCount = 1; 
int pinALast; 
int aVal;


LiquidCrystal lcd(12, 11, 10,  5,  4,  3,  2);
//                RS, RW, En, d4, d5, d6, d7


#define NUMBER_OF_CONTROLS 36 //26

DcsBios::Switch2Pos switch2_01("UNDEF", 22);
DcsBios::Switch2Pos switch2_02("UNDEF", 23);
DcsBios::Switch2Pos switch2_03("UNDEF", 24);
DcsBios::Switch2Pos switch2_04("UNDEF", 26);
DcsBios::Switch2Pos switch2_05("UNDEF", 27);
DcsBios::Switch2Pos switch2_06("UNDEF", 28);
DcsBios::Switch2Pos switch2_07("UNDEF", 30);
DcsBios::Switch2Pos switch2_08("UNDEF", 31);
DcsBios::Switch2Pos switch2_09("UNDEF", 32);
DcsBios::Switch2Pos switch2_10("UNDEF", 34);
DcsBios::Switch2Pos switch2_11("UNDEF", 35);
DcsBios::Switch2Pos switch2_12("UNDEF", 36);
DcsBios::Switch2Pos switch2_13("UNDEF", 25);
DcsBios::Switch2Pos switch2_14("UNDEF", 29);
DcsBios::Switch2Pos switch2_15("UNDEF", 33);
DcsBios::Switch2Pos switch2_16("UNDEF", 37);

DcsBios::RotaryEncoder enc_01("UNDEF", "DEC", "INC", 39, 40, 2); //RotEnc1
DcsBios::RotaryEncoder enc_02("UNDEF", "DEC", "INC", 42, 43, 2); //RotEnc2
DcsBios::RotaryEncoder enc_03("UNDEF", "DEC", "INC", 45, 46, 2); //RotEnc3
DcsBios::RotaryEncoder enc_04("UNDEF", "DEC", "INC", 48, 49, 2); //RotEnc4
DcsBios::RotaryEncoder enc_05("UNDEF", "DEC", "INC", 51, 52, 2); //RotEnc5 //This one is used for changing submenu's and is generally not used as input

DcsBios::Switch2Pos switch2_e1("UNDEF", 41); //button of RotEnc1
DcsBios::Switch2Pos switch2_e2("UNDEF", 44); //button of RotEnc2
DcsBios::Switch2Pos switch2_e3("UNDEF", 47); //button of RotEnc3
DcsBios::Switch2Pos switch2_e4("UNDEF", 50); //button of RotEnc4
DcsBios::Switch2Pos switch2_e5("UNDEF", 53); //button of RotEnc5

// To use LED in dynamic system, extra code is needed that is not currently implemented
//DcsBios::LED led_01(0x0000, 0x0000, 10); //example of LED


struct _controllayout_type {
  const char * PROGMEM cntrl_name[NUMBER_OF_CONTROLS];
  _controllayout_type(const char *_name[]) {
    for (int i = 0; i < NUMBER_OF_CONTROLS; i++ )
      cntrl_name[i] = _name[i]; 
  }
  
  void MakeCurrent() {
  
    /////////////////////////////////
    //  Needs to match the control map objects (DcsBios::#####) defined above
    // 
    
    switch2_01.SetControl(cntrl_name[0]);
    switch2_02.SetControl(cntrl_name[1]);
    switch2_03.SetControl(cntrl_name[2]);
    switch2_04.SetControl(cntrl_name[3]);
    switch2_05.SetControl(cntrl_name[4]);
    switch2_06.SetControl(cntrl_name[5]);
    switch2_07.SetControl(cntrl_name[6]);
    switch2_08.SetControl(cntrl_name[7]);
    switch2_09.SetControl(cntrl_name[8]);
    switch2_10.SetControl(cntrl_name[9]);
    switch2_11.SetControl(cntrl_name[10]);
    switch2_12.SetControl(cntrl_name[11]);
    switch2_13.SetControl(cntrl_name[12]);
    switch2_14.SetControl(cntrl_name[13]);
    switch2_15.SetControl(cntrl_name[14]);
    switch2_16.SetControl(cntrl_name[15]);

    enc_01.SetControl(cntrl_name[16]);
    enc_02.SetControl(cntrl_name[17]);
    enc_03.SetControl(cntrl_name[18]);
    enc_04.SetControl(cntrl_name[19]);
    enc_05.SetControl(cntrl_name[20]);

    switch2_e1.SetControl(cntrl_name[21]);
    switch2_e2.SetControl(cntrl_name[22]);
    switch2_e3.SetControl(cntrl_name[23]);
    switch2_e4.SetControl(cntrl_name[24]);
    switch2_e5.SetControl(cntrl_name[25]);

    enc_01.SetArg(cntrl_name[26], cntrl_name[27]);
    enc_02.SetArg(cntrl_name[28], cntrl_name[29]);
    enc_03.SetArg(cntrl_name[30], cntrl_name[31]);
    enc_04.SetArg(cntrl_name[32], cntrl_name[33]);
    enc_05.SetArg(cntrl_name[34], cntrl_name[35]);

    /* backup of the input's names
    switch2_01
    switch2_02
    switch2_03
    switch2_04
    switch2_05
    switch2_06
    switch2_07
    switch2_08
    switch2_09
    switch2_10
    switch2_11
    switch2_12
    switch2_13
    switch2_14
    switch2_15
    switch2_16
    
    enc_01
    enc_02
    enc_03
    enc_04
    
    switch2_e1
    switch2_e2
    switch2_e3
    switch2_e4
    switch2_e5
    */

  }
};

/*
 * templade
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UNDEF",    //switch2_01
  "UNDEF",    //switch2_02
  "UNDEF",    //switch2_03
  "UNDEF",    //switch2_04
  "UNDEF",    //switch2_05
  "UNDEF",    //switch2_06
  "UNDEF",    //switch2_07
  "UNDEF",    //switch2_08
  "UNDEF",    //switch2_09
  "UNDEF",    //switch2_10
  "UNDEF",    //switch2_11
  "UNDEF",    //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "UNDEF",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
 */

const char * const controlnames_default[] PROGMEM = {
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UNDEF",    //switch2_01
  "UNDEF",    //switch2_02
  "UNDEF",    //switch2_03
  "UNDEF",    //switch2_04
  "UNDEF",    //switch2_05
  "UNDEF",    //switch2_06
  "UNDEF",    //switch2_07
  "UNDEF",    //switch2_08
  "UNDEF",    //switch2_09
  "UNDEF",    //switch2_10
  "UNDEF",    //switch2_11
  "UNDEF",    //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "UNDEF",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_default(controlnames_default);


const char * const controlnames_A10C_1[] PROGMEM = { 
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UFC_1",    //switch2_01
  "UFC_2",    //switch2_02
  "UFC_3",    //switch2_03
  "UFC_4",    //switch2_04
  "UFC_5",    //switch2_05
  "UFC_6",    //switch2_06
  "UFC_7",    //switch2_07
  "UFC_8",    //switch2_08
  "UFC_9",    //switch2_09
  "UFC_CLR",  //switch2_10
  "UFC_10",   //switch2_11
  "UFC_ENT",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "LASTE_RDR_ALTM",    //switch2_15
  "LASTE_AP_TOGGLE",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "LASTE_AP_MODE",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_A10C_1(controlnames_A10C_1);

const char * const controlnames_A10C_2[] PROGMEM = { //VHF AM
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UFC_1",    //switch2_01
  "UFC_2",    //switch2_02
  "UFC_3",    //switch2_03
  "UFC_4",    //switch2_04
  "UFC_5",    //switch2_05
  "UFC_6",    //switch2_06
  "UFC_7",    //switch2_07
  "UFC_8",    //switch2_08
  "UFC_9",    //switch2_09
  "UFC_CLR",  //switch2_10
  "UFC_10",   //switch2_11
  "UFC_ENT",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "LASTE_RDR_ALTM",    //switch2_15
  "LASTE_AP_TOGGLE",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "LASTE_AP_MODE",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_A10C_2(controlnames_A10C_2);

const char * const controlnames_A10C_3[] PROGMEM = { //UHF
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UFC_1",    //switch2_01
  "UFC_2",    //switch2_02
  "UFC_3",    //switch2_03
  "UFC_4",    //switch2_04
  "UFC_5",    //switch2_05
  "UFC_6",    //switch2_06
  "UFC_7",    //switch2_07
  "UFC_8",    //switch2_08
  "UFC_9",    //switch2_09
  "UFC_CLR",  //switch2_10
  "UFC_10",   //switch2_11
  "UFC_ENT",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "LASTE_RDR_ALTM",    //switch2_15
  "LASTE_AP_TOGGLE",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "LASTE_AP_MODE",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_A10C_3(controlnames_A10C_3);

const char * const controlnames_A10C_4[] PROGMEM = { //VHF FM
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UFC_1",    //switch2_01
  "UFC_2",    //switch2_02
  "UFC_3",    //switch2_03
  "UFC_4",    //switch2_04
  "UFC_5",    //switch2_05
  "UFC_6",    //switch2_06
  "UFC_7",    //switch2_07
  "UFC_8",    //switch2_08
  "UFC_9",    //switch2_09
  "UFC_CLR",  //switch2_10
  "UFC_10",   //switch2_11
  "UFC_ENT",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "LASTE_RDR_ALTM",    //switch2_15
  "LASTE_AP_TOGGLE",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "LASTE_AP_MODE",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_A10C_4(controlnames_A10C_4);

const char * const controlnames_A10C_5[] PROGMEM = { //ILS
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UFC_1",    //switch2_01
  "UFC_2",    //switch2_02
  "UFC_3",    //switch2_03
  "UFC_4",    //switch2_04
  "UFC_5",    //switch2_05
  "UFC_6",    //switch2_06
  "UFC_7",    //switch2_07
  "UFC_8",    //switch2_08
  "UFC_9",    //switch2_09
  "UFC_CLR",  //switch2_10
  "UFC_10",   //switch2_11
  "UFC_ENT",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "LASTE_RDR_ALTM",    //switch2_15
  "LASTE_AP_TOGGLE",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "LASTE_AP_MODE",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_A10C_5(controlnames_A10C_5);

const char * const controlnames_A10C_6[] PROGMEM = { //TACAN
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UFC_1",    //switch2_01
  "UFC_2",    //switch2_02
  "UFC_3",    //switch2_03
  "UFC_4",    //switch2_04
  "UFC_5",    //switch2_05
  "UFC_6",    //switch2_06
  "UFC_7",    //switch2_07
  "UFC_8",    //switch2_08
  "UFC_9",    //switch2_09
  "UFC_CLR",  //switch2_10
  "UFC_10",   //switch2_11
  "UFC_ENT",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "LASTE_RDR_ALTM",    //switch2_15
  "LASTE_AP_TOGGLE",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "LASTE_AP_MODE",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_A10C_6(controlnames_A10C_6);


const char * const controlnames_AJS37_1[] PROGMEM = { 
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "NAV_SELECT_BTN_B1",    //switch2_01
  "NAV_SELECT_BTN_B2",    //switch2_02
  "NAV_SELECT_BTN_B3",    //switch2_03
  "NAV_SELECT_BTN_B4",    //switch2_04
  "NAV_SELECT_BTN_B5",    //switch2_05
  "NAV_SELECT_BTN_B6",    //switch2_06
  "NAV_SELECT_BTN_B7",    //switch2_07
  "NAV_SELECT_BTN_B8",    //switch2_08
  "NAV_SELECT_BTN_B9",    //switch2_09
  "NAV_SELECT_BTN_LS",    //switch2_10
  "NAV_SELECT_BTN_BX",    //switch2_11
  "NAV_SELECT_BTN_L_MAL", //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "MASTER_MODE_SELECT",     //enc_01
  "WEAPON_SELECT",          //enc_02
  "ALT_SET",                //enc_03
  "DATAPANEL_SELECTOR",     //enc_04
  "UNDEF",                  //enc_05
      
  "ATTITUDE_HOLD",        //switch2_e1
  "ALTITUDE_HOLD",        //switch2_e2
  "TANK_RELEASE_COVER",   //switch2_e3
  "TANK_RELEASE",         //switch2_e4
  "UNDEF",                //switch2_e5
  
  "DEC", "INC",       //enc_01 Arg
  "DEC", "INC",       //enc_02 Arg
  "-3200", "+3200",   //enc_03 Arg
  "DEC", "INC",       //enc_04 Arg
  "DEC", "INC",       //enc_05 Arg
};
_controllayout_type cl_AJS37_1(controlnames_AJS37_1);

const char * const controlnames_AJS37_2[] PROGMEM = { 
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "NAV_SELECT_BTN_B1",    //switch2_01
  "NAV_SELECT_BTN_B2",    //switch2_02
  "NAV_SELECT_BTN_B3",    //switch2_03
  "NAV_SELECT_BTN_B4",    //switch2_04
  "NAV_SELECT_BTN_B5",    //switch2_05
  "NAV_SELECT_BTN_B6",    //switch2_06
  "NAV_SELECT_BTN_B7",    //switch2_07
  "NAV_SELECT_BTN_B8",    //switch2_08
  "NAV_SELECT_BTN_B9",    //switch2_09
  "NAV_SELECT_BTN_LS",    //switch2_10
  "NAV_SELECT_BTN_BX",    //switch2_11
  "NAV_SELECT_BTN_L_MAL", //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "FR22_INNER_LEFT_KNOB",   //enc_01
  "FR22_OUTER_LEFT_KNOB",   //enc_02
  "FR22_OUTER_RIGHT_KNOB",  //enc_03
  "FR22_INNER_RIGHT_KNOB",  //enc_04
  "UNDEF",                  //enc_05
      
  "ATTITUDE_HOLD",    //switch2_e1
  "ALTITUDE_HOLD",    //switch2_e2
  "TANK_RELEASE_COVER",    //switch2_e3
  "TANK_RELEASE",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "-3200", "+3200", //enc_01 Arg
  "-3200", "+3200", //enc_02 Arg
  "-3200", "+3200", //enc_03 Arg
  "-32000", "+32000", //enc_04 Arg
  "DEC", "INC",     //enc_05 Arg
};
_controllayout_type cl_AJS37_2(controlnames_AJS37_2);


const char * const controlnames_MI8MT_1[] PROGMEM = { 
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "SIG_CAS2_RED",    //switch2_01
  "SIG_CAS1_RED",    //switch2_02
  "UNDEF",          //switch2_03
  "SIG_CAS2_GREEN",   //switch2_04
  "SIG_CAS1_GREEN",   //switch2_05
  "UNDEF",          //switch2_06
  "SIG_CAS2_YELLOW",  //switch2_07
  "SIG_CAS1_YELLOW",  //switch2_08
  "UNDEF",          //switch2_09
  "SIG_CAS2_WHITE",  //switch2_10
  "SIG_CAS1_WHITE",   //switch2_11
  "UV26_STOP_DSP",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "RADIO_SEL_L",    //enc_01
  "HSI_L_CRS",    //enc_02
  "HSI_R_CRS",    //enc_03
  "FUEL_METER_SWITCH",    //enc_04
  "UNDEF",    //enc_05
      
  "SPU7_L_ICS",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "-3200", "+3200", //enc_02 Arg
  "-3200", "+3200", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_MI8MT_1(controlnames_MI8MT_1);

const char * const controlnames_MI8MT_2[] PROGMEM = { 
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "DPL_DEC_DEV",    //switch2_01
  "DPL_INC_DEV",    //switch2_02
  "UNDEF",          //switch2_03
  "DPL_DEC_PATH",   //switch2_04
  "DPL_INC_PATH",   //switch2_05
  "UNDEF",          //switch2_06
  "DPL_DEC_ANGLE",  //switch2_07
  "DPL_INC_ANGLE",  //switch2_08
  "UNDEF",          //switch2_09
  "DPL_OFF_COORD",  //switch2_10
  "DPL_ON_COORD",   //switch2_11
  "UV26_STOP_DSP",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "AUTOPILOT_HDG_ADJ",    //enc_01
  "AUTOPILOT_ROLL_ADJ",    //enc_02
  "AUTOPILOT_PITCH_ADJ",    //enc_03
  "AUTOPILOT_ALT_CHNL",    //enc_04
  "UNDEF",    //enc_05
      
  "AUTOPILOT_HDG_OFF",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "AUTOPILOT_ALT_OFF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "-3200", "+3200", //enc_01 Arg
  "-3200", "+3200", //enc_02 Arg
  "-3200", "+3200", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_MI8MT_2(controlnames_MI8MT_2);

const char * const controlnames_MI8MT_3[] PROGMEM = { 
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "DPL_DEC_DEV",    //switch2_01
  "DPL_INC_DEV",    //switch2_02
  "UNDEF",          //switch2_03
  "DPL_DEC_PATH",   //switch2_04
  "DPL_INC_PATH",   //switch2_05
  "UNDEF",          //switch2_06
  "DPL_DEC_ANGLE",  //switch2_07
  "DPL_INC_ANGLE",  //switch2_08
  "UNDEF",          //switch2_09
  "DPL_OFF_COORD",  //switch2_10
  "DPL_ON_COORD",   //switch2_11
  "UV26_STOP_DSP",  //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "R863_FREQ1",   //enc_01
  "R863_FREQ2",   //enc_02
  "R863_FREQ3",   //enc_03
  "R863_FREQ4",   //enc_04
  "UNDEF",        //enc_05
      
  "UNDEF",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_MI8MT_3(controlnames_MI8MT_3);

const char * const controlnames_MI8MT_4[] PROGMEM = { 
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UNDEF",    //switch2_01
  "UNDEF",    //switch2_02
  "UNDEF",    //switch2_03
  "UNDEF",    //switch2_04
  "UNDEF",    //switch2_05
  "UNDEF",    //switch2_06
  "UNDEF",    //switch2_07
  "UNDEF",    //switch2_08
  "UNDEF",    //switch2_09
  "UNDEF",    //switch2_10
  "UNDEF",    //switch2_11
  "UNDEF",    //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "WPN_SEL",   //enc_01
  "POD_SEL_SWITH",   //enc_02
  "WPN_SEL2",   //enc_03
  "POD_VAR_SEL",   //enc_04
  "UNDEF",        //enc_05
      
  "UNDEF",    //switch2_e1
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5

  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_MI8MT_4(controlnames_MI8MT_4);


const char * const controlnames_F14B_1[] PROGMEM = {
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "PLT_EMERG_STORE_JETT",    //switch2_01
  "PLT_GUN_RATE",    //switch2_02
  "PLT_SIDEWINDER_COOL",    //switch2_03
  "PLT_GEAR_LEVER",    //switch2_04
  "PLT_VDI_MODE_DISP",    //switch2_05
  "PLT_HUD_MODE_A2A",    //switch2_06
  "PLT_NAV_STEER_TACAN",    //switch2_07
  "PLT_NAV_STEER_DEST",    //switch2_08
  "PLT_HUD_MODE_A2G",    //switch2_09
  "PLT_NAV_STEER_AWL",    //switch2_10
  "PLT_NAV_STEER_VECTOR",    //switch2_11
  "PLT_NAV_STEER_MAN",    //switch2_12
  "PLT_MISSLE_PREP",    //switch2_13
  "PLT_HUD_MODE_TAKEOFF",    //switch2_14
  "PLT_HUD_MODE_CRUISE",    //switch2_15
  "PLT_HUD_MODE_LAND",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "PLT_AUTOPLT_VECTOR_CARRIER",    //switch2_e1 
  "PLT_AUTOPLT_ALT",    //switch2_e2
  "PLT_AUTOPLT_HDG",    //switch2_e3
  "PLT_AUTOPLT_ENGAGE",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_F14B_1(controlnames_F14B_1);

const char * const controlnames_F14B_2[] PROGMEM = {
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "PLT_EMERG_STORE_JETT",    //switch2_01
  "PLT_GUN_RATE",    //switch2_02
  "PLT_SIDEWINDER_COOL",    //switch2_03
  "PLT_GEAR_LEVER",    //switch2_04
  "PLT_VDI_MODE_DISP",    //switch2_05
  "PLT_HUD_MODE_A2A",    //switch2_06
  "PLT_NAV_STEER_TACAN",    //switch2_07
  "PLT_NAV_STEER_DEST",    //switch2_08
  "PLT_HUD_MODE_A2G",    //switch2_09
  "PLT_NAV_STEER_AWL",    //switch2_10
  "PLT_NAV_STEER_VECTOR",    //switch2_11
  "PLT_NAV_STEER_MAN",    //switch2_12
  "PLT_MISSLE_PREP",    //switch2_13
  "PLT_HUD_MODE_TAKEOFF",    //switch2_14
  "PLT_HUD_MODE_CRUISE",    //switch2_15
  "PLT_HUD_MODE_LAND",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "PLT_TACAN_DIAL_TENS",    //switch2_e1 
  "PLT_TACAN_DIAL_ONES",    //switch2_e2
  "PLT_TACAN_CHANNEL",    //switch2_e3
  "PLT_TACAN_MODE",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_F14B_2(controlnames_F14B_2);

const char * const controlnames_F14B_3[] PROGMEM = {
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "PLT_EMERG_STORE_JETT",    //switch2_01
  "PLT_GUN_RATE",    //switch2_02
  "PLT_SIDEWINDER_COOL",    //switch2_03
  "PLT_GEAR_LEVER",    //switch2_04
  "PLT_VDI_MODE_DISP",    //switch2_05
  "PLT_HUD_MODE_A2A",    //switch2_06
  "PLT_NAV_STEER_TACAN",    //switch2_07
  "PLT_NAV_STEER_DEST",    //switch2_08
  "PLT_HUD_MODE_A2G",    //switch2_09
  "PLT_NAV_STEER_AWL",    //switch2_10
  "PLT_NAV_STEER_VECTOR",    //switch2_11
  "PLT_NAV_STEER_MAN",    //switch2_12
  "PLT_MISSLE_PREP",    //switch2_13
  "PLT_HUD_MODE_TAKEOFF",    //switch2_14
  "PLT_HUD_MODE_CRUISE",    //switch2_15
  "PLT_HUD_MODE_LAND",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "PLT_UHF1_1_DIAL",    //switch2_e1 
  "PLT_UHF1_110_DIAL",    //switch2_e2
  "PLT_UHF1_01_DIAL",    //switch2_e3
  "PLT_UHF1_025_DIAL",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_F14B_3(controlnames_F14B_3);


//F16 mode:
//MAIN
//
const char * const controlnames_F16_1[] PROGMEM = {
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UNDEF",    //switch2_01
  "UNDEF",    //switch2_02
  "UNDEF",    //switch2_03
  "UNDEF",    //switch2_04
  "UNDEF",    //switch2_05
  "UNDEF",    //switch2_06
  "UNDEF",    //switch2_07
  "UNDEF",    //switch2_08
  "UNDEF",    //switch2_09
  "UNDEF",    //switch2_10
  "UNDEF",    //switch2_11
  "UNDEF",    //switch2_12
  "UNDEF",    //switch2_13
  "UNDEF",    //switch2_14
  "UNDEF",    //switch2_15
  "UNDEF",    //switch2_16
      
  "UNDEF",    //enc_01
  "UNDEF",    //enc_02
  "UNDEF",    //enc_03
  "UNDEF",    //enc_04
  "UNDEF",    //enc_05
      
  "UNDEF",    //switch2_e1 
  "UNDEF",    //switch2_e2
  "UNDEF",    //switch2_e3
  "UNDEF",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_F16_1(controlnames_F16_1);


const char * const controlnames_AV8B_1[] PROGMEM = {
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UFC_B1",    //switch2_01
  "UFC_B2",    //switch2_02
  "UFC_B3",    //switch2_03
  "UFC_B4",    //switch2_04
  "UFC_B5",    //switch2_05
  "UFC_B6",    //switch2_06
  "UFC_B7",    //switch2_07
  "UFC_B8",    //switch2_08
  "UFC_B9",    //switch2_09
  "UFC_ENTER",    //switch2_10
  "UFC_B0",    //switch2_11
  "UFC_DOT",    //switch2_12
  "AG_SEL",    //switch2_13
  "NAV_SEL",    //switch2_14
  "VSTOL_SEL",    //switch2_15
  "UFC_EMCOM",    //switch2_16
      
  "H2O_MODE",    //enc_01
  "STO_LEVER",    //enc_02
  "BINGO_SET",    //enc_03
  "JETT_MODE",    //enc_04
  "UNDEF",    //enc_05
      
  "CMBT",    //switch2_e1 
  "FUEL_DUMP_L",    //switch2_e2
  "FUEL_DUMP_R",    //switch2_e3
  "JETT_STORES",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_AV8B_1(controlnames_AV8B_1);

const char * const controlnames_AV8B_2[] PROGMEM = {
  //define all aircraft DCS-BIOS messages including unused controls (e.g. "UNDEF"), needs to have NUMBER_OF_CONTROLS elements
  "UNDEF",    //switch2_01
  "UNDEF",    //switch2_02
  "UNDEF",    //switch2_03
  "UNDEF",    //switch2_04
  "UNDEF",    //switch2_05
  "UNDEF",    //switch2_06
  "UNDEF",    //switch2_07
  "UNDEF",    //switch2_08
  "UNDEF",    //switch2_09
  "UNDEF",    //switch2_10
  "UNDEF",    //switch2_11
  "UNDEF",    //switch2_12
  "AG_SEL",    //switch2_13
  "NAV_SEL",    //switch2_14
  "VSTOL_SEL",    //switch2_15
  "UFC_EMCOM",    //switch2_16
      
  "H2O_MODE",    //enc_01
  "STO_LEVER",    //enc_02
  "BINGO_SET",    //enc_03
  "JETT_MODE",    //enc_04
  "UNDEF",    //enc_05
      
  "CMBT",    //switch2_e1 
  "FUEL_DUMP_L",    //switch2_e2
  "FUEL_DUMP_R",    //switch2_e3
  "JETT_STORES",    //switch2_e4
  "UNDEF",    //switch2_e5
  
  "DEC", "INC", //enc_01 Arg
  "DEC", "INC", //enc_02 Arg
  "DEC", "INC", //enc_03 Arg
  "DEC", "INC", //enc_04 Arg
  "DEC", "INC", //enc_05 Arg
};
_controllayout_type cl_AV8B_2(controlnames_AV8B_2);



const char * const ajs37MasterModes[] PROGMEM = { 
  "Maintenance",
  "Beredskap  ",
  "Navigering ",
  "Anflygning ",
  "Spaning    ",
  "Landing NAV",
  "Landing P/O",
};

const char * const ajs37WeaponModes[] PROGMEM = { 
  " SJO/PLAN",
  "75/MR/DYK",
  "  LUFT/RR",
  "AKAN-JAKT",
  "   ATTACK",
  "    IR-RB",
};



void onA10VhfAmFrequencySChange(char* newValue) {
  if(encoderPosCount == 2) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<7> a10VhfAmFrequencySBuffer(0x12de, onA10VhfAmFrequencySChange);

void onA10UhfFrequencyChange(char* newValue) {
  if(encoderPosCount == 3) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<7> a10UhfFrequencyBuffer(0x1180, onA10UhfFrequencyChange);

void onA10VhfFmFrequencySChange(char* newValue) {
  if(encoderPosCount == 4) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<7> a10VhfFmFrequencySBuffer(0x12e6, onA10VhfFmFrequencySChange);

void onA10IlsFrequencySChange(char* newValue) {
  if(encoderPosCount == 5) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<6> a10IlsFrequencySBuffer(0x12d8, onA10IlsFrequencySChange);

void onA10TacanChannelChange(char* newValue) {
  if(encoderPosCount == 6) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<4> a10TacanChannelBuffer(0x1162, onA10TacanChannelChange);


void onAjs37MasterModeSelectChange(unsigned int newValue) {
  lcd.setCursor(0, 0);
  lcd.print(ajs37MasterModes[newValue]);
}
DcsBios::IntegerBuffer ajs37MasterModeSelectBuffer(0x4614, 0xe000, 13, onAjs37MasterModeSelectChange);

void onAjs37NavIndicatorData1Change(char* newValue) {
  lcd.setCursor(0, 1);
  lcd.print(newValue);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData1Buffer(0x46a2, onAjs37NavIndicatorData1Change);

void onAjs37NavIndicatorData2Change(char* newValue) {
  lcd.setCursor(1, 1);
  lcd.print(newValue);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData2Buffer(0x46a4, onAjs37NavIndicatorData2Change);

void onAjs37NavIndicatorData3Change(char* newValue) {
  lcd.setCursor(2, 1);
  lcd.print(newValue);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData3Buffer(0x46a6, onAjs37NavIndicatorData3Change);

void onAjs37NavIndicatorData4Change(char* newValue) {
  lcd.setCursor(3, 1);
  lcd.print(newValue);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData4Buffer(0x46a8, onAjs37NavIndicatorData4Change);

void onAjs37NavIndicatorData5Change(char* newValue) {
  lcd.setCursor(4, 1);
  lcd.print(newValue);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData5Buffer(0x46aa, onAjs37NavIndicatorData5Change);

void onAjs37NavIndicatorData6Change(char* newValue) {
  lcd.setCursor(5, 1);
  lcd.print(newValue);
}
DcsBios::StringBuffer<1> ajs37NavIndicatorData6Buffer(0x46ac, onAjs37NavIndicatorData6Change);

void onAjs37WeaponSelectChange(unsigned int newValue) {
  lcd.setCursor(7, 1);
  lcd.print(ajs37WeaponModes[newValue]);
}
DcsBios::IntegerBuffer ajs37WeaponSelectBuffer(0x4600, 0x00e0, 5, onAjs37WeaponSelectChange);


void onMi8R863FreqChange(char* newValue) {
  if (planeId == 3) {
    lcd.setCursor(0, 0);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<7> mi8r863FreqBuffer(0x281c, onMi8R863FreqChange);

void onMi8HdgDegChange(unsigned int newValue) {
  if (planeId == 3) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::IntegerBuffer mi8HdgDegBuffer(0x0436, 0x01ff, 0, onMi8HdgDegChange);

void onMi8IasEuChange(char* newValue) {
  if (planeId == 3) {
    lcd.setCursor(11, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<4> mi8IasEuBuffer(0x0424, onMi8IasEuChange);


void onFc3FuelAllChange(char* newValue) {
  if (planeId == -1) {
    lcd.setCursor(10, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<5> fc3FuelAllBuffer(0x6016, onFc3FuelAllChange);

void onFc3IndicatedAirspeedChange(char* newValue) {
  if (planeId == -1) {
    lcd.setCursor(0, 0);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<4> fc3IndicatedAirspeedBuffer(0x6020, onFc3IndicatedAirspeedChange);

void onFc3AltitudeGroundChange(char* newValue) {
  if (planeId == -1) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<6> fc3AltitudeGroundBuffer(0x6006, onFc3AltitudeGroundChange);


void onF14RioCmdsFlarecntDisplayChange(unsigned int newValue) {
  if(encoderPosCount == 1) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::IntegerBuffer f14RioCmdsFlarecntDisplayBuffer(0x141c, 0x007f, 0, onF14RioCmdsFlarecntDisplayChange);

void onF14RioCmdsChaffcntDisplayChange(unsigned int newValue) {
  if(encoderPosCount == 1) {
    lcd.setCursor(0, 8);
    lcd.print(newValue);
  }
}
DcsBios::IntegerBuffer f14RioCmdsChaffcntDisplayBuffer(0x13fa, 0xfe00, 9, onF14RioCmdsChaffcntDisplayChange);

void onF14HsdTacanRangeSChange(char* newValue) {
  if(encoderPosCount == 2) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<5> f14HsdTacanRangeSBuffer(0x1490, onF14HsdTacanRangeSChange);

void onF14HsdTacanCrsChange(unsigned int newValue) {
  if(encoderPosCount == 2) {
    lcd.setCursor(0, 8);
    lcd.print(newValue);
  }
}
DcsBios::IntegerBuffer f14HsdTacanCrsBuffer(0x149e, 0x01ff, 0, onF14HsdTacanCrsChange);

void onF14PltUhfRemoteDispChange(char* newValue) {
  if(encoderPosCount == 3) {
    lcd.setCursor(0, 1);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<7> f14PltUhfRemoteDispBuffer(0x1472, onF14PltUhfRemoteDispChange);

void onF14PltVuhfRemoteDispChange(char* newValue) {
  if(encoderPosCount == 3) {
    lcd.setCursor(0, 8);
    lcd.print(newValue);
  }
}
DcsBios::StringBuffer<7> f14PltVuhfRemoteDispBuffer(0x1482, onF14PltVuhfRemoteDispChange);


void onAv8bUfcScratchpadChange(char* newValue) {
  lcd.setCursor(0, 1);
  lcd.print(newValue);
}
DcsBios::StringBuffer<12> av8bUfcScratchpadBuffer(0x7984, onAv8bUfcScratchpadChange);



void drawSubmenu() {
  lcd.setCursor(13, 0);
  lcd.print(encoderPosCount);
  lcd.print("/");
  lcd.print(maxSubmenu);
}


void setup() {
  lcd.begin(16, 2);
  DcsBios::setup();
  drawSubmenu();
  lcd.setCursor(0, 0);
  lcd.print("V0.1"); // Flightpannel using DCS BIOS V0.1
  lcd.setCursor(0, 1);
  lcd.print("DCS COMMPANEL"); // Flightpannel using DCS BIOS V0.1
}

void veranderVliegtuig(int newPlaneId, int submenus) {
  planeId = newPlaneId;
  encoderPosCount = 1;
  maxSubmenu = submenus;
  submenuChange();
}

void onAcftNameChange(char* newValue)  {
  g_bRun = false; //signal main loop to skip DcsBios::Loop
   
  delay(500);

  lcd.clear();
  
  if (!strcmp(newValue, "A-10C_2")) { //"A-10C" "A-10C_2"
    veranderVliegtuig(1, 6);
  }
  else if (!strcmp(newValue, "AJS37")) {
    veranderVliegtuig(2, 2);
  }
  else if (!strcmp(newValue, "Mi-8MT") || !strcmp(newValue, "Mi-8MTV2")) {
    veranderVliegtuig(3, 4);
  }
  else if (!strcmp(newValue, "F-14A") || !strcmp(newValue, "F-14A-135-GR") || !strcmp(newValue, "F-14B")) {
    veranderVliegtuig(4, 3);
  }
  else if (!strcmp(newValue, "F-16C_50")) {
    veranderVliegtuig(5, 1);
  }
  else if (!strcmp(newValue, "AV8BNA")) {
    veranderVliegtuig(6, 2);
  }
  else if (!strcmp(newValue, "A-10A") || !strcmp(newValue, "F-15C") || !strcmp(newValue, "MiG-29A") || !strcmp(newValue, "MiG-29G") || !strcmp(newValue, "MiG-29S") ||
           !strcmp(newValue, "Su-25") || !strcmp(newValue, "Su-25T") || !strcmp(newValue, "Su-27") || !strcmp(newValue, "Su-33") || !strcmp(newValue, "J-11A")) {
    veranderVliegtuig(-1, 1);
  }
  else {
    veranderVliegtuig(0, 1);
  }

  g_bRun = true;
}
DcsBios::StringBuffer<16> AcftNameBuffer(0x0000, onAcftNameChange);


void submenuChange() {
  if (encoderPosCount <= 0) {
    encoderPosCount = 1;
  }
  else if (encoderPosCount > maxSubmenu) {
    encoderPosCount = maxSubmenu;
  }

  drawSubmenu();

  if (planeId == 1) {
    lcd.setCursor(0, 0);
    lcd.print("          ");
    switch (encoderPosCount) {
      case 1:
        cl_A10C_1.MakeCurrent();
        break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("VHF AM");
        cl_A10C_2.MakeCurrent();
        break;
      case 3:
        lcd.setCursor(0, 0);
        lcd.print("UHF");
        cl_A10C_3.MakeCurrent();
        break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print("VHF FM");
        cl_A10C_4.MakeCurrent();
        break;
      case 5:
        lcd.setCursor(0, 0);
        lcd.print("ILS");
        cl_A10C_5.MakeCurrent();
        break;
      case 6:
        lcd.setCursor(0, 0);
        lcd.print("TACAN");
        cl_A10C_6.MakeCurrent();
        break;
    }
  }
  else if (planeId == 2) {
    switch (encoderPosCount) {
      case 1:
        cl_AJS37_1.MakeCurrent();
        break;
      case 2:
        cl_AJS37_2.MakeCurrent();
        break;
    }
  }
  else if (planeId == 3) {
    switch (encoderPosCount) {
      case 1:
        cl_MI8MT_1.MakeCurrent();
        break;
      case 2:
        cl_MI8MT_2.MakeCurrent();
        break;
      case 3:
        cl_MI8MT_3.MakeCurrent();
        break;
      case 4:
        cl_MI8MT_4.MakeCurrent();
        break;
    }
  }
  else if (planeId == 4) {
    lcd.setCursor(0, 0);
    lcd.print("          ");
    switch (encoderPosCount) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("Auto Pilot");
        cl_F14B_1.MakeCurrent();
        break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("TACAN");
        cl_F14B_2.MakeCurrent();
        break;
      case 3:
        lcd.setCursor(0, 0);
        lcd.print("UHF 1");
        cl_F14B_2.MakeCurrent();
        break;
    }
  }
  else if (planeId == 5) {
    lcd.setCursor(0, 0);
    lcd.print("F16");
  }
  else if (planeId == 6) {
    lcd.setCursor(0, 0);
    lcd.print("          ");
    switch (encoderPosCount) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("MAIN");
        cl_AV8B_1.MakeCurrent();
        break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("MISC");
        cl_AV8B_2.MakeCurrent();
        break;
  }
  else {
    cl_default.MakeCurrent();
  }
}

void loop() {
  if ( g_bRun ) {
    DcsBios::loop();
  }
  
  aVal = digitalRead(enc5PinA);
  if (aVal != pinALast){ // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(enc5PinB) != aVal) { // Means pin A Changed first - We're Rotating Clockwise
      encoderPosCount++;
      submenuChange();
    } else {// Otherwise B changed first and we're moving CCW
      encoderPosCount--;
      submenuChange();
    }
    pinALast = aVal;
  }
}
