#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "";
const char* password = "";
int GMToffset = 1;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedTime;

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
   formattedTime = timeClient.getFormattedTime();
   Serial.println(formattedTime);
   delay(1000);
}
