#include <Time.h>
#include <PString.h>
#include <DHT.h>
#include <EEPROM.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <avr/pgmspace.h>
#include "Arduino.h"

/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

String Serial_inString = "";
boolean stringComplete = false;
int serialcounter = 0;

char longdate[25] = "Jan 01, 2012 12:00:00 PM";
char pH1_char[6] = "00.00";
char pH2_char[6] = "00.00";
char Temp_char[8]= "";
char RH_char[7] = "00.00%";
char TDS1_char[11] = "0000.0ppm";
char TDS2_char[11] = "0000.0ppm";
char CO2_char[8] = "00.00%";
char Light_char[7] = "00.00%";

//Temporary placeholders for Time Settings Screen
int tmp_month;
int tmp_day;
int tmp_year;
int tmp_hour;
int tmp_minute;
int tmp_second;

int last_minute;

//Note: Committed Time Settings are stored as their associated month(), day(), year(), etc... as per <Time.h>

//Hours of the day array
String DayHours[24] = {
  "12:00 AM"," 1:00 AM"," 2:00 AM"," 3:00 AM"," 4:00 AM"," 5:00 AM"," 6:00 AM"," 7:00 AM"," 8:00 AM"," 9:00 AM","10:00 AM","11:00 AM",
  "12:00 PM"," 1:00 PM"," 2:00 PM"," 3:00 PM"," 4:00 PM"," 5:00 PM"," 6:00 PM"," 7:00 PM"," 8:00 PM"," 9:00 PM","10:00 PM","11:00 PM"};

//Temporary placeholders for Light Schedule Screen
int tmp_send;
int tmp_Light_ON_hour;
int tmp_Light_ON_min;
int tmp_Light_OFF_hour;
int tmp_Light_OFF_min;

//Committed Light Settings
int Light_ON_hour = 0;
int Light_ON_min = 0;
int Light_OFF_hour = 18;
int Light_OFF_min = 0;

//Temporary placeholders for Pump Schedule Screen
int tmp_Pump_start_hour;
int tmp_Pump_start_min;
boolean tmp_Pump_start_isAM = true;
int tmp_Pump_every_hours;
int tmp_Pump_every_mins;
int tmp_Pump_for; //In Minutes
int tmp_Pump_times; //Number of times per day

int tmp_Pump_hour_array[16];
int tmp_Pump_min_array[16];
boolean tmp_Pump_isAM_array[16];

//Committed Pump Schedule Settings
int Pump_start_hour = 7;
int Pump_start_min = 15;
boolean Pump_start_isAM = true;
int Pump_every_hours = 2;
int Pump_every_mins = 30;
int Pump_for = 15; //In Minutes
int Pump_times = 1; //Number of times per day

int Pump_hour_array[16];
int Pump_min_array[16];
boolean Pump_isAM_array[16];


/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!SENSOR VARIABLES!!SENSOR VARIABLES!!SENSOR VARIABLES!!SENSOR VARIABLES!!SENSOR VARIABLES!!SENSOR VARIABLES!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

//Values the arduino sees
int pH1RawValue = 0;
int pH2RawValue = 0;
int TempRawValue = 0;
int RHRawValue = 0;
int TDS1RawValue = 0;
int TDS2RawValue = 0;
int CO2RawValue = 0;
int LightRawValue = 0;

//Values the humans see (after it has been calculated using raw values above ^^^ and their respected formulas)
float pH1Value = 0;
float pH2Value = 0;
float TempValue = 0;
float RHValue = 0;
float TDS1Value = 0;
float TDS2Value = 0;
float CO2Value = 0;
float LightValue = 0;

//PH
//Status Indicator Values
String pH1_Status = "OK";
float pH1Value_Low = 5.60;
float pH1Value_High = 6.10;

String pH2_Status = "OK";
float pH2Value_Low = 5.60;
float pH2Value_High = 6.10;

//Temp
String Temp_Status = "OK";
float TempValue_Low = 21.00;
float TempValue_High = 29.00;
//Accessory ON/OFF Values
float Heater_ON = 21.00;
float Heater_OFF = 25.00;
float AC_ON = 29.00;
float AC_OFF = 25.00;


//Humidty(RH)
String RH_Status = "OK";
float RHValue_Low = 30.00;
float RHValue_High = 80.00;
//Accessory ON/OFF Values
float Humidifier_ON = 40.00;
float Humidifier_OFF = 60.00;
float Dehumidifier_ON = 80.00;
float Dehumidifier_OFF = 60.00;

//TDS1
String TDS1_Status = "OK";
float TDS1Value_Low = 500.0;
float TDS1Value_High = 800.0;
//Accessory ON/OFF Values
float NutePump1_ON = 500.0;
float NutePump1_OFF = 800.0;
boolean MixPump1_Enabled = true;

