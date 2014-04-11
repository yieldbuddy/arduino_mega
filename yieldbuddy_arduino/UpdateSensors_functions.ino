/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!UPDATE SENSOR VALUES!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

//READ ALL SENSOR VALUES AND CONVERT FOR LCD DISPLAY
void updateSensorValues() {
 
  analogReference(DEFAULT);  //Seems more accurate.
  
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!PH SENSORS!!PH SENSORS!!PH SENSORS!!PH SENSORS!!PH SENSORS!!PH SENSORS!!PH SENSORS!!PH SENSORS!!PH SENSORS!!
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  /*PH1------------------------------------------------*/
  float pH1Sum = 0;
  int j = 0;
  analogRead(pH1Pin);  //Get ADC to switch to correct pin
  delay(20); //Wait for Pin to Change
  
  while(j<30) {
    pH1Sum = pH1Sum + analogRead(pH1Pin);
    j++;
  }
  pH1RawValue = pH1Sum/30;

  pH1Value = (0.0178 * pH1RawValue - 1.889);
  if(isnan(pH1Value)){
    pH1Value = 0;        
  }
  PString my_pH1_string(pH1_char, sizeof(pH1_char));
  if (pH1Value < 10){
    my_pH1_string.print(" "); 
    my_pH1_string.println(pH1Value);
  } 
  else {
    my_pH1_string.println(pH1Value);
  }
  
  
  
  /*PH2------------------------------------------------*/
  float pH2Sum = 0;
  j = 0;
  analogRead(pH2Pin);  //Get ADC to switch to correct pin
  delay(15); //Wait for Pin to Change

  while(j<30) {
    pH2Sum = pH2Sum + analogRead(pH2Pin);
    j++;
  }
  pH2RawValue = pH2Sum/30;

  pH2Value = (0.0178 * pH2RawValue - 1.889);
  if(isnan(pH2Value)){
    pH2Value = 0;        
  }
  PString my_pH2_string(pH2_char, sizeof(pH2_char));
  if (pH2Value < 20){
    my_pH2_string.print(" "); 
    my_pH2_string.println(pH2Value);
  } 
  else {
    my_pH2_string.println(pH2Value);
  }
  
  
  
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!TEMPERATURE SENSOR!!TEMPERATURE SENSOR!!TEMPERATURE SENSOR!!TEMPERATURE SENSOR!!TEMPERATURE SENSOR!!
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  float TempSum = 0;
  j = 0;
  analogRead(TempPin);  //Get ADC to switch to correct pin
  delay(15); //Wait for Pin to Change

  while(j<10) {
    TempSum = TempSum + analogRead(TempPin);
    j++;
  }

  TempRawValue = TempSum/((j-1) * 2);

  TempValue = ((5.00 * TempRawValue * 100.0)/1024.0) + 8.50;
  
  ;  //dht.readTemperature(); to use the DHT11
  if(isnan(TempValue)){
    TempValue = 0;        
  }
  PString my_Temp_string(Temp_char, sizeof(Temp_char));
  my_Temp_string.print(TempValue);
  my_Temp_string.println(" C"); 
  
  
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!HUMIDITY DHT11 SENSOR!!HUMIDITY DHT11 SENSOR!!HUMIDITY DHT11 SENSOR!!HUMIDITY DHT11 SENSOR!!HUMIDITY DHT11!!
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  //       float RHSum = 0;
  //       j = 0;
  //       
  //       while(j<30) {
  //       RHSum = RHSum + ;
  //       j++;
  //       delay(10);
  //       }
  //       RHRawValue = RHSum/30;
  dht.readHumidity();  //The DHT11 Sensor works differently, but for 'good measure'.
  delay(15); //Wait for Pin to Change
  RHValue = dht.readHumidity();
  if (isnan(RHValue)) {
    RHValue = 0;
  } 
  PString my_RH_string(RH_char, sizeof(RH_char));
  my_RH_string.print(RHValue);

  if (RHValue < 10){
    my_RH_string.println("% "); 
  } 
  else {
    my_RH_string.println("%"); 
  }
  
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!TDS1 SENSOR!!TDS1 SENSOR!!TDS1 SENSOR!!TDS1 SENSOR!!TDS1 SENSOR!!TDS1 SENSOR!!TDS1 SENSOR!!TDS1 SENSOR!!TDS1 SENSOR!!
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  float TDS1Sum = 0;
  j = 0;
  analogRead(TDS1Pin);  //Get ADC to switch to correct pin
  delay(15); //Wait for Pin to Change

  while(j<10) {
    TDS1Sum = TDS1Sum + analogRead(TDS1Pin);
    j++;
  }

  TDS1RawValue = TDS1Sum/((j-1) * 2);

  TDS1Value = ((TDS1RawValue * 100.0)/1024.0);
  
  if(isnan(TDS1Value)){
    TDS1Value = 0;        
  }
  PString my_TDS1_string(TDS1_char, sizeof(TDS1_char));
  my_TDS1_string.println(TDS1Value);
  my_TDS1_string.println(" ppm"); 
  
  
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!TDS2 SENSOR!!TDS2 SENSOR!!TDS2 SENSOR!!TDS2 SENSOR!!TDS2 SENSOR!!TDS2 SENSOR!!TDS2 SENSOR!!TDS2 SENSOR!!TDS2 SENSOR!!
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  float TDS2Sum = 0;
  j = 0;
  analogRead(TDS2Pin);  //Get ADC to switch to correct pin
  delay(15); //Wait for Pin to Change

  while(j<10) {
    TDS2Sum = TDS2Sum + analogRead(TDS2Pin);
    j++;
  }

  TDS2RawValue = TDS2Sum/((j-1) * 2);

  TDS2Value = ((TDS2RawValue * 100.0)/1024.0);
  
  if(isnan(TDS2Value)){
    TDS2Value = 0;        
  }
  PString my_TDS2_string(TDS2_char, sizeof(TDS2_char));
  my_TDS2_string.print(TDS2Value);
  my_TDS2_string.println(" ppm"); 
  
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!CO2 SENSOR!!CO2 SENSOR!!CO2 SENSOR!!CO2 SENSOR!!CO2 SENSOR!!CO2 SENSOR!!CO2 SENSOR!!CO2 SENSOR!!CO2 SENSOR!!
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  float CO2Sum = 0;
  j = 0;
  analogRead(CO2Pin);  //Get ADC to switch to correct pin
  delay(15); //Wait for Pin to Change

  while(j<10) {
    CO2Sum = CO2Sum + analogRead(CO2Pin);
    j++;
  }

  CO2RawValue = CO2Sum/((j-1) * 2);

  CO2Value = ((CO2RawValue * 100.0)/1024.0);
  
  if(isnan(CO2Value)){
    CO2Value = 0;        
  }
  PString my_CO2_string(CO2_char, sizeof(CO2_char));
  my_CO2_string.print(CO2Value);
  my_CO2_string.println(" ppm"); 
  
  
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!LIGHT SENSOR!!LIGHT SENSOR!!LIGHT SENSOR!!LIGHT SENSOR!!LIGHT SENSOR!!LIGHT SENSOR!!LIGHT SENSOR!!
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  float LightSum = 0;
  j = 0;
  analogRead(LightPin);  //Get ADC to switch to correct pin
  delay(10); //Wait for Pin to Change
  
  while(j<10) {
    LightSum = LightSum + analogRead(LightPin);
    j++;
  }

  LightRawValue = LightSum/10;

  LightValue = ((LightRawValue * 100.0) / 1024.0);
  
  if (isnan(LightValue)) {
    LightValue = 0;
  } 
  PString my_Light_string(Light_char, sizeof(Light_char));
  my_Light_string.print(LightValue);
  if (LightValue < 10){
    my_Light_string.println("% "); 
  } 
  else {
    my_Light_string.println("%"); 
  }
  
  
  
  

  //pH
  if (pH1Value < pH1Value_Low) {
    pH1_Status = "LOW";
  } 
  else if (pH1Value > pH1Value_Low && pH1Value < pH1Value_High) {
    pH1_Status = "OK";
  } 
  else if (pH1Value > pH1Value_High) {
    pH1_Status = "HIGH";
  }


  if (pH2Value < pH2Value_Low) {
    pH2_Status = "LOW";
  } 
  else if (pH2Value > pH2Value_Low && pH2Value < pH2Value_High) {
    pH2_Status = "OK";
  } 
  else if (pH2Value > pH2Value_High) {
    pH2_Status = "HIGH";
  }

  //Temp
  if (TempValue < TempValue_Low) {
    Temp_Status = "LOW";
  } 
  else if (TempValue > TempValue_Low && TempValue < TempValue_High) {
    Temp_Status = "OK";
  } 
  else if (TempValue > TempValue_High) {
    Temp_Status = "HIGH";
  }
  //RH
  if (RHValue < RHValue_Low) {
    RH_Status = "LOW";
  } 
  else if (RHValue > RHValue_Low && RHValue < RHValue_High) {
    RH_Status = "OK";
  }
  else if (RHValue < RHValue_High) {
    RH_Status = "HIGH";
  }
  //TDS1
  if (TDS1Value < TDS1Value_Low) {
    TDS1_Status = "LOW";
  } 
  else if (TDS1Value > TDS1Value_Low && TDS1Value < TDS1Value_High) {
    TDS1_Status = "OK";
  } 
  else if (TDS1Value < TDS1Value_High) {
    TDS1_Status = "HIGH";
  }
  //TDS2
  if (TDS2Value < TDS2Value_Low) {
    TDS2_Status = "LOW";
  } 
  else if (TDS2Value > TDS2Value_Low && TDS2Value < TDS2Value_High) {
    TDS2_Status = "OK";
  } 
  else if (TDS2Value < TDS2Value_High) {
    TDS2_Status = "HIGH";
  }
  //CO2
  if (CO2Value < CO2Value_Low) {
    CO2_Status = "LOW";
  } 
  else if (CO2Value > CO2Value_Low && CO2Value < CO2Value_High) {
    CO2_Status = "OK";
  } 
  else if (CO2Value > CO2Value_High){
    CO2_Status = "HIGH";
  }
  //Light
  if (LightValue < LightValue_Low) {
    Light_Status = "LOW";
  } 
  else if (LightValue > LightValue_Low && LightValue < LightValue_High) {
    Light_Status = "OK";
  } 
  else if (LightValue < LightValue_High) {
    Light_Status = "HIGH";
  }

}
