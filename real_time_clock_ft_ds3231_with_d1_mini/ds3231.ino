#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
const char* ssid     = "Sagar's";
const char* password  = "juice098";
WiFiUDP ntpUDP;

#include <DS3231.h>
#include <Wire.h>
DS3231 Clock;
#include <NTPClient.h>
// wifi_udp , time_server_pool , offset_in_sec , update_interval_in_sec 
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 19800, 60000);
// Read time
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ))     // from time-lib
// Set time
String formattedDate, dateStamp, formattedTime, TimeStamp, h1_str, t_str;
int splitT, y_dt, m_dt, d_dt, h_tm, m_tm, s_tm, DoW, c_dt, t_num ;
String Ydt_str, Mdt_str, Ddy_str, Htm_str, Mtm_str, Stm_str, Time_str, Date_str, Temp_str, Day_str, ab;


void setup() {
  Serial.begin(115200);
  Serial.println("");
  Wire.begin();
  set_new_time();
}

void loop() {
  update_lcd_time();
  //set_new_time();
}

void update_lcd_time() {
  // send what's going on to the serial monitor.
  // Start with the year
  Serial.print("2");
  if (Century) {      // Won't need this for 89 years.
    Serial.print("1");
  } else {
    Serial.print("0");
  }
  Serial.print(Clock.getYear(), DEC);
  Serial.print(' ');
  // then the month
  Serial.print(Clock.getMonth(Century), DEC);
  Serial.print(' ');
  // then the date
  Serial.print(Clock.getDate(), DEC);
  Serial.print(' ');
  // and the day of the week
  Serial.print(Clock.getDoW(), DEC);
  Serial.print(' ');
  // Finally the hour, minute, and second
  Serial.print(Clock.getHour(h12, PM), DEC);
  Serial.print(' ');
  Serial.print(Clock.getMinute(), DEC);
  Serial.print(' ');
  Serial.print(Clock.getSecond(), DEC);
  // Add AM/PM indicator
  if (h12) {
    if (PM) {
      Serial.print(" PM ");
    } else {
      Serial.print(" AM ");
    }
  } else {
    Serial.print(" 24h ");
  }
  // Display the temperature
  Serial.print("T=");
  Serial.print(Clock.getTemperature(), 2);
  // Tell whether the time is (likely to be) valid
  if (Clock.oscillatorCheck()) {
    Serial.print(" O+");
  } else {
    Serial.print(" O-");
  }
  // Indicate whether an alarm went off
  if (Clock.checkIfAlarm(1)) {
    Serial.print(" A1!");
  }
  if (Clock.checkIfAlarm(2)) {
    Serial.print(" A2!");
  }
  // New line on display
  Serial.print('\n');
  // Display Alarm 1 information
  Serial.print("Alarm 1: ");
  Clock.getA1Time(ADay, AHour, AMinute, ASecond, ABits, ADy, A12h, Apm);
  Serial.print(ADay, DEC);
  if (ADy) {
    Serial.print(" DoW");
  } else {
    Serial.print(" Date");
  }
  Serial.print(' ');
  Serial.print(AHour, DEC);
  Serial.print(' ');
  Serial.print(AMinute, DEC);
  Serial.print(' ');
  Serial.print(ASecond, DEC);
  Serial.print(' ');
  if (A12h) {
    if (Apm) {
      Serial.print('pm ');
    } else {
      Serial.print('am ');
    }
  }
  if (Clock.checkAlarmEnabled(1)) {
    Serial.print("enabled");
  }
  Serial.print('\n');
  // Display Alarm 2 information
  Serial.print("Alarm 2: ");
  Clock.getA2Time(ADay, AHour, AMinute, ABits, ADy, A12h, Apm);
  Serial.print(ADay, DEC);
  if (ADy) {
    Serial.print(" DoW");
  } else {
    Serial.print(" Date");
  }
  Serial.print(' ');
  Serial.print(AHour, DEC);
  Serial.print(' ');
  Serial.print(AMinute, DEC);
  Serial.print(' ');
  if (A12h) {
    if (Apm) {
      Serial.print('pm');
    } else {
      Serial.print('am');
    }
  }
  if (Clock.checkAlarmEnabled(2)) {
    Serial.print("enabled");
  }
  // display alarm bits
  Serial.print('\nAlarm bits: ');
  Serial.print(ABits, BIN);

  Serial.print('\n');
  Serial.print('\n');
  delay(1000);
}


void set_new_time() {
  Serial.println("Connecting Wi-Fi");
  WiFi.begin(ssid, password);
  delay(500);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
  }
  Serial.println("WiFi Connected");
  Serial.println("Getting new Date and Time");
  timeClient.begin();
  timeClient.update();
  
  formattedDate = timeClient.getFormattedDate();
  splitT = formattedDate.indexOf("T");
  dateStamp = formattedDate.substring(0, splitT);
  formattedDate.remove(splitT);
  splitT = formattedDate.indexOf("-");
  dateStamp = formattedDate.substring(0, splitT);
  y_dt = dateStamp.toInt();
  splitT = splitT + 1;
  formattedDate.remove(0, splitT);
  splitT = formattedDate.indexOf("-");
  dateStamp = formattedDate.substring(0, splitT);
  m_dt = dateStamp.toInt();
  splitT = splitT + 1;
  formattedDate.remove(0, splitT);
  splitT = formattedDate.indexOf("-");
  dateStamp = formattedDate.substring(0, splitT);
  d_dt = dateStamp.toInt();

  formattedTime = timeClient.getFormattedTime();
  splitT = formattedTime.indexOf(":");
  TimeStamp = formattedTime.substring(0, splitT);
  h_tm = TimeStamp.toInt();
  splitT = splitT + 1;
  formattedTime.remove(0, splitT);
  splitT = formattedTime.indexOf(":");
  TimeStamp = formattedTime.substring(0, splitT);
  m_tm = TimeStamp.toInt();
  splitT = splitT + 1;
  formattedTime.remove(0, splitT);
  splitT = formattedTime.indexOf(":");
  TimeStamp = formattedTime.substring(0, splitT);
  s_tm = TimeStamp.toInt();
  DoW = dayOfWeek(y_dt, m_dt, d_dt);

  y_dt = y_dt - 48;
  Clock.setClockMode(true);
  Clock.setSecond(s_tm);
  Clock.setMinute(m_tm);
  Clock.setHour(h_tm);
  Clock.setDate(d_dt);
  Clock.setMonth(m_dt);
  Clock.setYear(y_dt);
  Clock.setDoW(DoW);
  WiFi.mode(WIFI_OFF);

  Serial.print("Hour : ");
  Serial.println(h_tm);
  Serial.print("Minute : ");
  Serial.println(m_tm);
  Serial.print("Second : ");
  Serial.println(s_tm);
  Serial.print("Year : ");
  Serial.println(y_dt);
  Serial.print("Hour : ");
  Serial.println(m_dt);
  Serial.print("Hour : ");
  Serial.println(d_dt);
  Serial.print("Day of week : ");
  Serial.println(DoW);
}

int dayOfWeek(uint16_t year, uint8_t month, uint8_t day) {
  uint16_t months[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
  };
  uint32_t days = year * 365;
  for (uint16_t i = 4; i < year; i += 4) if (LEAP_YEAR(i) ) days++;
  days += months[month - 1] + day;
  if ((month > 2) && LEAP_YEAR(year)) days++;
  return days % 7;
}