//TDS2
String TDS2_Status = "OK";
float TDS2Value_Low = 500.0;
float TDS2Value_High = 800.0;
//Accessory ON/OFF Values
float NutePump2_ON = 500.0;
float NutePump2_OFF = 800.0;
boolean MixPump2_Enabled = true;

//CO2
String CO2_Status = "OK";
float CO2Value_Low = 60.00;
float CO2Value_High= 75.00;
//Accessory ON/OFF Values
float CO2_ON = 40.00;
float CO2_OFF = 60.00 ;
boolean CO2_Enabled = true;

//Light
String Light_Status = "OK";
float LightValue_Low = 20.00;
float LightValue_High = 95.00;


/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!PIN DEFINITIONS!!PIN DEFINITIONS!!PIN DEFINITIONS!!PIN DEFINITIONS!!PIN DEFINITIONS!!PIN DEFINITIONS!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
int pH1Pin = A3;
int pH2Pin = A4;
int TempPin = A0;

//RH
#define DHTPIN 28
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

int TDS1Pin = A5;
int TDS2Pin = A6;
int CO2Pin = A1;
int LightPin = A2;

int Relay1_Pin = 27;  //Water Pump 1
int Relay2_Pin = 26;  //Water Pump 2
int Relay3_Pin = 25;  //Free
int Relay4_Pin = 24;  //Free
int Relay5_Pin = 23;  //Free
int Relay6_Pin = 22;  //Light/Ballast

int Relay1_State = 0;
int Relay2_State = 0;
int Relay3_State = 0;
int Relay4_State = 0;
int Relay5_State = 0;
int Relay6_State = 0;

int Relay1_isAuto = 1;  //Water Pump 1
int Relay2_isAuto = 1;  //Water Pump 2
int Relay3_isAuto = 0;  //Free
int Relay4_isAuto = 0;  //Free
int Relay5_isAuto = 0;  //Free
int Relay6_isAuto = 1;  //Light/Ballast

