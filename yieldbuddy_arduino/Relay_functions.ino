/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!turnRelay!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void turnRelay(int Relay_num, int TurnOnOff){
  int Relay_Pin[6] = {
    Relay1_Pin, Relay2_Pin, Relay3_Pin, Relay4_Pin, Relay5_Pin, Relay6_Pin  };

  if (Relay_num < 6) {
    //Relay Board works opposite (Low/High) (Relays 1 - 5)
    if (TurnOnOff == 1) {
      digitalWrite(Relay_Pin[Relay_num - 1], LOW);
    }

    if(TurnOnOff == 0) {
      digitalWrite(Relay_Pin[Relay_num - 1], HIGH);      
    }
  } 
  else if (Relay_num == 6) {
    //SSR relay works as expected (High/Low) (Relay 6)
    if (TurnOnOff == 1) {
      digitalWrite(Relay_Pin[Relay_num - 1], HIGH);  
    }

    if(TurnOnOff == 0) {
      digitalWrite(Relay_Pin[Relay_num - 1], LOW);      
    }
  }
  sendRelayMessages(); // (through serial)
}

void FillPumpTimesArrays(int tmp_Pump_start_hour, int tmp_Pump_start_min, int tmp_Pump_every_hours, int tmp_Pump_every_mins, int tmp_Pump_for, int tmp_Pump_times) {
  tmp_Pump_hour_array[0] = tmp_Pump_start_hour;
  tmp_Pump_min_array[0] = tmp_Pump_start_min;
  tmp_Pump_isAM_array[0] = tmp_Pump_start_isAM;

  if (tmp_Pump_start_hour > 12) {
    tmp_Pump_isAM_array[0] = false;
  }


  int i = 0;
  for(i = 0; i < tmp_Pump_times; i++){

    tmp_Pump_hour_array[i] = tmp_Pump_start_hour + ((i) * tmp_Pump_every_hours);
    tmp_Pump_min_array[i] = tmp_Pump_start_min + ((i) * tmp_Pump_every_mins);


    while (tmp_Pump_min_array[i] > 59) {
      tmp_Pump_min_array[i] = tmp_Pump_min_array[i] - 60;
      tmp_Pump_hour_array[i]++;
    }

    int AMPM_int = tmp_Pump_hour_array[i] / 12;

    while (tmp_Pump_hour_array[i] > 12) {
      tmp_Pump_hour_array[i] = tmp_Pump_hour_array[i] - 12;
    }

    Serial1.println();
    Serial1.print("tmp_Pump_start_isAM:");       
    Serial1.print(tmp_Pump_start_isAM);       
    Serial1.println();
    Serial1.print(tmp_Pump_hour_array[i]);
    Serial1.print(") ");
    Serial1.print(AMPM_int);
    Serial1.println();

    boolean case_zero = false;
    switch (AMPM_int) {
    case 0:
      case_zero = true;
      if (tmp_Pump_start_isAM == true) {
        tmp_Pump_isAM_array[i] = true;
      } 
      else {
        tmp_Pump_isAM_array[i] = false;
      }
      break;
    case 1:
      if (case_zero == true){
        if (tmp_Pump_start_isAM == true) {
          tmp_Pump_isAM_array[i] = false;
        } 
        else {
          tmp_Pump_isAM_array[i] = true;
        }
      } 
      else {
        if (tmp_Pump_start_isAM == true) {
          tmp_Pump_isAM_array[i] = false;
        } 
        else {
          tmp_Pump_isAM_array[i] = true;
        }
      }
      break;
    case 2:
      if (case_zero == true){
        if (tmp_Pump_start_isAM == true) {
          tmp_Pump_isAM_array[i] = false;
        } 
        else {
          tmp_Pump_isAM_array[i] = true;
        }
      } 
      else {
        if (tmp_Pump_start_isAM == true) {
          tmp_Pump_isAM_array[i] = true;
        } 
        else {
          tmp_Pump_isAM_array[i] = false;
        }
      }
      break;
    case 3:
      if (case_zero == true){
        if (tmp_Pump_start_isAM == true) {
          tmp_Pump_isAM_array[i] = true;
        } 
        else {
          tmp_Pump_isAM_array[i] = false;
        }
      } 
      else {
        if (tmp_Pump_start_isAM == true) {
          tmp_Pump_isAM_array[i] = false;
        } 
        else {
          tmp_Pump_isAM_array[i] = true;
        }
      }
      break;
    case 4:
      if (case_zero == true){
        if (tmp_Pump_start_isAM == true) {
          tmp_Pump_isAM_array[i] = false;
        } 
        else {
          tmp_Pump_isAM_array[i] = true;
        }
      } 
      else {
        if (tmp_Pump_start_isAM == true) {
          tmp_Pump_isAM_array[i] = true;
        } 
        else {
          tmp_Pump_isAM_array[i] = false;
        }
      }
      break;
    }
  }
}

