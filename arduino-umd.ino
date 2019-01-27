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
   ti = localtime (&epochTime);

   yearStr = String(ti->tm_year + 1900);
   monthStr = lessThan10(ti->tm_mon + 1);
   dayStr = lessThan10(ti->tm_mday);
   hourStr = lessThan10(ti->tm_hour);
   minuteStr = lessThan10(ti->tm_min);
   secondStr = lessThan10(ti->tm_sec);

   Serial.print(yearStr + "." + monthStr + "." + dayStr + ". ");
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
