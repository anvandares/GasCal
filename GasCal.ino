#include <Arduino.h>
#include "dht11.h"
#include "mq7.h"
#include "time.h"
#include "WiFi.h"

#include <Wire.h>
unsigned long lastConnectionTime = 0;  // last time you connected to the server, in milliseconds


void setup() {
/* -------------------------------------------------------------------------- */  


  pinMode(gas_ain,INPUT);


  //Initialize serial and wait for port to open:
  Serial.begin(9600);

 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 

  connectToWiFi();
  Serial.println("\nStarting connection to server...");
  
  RTC.begin();
  timeClient.begin();
  timeClient.update();
  auto timeZoneOffsetHours = 2;
  auto unixTime = timeClient.getEpochTime() + (timeZoneOffsetHours * 3600);
  RTCTime timeToSet = RTCTime(unixTime);
  RTC.setTime(timeToSet);


}
/* -------------------------------------------------------------------------- */
void loop() {


  read_request(); 
  
  if(_delay(lastConnectionTime,10000UL)){  // if ten seconds have passed since your last connection,
      httpRequest(client_print());                       // then connect again and send data:  
      lastConnectionTime = millis();   // notes the time that the connection was made:
        

  }
}

String client_print()
{
  
  int gas=detectGas();
  int temp=get_temp();
  int hum=get_hum();
  String time=get_time();
  char reportTemp[1020];
 
  char timeStr[25];

  time.toCharArray(timeStr, 25);
  sprintf(reportTemp, "GET /show/temp/%d/hum/%d/gas/%d/time/%s HTTP/1.1\n", temp, hum, gas, timeStr); //Copies state to string reportTemp.
  Serial.println(reportTemp);

  return reportTemp;

}




