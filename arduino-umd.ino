#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

//SSID of the network to be connected to
const char* ssid = "";

//password of the network to be connected to
const char* password = "";

//GMT offset
int GMToffset = 2;

//UMD address
int UMDaddress = 0;

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

   //displaying connection messages
   while (WiFi.status() != WL_CONNECTED) {
      Serial.print(UMDify("connecting"));
      delay(250);
      if (WiFi.status() != WL_CONNECTED) {
         Serial.print(UMDify("connecting."));
         delay(250);
      }
      if (WiFi.status() != WL_CONNECTED) {
         Serial.print(UMDify("connecting.."));
         delay(250);
      }
      if (WiFi.status() != WL_CONNECTED) {
         Serial.print(UMDify("connecting..."));
         delay(250);
      }
   }
   Serial.print(UMDify("connected successfully"));
   delay(3000);

   //displaying IP address
   Serial.print("%" + String(UMDaddress) + "D" + "IP: ");
   Serial.print(WiFi.localIP());
   Serial.print("%Z");
   delay(3000);

   timeClient.begin();

   //setting GMT offset
   timeClient.setTimeOffset(GMToffset * 3600);
}

void loop() {
   //updating time using NTP
   if(!timeClient.update()) {
      timeClient.forceUpdate();
   }

   //getting epoch time for displaying the date
   epochTime = timeClient.getEpochTime();
   
   //getting day of week
   DOW = timeClient.getDay();
   ti = localtime (&epochTime);

   yearStr = String(ti->tm_year + 1900);
   monthStr = lessThan10(ti->tm_mon + 1);
   dayStr = lessThan10(ti->tm_mday);
   hourStr = lessThan10(ti->tm_hour);
   minuteStr = lessThan10(ti->tm_min);
   secondStr = lessThan10(ti->tm_sec);

   UMDclock = (yearStr + "." + monthStr + "." + dayStr + ".     " + dayOfWeek(DOW) + "      " + hourStr + ":" + minuteStr + ":" + secondStr);
   
   //replacing regular 1's and I's with fixed width characters
   UMDclock.replace('1', 0x7E);
   UMDclock.replace('I', 0x7F);
   Serial.print(UMDify(UMDclock));
   delay(1000);
}

//formatting single digit numbers with a leading zero
String lessThan10(int number) {
   if (number < 10) {
      return ("0" + String(number));
   } else {
      return String(number);
   }
}

//getting desired DOW string from integer data
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

//creating an UMD display string
String UMDify(String strparam) {
   return ("%" + String(UMDaddress) + "D" + strparam + "%Z");
}

