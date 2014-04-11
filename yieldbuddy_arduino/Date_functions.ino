/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void updatelongdate() {

  //MONTH
  char month_buffer[4];
  PString my_month_string(month_buffer, sizeof(month_buffer));
  int monthint = month();

  switch (monthint) {
  case 1:
    my_month_string.println("Jan");
  case 2:
    my_month_string.println("Feb");   
  case 3:
    my_month_string.println("Mar");
  case 4:
    my_month_string.println("Apr");
  case 5:
    my_month_string.println("May");
  case 6:
    my_month_string.println("Jun");
  case 7:
    my_month_string.println("Jul");
  case 8:
    my_month_string.println("Aug");
  case 9:
    my_month_string.println("Sep");
  case 10:
    my_month_string.println("Oct");
  case 11:
    my_month_string.println("Nov");
  case 12:
    my_month_string.println("Dec");
  }


  //DAY
  char day_int_buffer[3];
  PString my_day_string(day_int_buffer, sizeof(day_int_buffer));
  int dayint = day();

  if (dayint < 10){
    my_day_string.print("0");
    my_day_string.println(dayint);
  } 
  else {
    my_day_string.println(dayint);
  }

  //YEAR
  char year_int_buffer[5];
  PString my_year_string(year_int_buffer, sizeof(year_int_buffer));
  int yearint = year();
  my_year_string.println(yearint);

  //HOUR
  char hour_int_buffer[3];
  PString my_hour_string(hour_int_buffer, sizeof(hour_int_buffer));
  int hourint = hour();
  if (hourint > 12) {
    hourint = hourint - 12; 
  }

  if (hourint < 10) {
    my_hour_string.print("0");
    my_hour_string.println(hourint);
  } 
  else {
    my_hour_string.println(hourint);
  }

  //MINUTE
  char minute_int_buffer[3];
  PString my_minute_string(minute_int_buffer, sizeof(minute_int_buffer));
  int minuteint = minute();

  if (minuteint < 10){
    my_minute_string.print("0");
    my_minute_string.println(minuteint);
  } 
  else {
    my_minute_string.println(minuteint);
  }

  if (last_minute != minute()) {   //CODE THAT IS EXECUTED WHEN THE VALUE minute() CHANGES
    EEPROM.write(0,hour());
    EEPROM.write(1,minute());
    EEPROM.write(2,second());
    EEPROM.write(3,day());
    EEPROM.write(4,month());
    EEPROM.write(5,year());
  }

  last_minute = minute();

  //SECOND
  char second_int_buffer[3];
  PString my_second_string(second_int_buffer, sizeof(second_int_buffer));
  int secondint = second();


  if (secondint < 10){
    my_second_string.print("0");
    my_second_string.println(secondint);
  } 
  else {
    my_second_string.println(secondint);
  }

  // AM/PM
  char am_pm_buffer[3];
  PString my_am_pm_string(am_pm_buffer, sizeof(am_pm_buffer));

  if (isAM() ==true){
    my_am_pm_string.println("AM");
  } 
  else if (isAM()==false) {
    my_am_pm_string.println("PM");
  }
  //COMBINED LONG FORMAT DATE
  // updates char longdate[22];
  PString my_longdate_string(longdate, sizeof(longdate));
  my_longdate_string.print(month_buffer);
  my_longdate_string.print(" ");
  my_longdate_string.print(day_int_buffer);
  my_longdate_string.print(", ");
  my_longdate_string.print(year_int_buffer);
  my_longdate_string.print(" ");
  my_longdate_string.print(hour_int_buffer);
  my_longdate_string.print(":");
  my_longdate_string.print(minute_int_buffer);
  my_longdate_string.print(":");
  my_longdate_string.print(second_int_buffer);
  my_longdate_string.print(" ");
  my_longdate_string.println(am_pm_buffer);
}
