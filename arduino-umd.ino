#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

const char* ssid = "";
const char* password = "";
int GMToffset = 1;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
time_t epochTime;
struct tm *ti;

String yearStr;
String monthStr;
String dayStr;
String hourStr;
String minuteStr;
String secondStr;
int DOW;

void setup() {
   Serial.begin(9600);

   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
      Serial.println("connecting");
      delay(250);
      if (WiFi.status() != WL_CONNECTED) {
         Serial.println("connecting.");
         delay(250);
      }
      if (WiFi.status() != WL_CONNECTED) {
         Serial.println("connecting..");
         delay(250);
      }
      if (WiFi.status() != WL_CONNECTED) {
         Serial.println("connecting...");
         delay(250);
      }
   }
   Serial.println("connected successfully");
   delay(1000);

   Serial.print("IP: ");
   Serial.println(WiFi.localIP());
   delay(3000);

   timeClient.begin();
   timeClient.setTimeOffset(GMToffset * 3600);
}

void loop() {
   if(!timeClient.update()) {
      timeClient.forceUpdate();
   }
   epochTime = timeClient.getEpochTime();
   DOW = timeClient.getDay();
   ti = localtime (&epochTime);

   yearStr = String(ti->tm_year + 1900);
   monthStr = lessThan10(ti->tm_mon + 1);
   dayStr = lessThan10(ti->tm_mday);
   hourStr = lessThan10(ti->tm_hour);
   minuteStr = lessThan10(ti->tm_min);
   secondStr = lessThan10(ti->tm_sec);

   Serial.print(yearStr + "." + monthStr + "." + dayStr + ". ");
   Serial.print(dayOfWeek(DOW) + " ");
   Serial.println(hourStr + ":" + minuteStr + ":" + secondStr);
   delay(1000);
}

String lessThan10(int number) {
   if (number < 10) {
      return ("0" + String(number));
   } else {
      return String(number);
   }
}

String dayOfWeek(int number) {
   switch (number) {
      case 0: return "SUN";
      case 1: return "MON";
      case 2: return "TUE";
      case 3: return "WED";
      case 4: return "THU";
      case 5: return "FRI";
      case 6: return "SAT";
   }
}
