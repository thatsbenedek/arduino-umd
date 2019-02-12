#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

const char* ssid = ""; //SSID of the network to be connected to
const char* password = ""; //password of the network to be connected to
int GMToffset = 1; //GMT offset

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
String UMDclock;

void setup() {
   Serial.begin(9600);

   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) { //displaying connection messages
      Serial.print("%0Dconnecting%Z");
      delay(250);
      if (WiFi.status() != WL_CONNECTED) {
         Serial.print("%0Dconnecting.%Z");
         delay(250);
      }
      if (WiFi.status() != WL_CONNECTED) {
         Serial.print("%0Dconnecting..%Z");
         delay(250);
      }
      if (WiFi.status() != WL_CONNECTED) {
         Serial.print("%0Dconnecting...%Z");
         delay(250);
      }
   }
   Serial.print("%0Dconnected successfully%Z");
   delay(3000);

   Serial.print("%0DIP: "); //displaying IP address
   Serial.print(WiFi.localIP());
   Serial.print("%Z");
   delay(3000);

   timeClient.begin();
   timeClient.setTimeOffset(GMToffset * 3600); //setting GMT offset using the previously provided value
}

void loop() {
   if(!timeClient.update()) { //updating time using NTP
      timeClient.forceUpdate();
   }
   epochTime = timeClient.getEpochTime(); //getting epoch time for displaying the date
   DOW = timeClient.getDay(); //getting day of week
   ti = localtime (&epochTime);

   yearStr = String(ti->tm_year + 1900);
   monthStr = lessThan10(ti->tm_mon + 1);
   dayStr = lessThan10(ti->tm_mday);
   hourStr = lessThan10(ti->tm_hour);
   minuteStr = lessThan10(ti->tm_min);
   secondStr = lessThan10(ti->tm_sec);

   UMDclock = (yearStr + "." + monthStr + "." + dayStr + ".     " + dayOfWeek(DOW) + "      " + hourStr + ":" + minuteStr + ":" + secondStr);
   UMDclock.replace('1', 0x7E); //replacing regular 1's and I's with fixed width characters
   UMDclock.replace('I', 0x7F);
   Serial.print("%0D" + UMDclock + "%Z");
   delay(1000);
}

String lessThan10(int number) { //formatting single digit numbers with a leading zero
   if (number < 10) {
      return ("0" + String(number));
   } else {
      return String(number);
   }
}

String dayOfWeek(int number) { //getting desired DOW string from integer data
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
