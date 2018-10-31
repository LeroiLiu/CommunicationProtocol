#include <ESP8266WiFi.h>

#include "common.h"

void setup()
{
  initSerialBaudRate(115200);
   
  initAPInfo("SSID","PASSWORD");

}

void loop()
{
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
