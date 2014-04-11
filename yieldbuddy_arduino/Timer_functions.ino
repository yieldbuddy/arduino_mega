#include "Arduino.h"
/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!!!CHECK TIMERS!!CHECK TIMERS!!CHECK TIMERS!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void CheckTimers(){
  //Check Light Timer
  //    Serial1.println();
  //    Serial1.print("Light Schedule Timer: ");
  //    Serial1.println();
  //    Serial1.print("hour: ");
  //    Serial1.print(hour());
  //    Serial1.println();
  //    Serial1.print("minute: ");
  //    Serial1.print(minute());
  //    Serial1.println();
  //    Serial1.print("Light_ON_hour: ");
  //    Serial1.print(Light_ON_hour);
  //    Serial1.println();
  //    Serial1.print("Light_ON_min: ");
  //    Serial1.print(Light_ON_min);
  //    Serial1.println();
  //    Serial1.print("Light_OFF_hour: ");
  //    Serial1.print(Light_OFF_hour);
  //    Serial1.println();
  //    Serial1.print("Light_OFF_min: ");
  //    Serial1.print(Light_OFF_min);
  //    Serial1.println();

  if (Relay6_isAuto == 1){  



    int TurnLightOn = 2;  //0: Turn Off  1: Turn On

    if (Light_ON_hour < Light_OFF_hour) {
      if (hour() >= Light_ON_hour && hour() <= Light_OFF_hour) {
        if (hour() == Light_OFF_hour && minute() < Light_OFF_min) {
          TurnLightOn = 1;
          goto exit_loop_light;          
        }
        if (hour() == Light_ON_hour && minute() >= Light_ON_min) {
          TurnLightOn = 1;
          goto exit_loop_light;          
        }
        if (hour() != Light_OFF_hour && hour() != Light_ON_hour && hour() > Light_ON_hour && hour() < Light_OFF_hour){
          TurnLightOn = 1;
          goto exit_loop_light;
        }
      }
    }

    if (Light_ON_hour > Light_OFF_hour) {
      if (hour() <= Light_OFF_hour || hour() >= Light_ON_hour) {
        if (hour() == Light_OFF_hour && minute() < Light_OFF_min) {
          TurnLightOn = 1;
          goto exit_loop_light;          
        }
        if (hour() == Light_ON_hour && minute() >= Light_ON_min) {
          TurnLightOn = 1;
          goto exit_loop_light;          
        }
        if (hour() != Light_OFF_hour && hour() != Light_ON_hour){
          if (hour() > Light_ON_hour && hour() < 24){
            TurnLightOn = 1;
            goto exit_loop_light;
          }
          if (hour() < Light_OFF_hour) {
            TurnLightOn = 1;
            goto exit_loop_light;
          }
        }
      }
    }

exit_loop_light:;
    if (TurnLightOn == 1) {
      if (Relay6_isAuto == 1){
        Relay6_State = 1;
        EEPROM.write(11,1);
        turnRelay(6, 1);
      }
      //    Serial1.println();
      //    Serial1.println("Turned Light ON");
      //    Serial1.println();
    } 
    else {
      if (Relay6_isAuto == 1){
        Relay6_State = 0;
        EEPROM.write(11,0);
        turnRelay(6, 0);
      }
      //    Serial1.println();
      //    Serial1.println("Turned Light OFF");
      //    Serial1.println();
    }


  }

  //Check Pump Timers

  int Pump_hour_on;
  int Pump_min_on;
  int Pump_hour_off;
  int Pump_min_off;

  int TurnPumpOn = 2;  //0: Turn Off  1: Turn On  2: Unsure


  int i = 0;
  //  Serial1.println();
  //  Serial1.print("Water Pump Timers: ");
  //  Serial1.println();

  for(i=0;i<Pump_times;i++){
    Pump_hour_on = Pump_hour_array[i];
    Pump_min_on  = Pump_min_array[i]; 
    Pump_min_off = Pump_min_on + Pump_for;

    if (Pump_isAM_array[i] == false && Pump_hour_on != 12){
      Pump_hour_on = Pump_hour_on + 12;
      //      Serial1.println("Added 12");
      //      Serial1.println(Pump_hour_on);
    }

    if (Pump_hour_on == 24){
      Pump_hour_on = 12;
      //      Serial1.println("Change 0 to 12");
    }

    Pump_hour_off = Pump_hour_on;

    if (Pump_min_on > 59) {
      Pump_min_on = 60 - Pump_min_on;
      Pump_hour_on++; 
    }
    if (Pump_hour_on > 23) {
      Pump_hour_on = Pump_hour_on - 24; 
    }

    if (Pump_min_off > 59) {
      Pump_min_off = Pump_min_off - 60;
      Pump_hour_off++; 
    }
    if (Pump_hour_off > 23) {
      Pump_hour_off = Pump_hour_off - 24; 
    }

    //    Serial1.print(i);
    //    Serial1.print(") ");
    //    Serial1.print("Hour: ");
    //    Serial1.print(hour());
    //    Serial1.print("   Minute: ");
    //    Serial1.print(minute());
    //    Serial1.print("   On Time: ");
    //    Serial1.print(Pump_hour_on);
    //    Serial1.print(":");
    //    Serial1.print(Pump_min_on);  
    //    Serial1.print("   Off Time: ");
    //    Serial1.print(Pump_hour_off);
    //    Serial1.print(":");
    //    Serial1.print(Pump_min_off);
    //    Serial1.print("   Is AM:");
    //    Serial1.println(Pump_isAM_array[i]);
    //    Serial1.println(); 

    if (Pump_hour_on == 23 && Pump_hour_off < Pump_hour_on) {
      if (Pump_hour_on == hour() && minute() >= Pump_min_on ) {
        SwitchPump(1);
        goto exit_loop_pump;
      }
      if (hour() < Pump_hour_off) {
        SwitchPump(1);
        goto exit_loop_pump;
      }
      if (hour() == Pump_hour_off) {
        if (minute() < Pump_min_off) {
          SwitchPump(1);
          goto exit_loop_pump;   
        }
      }
    }

    if (hour() == Pump_hour_on && hour() <= Pump_hour_off) {
      if (minute() >= Pump_min_on) {
        if (Pump_hour_off != Pump_hour_on && hour() == Pump_hour_off && minute() < Pump_min_off){
          SwitchPump(1);
          goto exit_loop_pump;          
        }
        if (Pump_hour_off != Pump_hour_on && hour() == Pump_hour_on && minute() >= Pump_min_on){
          SwitchPump(1);
          goto exit_loop_pump;          
        }
        if (Pump_hour_off == Pump_hour_on && minute() >= Pump_min_on && minute() < Pump_min_off){
          SwitchPump(1);
          goto exit_loop_pump;
        }
      }

    }
    if (hour() > Pump_hour_on && hour() < Pump_hour_off) {
      SwitchPump(1);
      goto exit_loop_pump;
    }
    if (hour() >= Pump_hour_on && hour() == Pump_hour_off) {
      if (Pump_hour_off != Pump_hour_on && hour() == Pump_hour_off && minute() < Pump_min_off){
        SwitchPump(1);
        goto exit_loop_pump;          
      }
      if (Pump_hour_off != Pump_hour_on && hour() == Pump_hour_on && minute() >= Pump_min_on){
        SwitchPump(1);
        goto exit_loop_pump;          
      }
      if (Pump_hour_off == Pump_hour_on && minute() >= Pump_min_on && minute() < Pump_min_off){
        SwitchPump(1);
        goto exit_loop_pump;
      }
    }


  }

  SwitchPump(TurnPumpOn);
exit_loop_pump:;
}

void SwitchPump(int TurnPumpOn){
  //  Serial1.print("TurnPumpOn: ");
  //  Serial1.println(TurnPumpOn);
  if (TurnPumpOn == 1) {
    if (Relay1_isAuto == 1) {
      Relay1_State = 1;
      EEPROM.write(6,1);
      turnRelay(1, 1);
    }
    if (Relay2_isAuto == 1) {
      Relay2_State = 1;
      EEPROM.write(7,1);
      turnRelay(2, 1);
    }
    //        Serial1.println();
    //        Serial1.println("Turned Water Pump On");
    //        Serial1.println();
  } 
  else if (TurnPumpOn == 0 || TurnPumpOn == 2) {
    if (Relay1_isAuto == 1){
      Relay1_State = 0;
      EEPROM.write(6,0);
      turnRelay(1, 0);
    }
    if (Relay2_isAuto == 1){
      Relay2_State = 0;
      EEPROM.write(7,0);
      turnRelay(2, 0);
    }
    //        Serial1.println();
    //        Serial1.println("Turned Water Pump Off");
    //        Serial1.println();
  }
}

