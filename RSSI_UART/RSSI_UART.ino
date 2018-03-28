#include <SPI.h>
#include <ESP8266WiFi.h>


String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String temp = "";

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT); 

 // Set Station mode
 WiFi.mode(WIFI_STA);
 // Disconnect from AP
 WiFi.disconnect();
 WiFi.softAP("NODE1");

 delay(100);
 //Serial.println("Setup done");
 //WiFi.hostname("NODE1");
}

void loop() {
  //Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  serialEvent();
  if (stringComplete) {
    //Serial.println(inputString);
    // clear the string:
    temp = inputString;
    inputString = "";
    stringComplete = false;
  int length = temp.length();
  temp.remove(length-1);
  temp.remove(length-2);
  int n = WiFi.scanNetworks();
  //Serial.println("scan done");
  if (n == 0) {
    //Serial.println("no networks found");
  } else {
    //Serial.print(n);
    //Serial.println(" networks found");
    //Serial.print(temp);
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      //Serial.print(i + 1);
      //Serial.print(": ");
      //Serial.print(WiFi.SSID(i));
      //Serial.print(" (");
      //Serial.print(WiFi.RSSI(i));
      //Serial.print(")");
      //Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      if (temp == WiFi.SSID(i)) 
      {
        //Serial.print("here: ");
        //Serial.print(WiFi.SSID(i));
        //Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        //Serial.println(")");
      }
      delay(10);
    }
  }
  }
  Serial.println("");

  // Wait a bit before scanning again
delay(5000);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
