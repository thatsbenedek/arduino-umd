#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";

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
}

void loop() {

}
