#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <Arduino.h>

boolean FirstTimeSet = false;
time_t t = now();
String Months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

void setup () {
    Serial.flush();
    Serial.begin(115200);
    Serial.println(__DATE__);
    Serial.println(__TIME__);
    Serial.println();
    char DateChar[] = __DATE__;
    char TimeChar[] = __TIME__;
    Serial.print("Now(): ");
    Serial.println(now() );
    Serial.println();
    
    int i = 0;
    String Date_buffer;
    String Date[4];
    int j = 0;
    while(i < sizeof(DateChar)){
      if (DateChar[i] != ' '){
        Date_buffer = Date_buffer + DateChar[i];
      } else {
        Date[j] = Date_buffer;
        Date_buffer = "";
        Serial.print("Date[");
        Serial.print(j);
        Serial.print("] = ");
        Serial.println(Date[j]);
        j++;
      }
      i++;
    }
    Date[2] = Date_buffer;
    Serial.print("Date[2] = ");
    Serial.println(Date[2]);
    
    int k = 0;
    while(Months[k] != Date[0]){
      k++;
    }
        
    Serial.print("Month: ");
    Serial.println(k+1);
    Serial.print("Day: ");
    Serial.println(Date[1]);
    Serial.print("Year: ");
    Serial.println(Date[2]);
    
    int New_month = k+1;
    int New_day = stringToInt(Date[1]);
    int New_year = stringToInt(Date[2]);
    
    Serial.println();
    
    
    i = 0;
    String Time_buffer;
    String Time[4];
    j = 0;
    while(i < sizeof(TimeChar)){
      if (TimeChar[i] != ':'){
        Time_buffer = Time_buffer + TimeChar[i];
      } else {
        Time[j] = Time_buffer;
        Time_buffer = "";
        Serial.print("Time[");
        Serial.print(j);
        Serial.print("] = ");
        Serial.println(Time[j]);
        j++;
      }
      i++;
    }
    Time[2] = Time_buffer;
    Serial.print("Time[2] = ");
    Serial.println(Time[2]);
    
    Serial.print("Hour: ");
    Serial.println(Time[0]);
    Serial.print("Minute: ");
    Serial.println(Time[1]);
    Serial.print("Second: ");
    Serial.println(Time[2]);
    
    int New_hour = stringToInt(Time[0]);
    int New_minute = stringToInt(Time[1]);
    int New_second = stringToInt(Time[2]);

    //setTime(hr,min,sec,day,month,yr)
    setTime(New_hour,New_minute,New_second,New_day,New_month,New_year);   //<------------  The time will be the time at which this sketch was compiled, otherwise specify a time here.
    
    Serial.println();
    Serial.print("Now(): ");
    Serial.println(now() );
    Serial.println();

    RTC.set(now()+10);  //add ten seconds for upload time.

}

int stringToInt(String string){
  
  char char_string[string.length()+1];
  string.toCharArray(char_string, string.length()+1);
  
  return atoi(char_string);
}

void loop () {        

    delay(3000);
}