/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void setup()
{
  //Set Pin Modes
  pinMode(Relay1_Pin, OUTPUT);
  pinMode(Relay2_Pin, OUTPUT);
  pinMode(Relay3_Pin, OUTPUT);
  pinMode(Relay4_Pin, OUTPUT);
  pinMode(Relay5_Pin, OUTPUT);
  pinMode(Relay6_Pin, OUTPUT);

  //COMMENT OUT THIS SECTION ON FIRST START UP!!-----------------------------------
  //EEPROM TIME
  int eeprom_hr = EEPROM.read(0);
  int eeprom_min = EEPROM.read(1);
  int eeprom_sec = EEPROM.read(2);
  int eeprom_day = EEPROM.read(3);
  int eeprom_month = EEPROM.read(4);
  int eeprom_yr = EEPROM.read(5);

  //EEPROM RELAYS
  Relay1_State = 0; //EEPROM.read(6);     //Water-Pump 1
  Relay2_State = 0; //EEPROM.read(7);     //Water-Pump 2
  Relay3_State = 0; //EEPROM.read(8);     //Free
  Relay4_State = 0; //EEPROM.read(9);     //Free
  Relay5_State = 0; //EEPROM.read(10);    //Free
  Relay6_State = 0; //EEPROM.read(11);    //Light/Ballast

  Relay1_isAuto = EEPROM.read(211);  //Water Pump 1
  Relay2_isAuto = EEPROM.read(212);  //Water Pump 2
  Relay3_isAuto = EEPROM.read(213);    //Free
  Relay4_isAuto = EEPROM.read(214);    //Free
  Relay5_isAuto = EEPROM.read(215);   //Free
  Relay6_isAuto = EEPROM.read(216);  //Light/Ballast  


  //Safe-Route ---> Disregard last known states and turn all relays off (auto will take over):
    turnRelay(1, 0);
    turnRelay(2, 0);
    turnRelay(3, 0);
    turnRelay(4, 0);
    turnRelay(5, 0);
    turnRelay(6, 0);


  //If Relay is not set for automatic mode, then resume last known state 
  //(ie. Set relay as it was before a power failure?)
  //  if (Relay1_State == 0 && Relay1_isAuto == 0) {
  //   turnRelay(1, 0); 
  //  } else if (Relay2_State == 1 && Relay2_isAuto == 0){
  //   turnRelay(1, 1);
  //  }
  //  if (Relay2_State == 0 && Relay2_isAuto == 0) {
  //   turnRelay(2, 0); 
  //  } else if (Relay1_State == 1 && Relay2_isAuto == 0){
  //   turnRelay(2, 1);
  //  }
  //  if (Relay3_State == 0 && Relay3_isAuto == 0) {
  //   turnRelay(3, 0); 
  //  } else if (Relay3_State == 1 && Relay3_isAuto == 0){
  //   turnRelay(3, 1);
  //  }
  //  if (Relay4_State == 0 && Relay4_isAuto == 0) {
  //   turnRelay(4, 0); 
  //  } else if (Relay4_State == 1 && Relay4_isAuto == 0){
  //   turnRelay(4, 1);
  //  }
  //  if (Relay5_State == 0 && Relay5_isAuto == 0) {
  //   turnRelay(5, 0); 
  //  } else if (Relay5_State == 1 && Relay5_isAuto == 0){
  //   turnRelay(5, 1);
  //  }
  //  if (Relay6_State == 0 && Relay6_isAuto == 0) {
  //   turnRelay(6, 0); 
  //  } else if (Relay6_State == 1 && Relay6_isAuto == 0){
  //   turnRelay(6, 1);
  //  }


  //EEPROM Water Pump Schedule
  Pump_start_hour = EEPROM.read(21);
  Pump_start_min = EEPROM.read(22);
  Pump_every_hours = EEPROM.read(23);
  Pump_every_mins = EEPROM.read(24);
  Pump_for = EEPROM.read(25);
  Pump_times = EEPROM.read(26);

  int i = 0;
  for(i = 0; i < 16; i++){
    Pump_hour_array[i] =  EEPROM.read(i+27);
    Pump_min_array[i] = EEPROM.read(i+43);
    Pump_isAM_array[i] = EEPROM.read(i+59);
  }

  //EEPROM Light Schedule
  Light_ON_hour = EEPROM.read(76);
  Light_ON_min = EEPROM.read(209);
  Light_OFF_hour = EEPROM.read(77);
  Light_OFF_min = EEPROM.read(210);

  //EEPROM pH1 Settings
  pH1Value_Low = eepromReadFloat(78);
  pH1Value_High = eepromReadFloat(82);

  //EEPROM pH2 Settings
  pH2Value_Low = eepromReadFloat(180);
  pH2Value_High = eepromReadFloat(184);

  //EEPROM Temp Settings
  TempValue_Low  = eepromReadFloat(86);
  TempValue_High = eepromReadFloat(90);
  Heater_ON = eepromReadFloat(94);
  Heater_OFF =eepromReadFloat(98);
  AC_ON = eepromReadFloat(102);
  AC_OFF = eepromReadFloat(106);

  //EEPROM RH Settings
  RHValue_Low = eepromReadFloat(110);
  RHValue_High = eepromReadFloat(114);
  Humidifier_ON = eepromReadFloat(118);
  Humidifier_OFF = eepromReadFloat(122);
  Dehumidifier_ON = eepromReadFloat(126);
  Dehumidifier_OFF = eepromReadFloat(130);

  //EEPROM TDS1 Settings
  TDS1Value_Low = eepromReadFloat(134);
  TDS1Value_High = eepromReadFloat(139);
  NutePump1_ON = eepromReadFloat(144);
  NutePump1_OFF = eepromReadFloat(149);
  if (EEPROM.read(154) == 1){
    MixPump1_Enabled = true;
  } 
  else {
    MixPump1_Enabled = false;
  }

  //EEPROM TDS2 Settings
  TDS2Value_Low = eepromReadFloat(188);
  TDS2Value_High = eepromReadFloat(193);
  NutePump2_ON = eepromReadFloat(198);
  NutePump2_OFF = eepromReadFloat(203);
  if (EEPROM.read(208) == 1){
    MixPump2_Enabled = true;
  } 
  else {
    MixPump2_Enabled = false;
  }


  //EEPROM CO2 Settings
  CO2Value_Low = eepromReadFloat(155);
  CO2Value_High = eepromReadFloat(159);
  CO2_ON = eepromReadFloat(163);
  CO2_OFF = eepromReadFloat(167);
  if (EEPROM.read(171) == 1){
    CO2_Enabled = true;
  } 
  else {
    CO2_Enabled = false;
  }
  //
  //EEPROM Light Settings
  LightValue_Low = eepromReadFloat(172);
  LightValue_High = eepromReadFloat(176);


  //------------------------------------------------------------------------------

  //Load default time first, then try the RTC.
  //Set-Time  setTime(hr,min,sec,day,month,yr);
  setTime(0,0,0,1,1,2013);
  setSyncProvider(RTC.get);

  Serial1.begin(115200);
}


/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void loop()
{
  
  
  //Clear the EEPROM and then write defaults.
  for (int i = 0; i < 4096; i++) {
    EEPROM.write(i, 0);
  }
  delay(1000); 

  RestoreDefaults();
  turnRelay(1,1);
  delay(1000);
  turnRelay(1,0);
  //delay(30000);
  //delay(30000);
  
  
  
  while (1){
  updatelongdate();
  updateSensorValues();
  serialEvent();
  sendserialmessages();
  CheckTimers();
  serialEvent();
  CheckSetPoints();
  }
}











