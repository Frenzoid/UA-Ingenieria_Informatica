
/** 
 * Author: MrFrenzoid 
 * Date: 14/03/2022
 * Device: Arduino NANO 33 IoT With headers.
 * Libraries: WiFiNINA, ArduinoBLE
 */

#include <ArduinoBLE.h>
#include <WiFiNINA.h>

// SSID and PASSWORD
#define SSID        "arduino"
#define PASSWORD    "okokokok"


void setup() {
  // The WiFi radio's status.
  int status = WL_IDLE_STATUS; 
  
  // setup serial output
  Serial.begin(9600);
  while (!Serial) {
      // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(SSID);
    
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(SSID, PASSWORD);

    // wait 5 seconds for connection:
    delay(5000);
  }
  
  // Once connected, notify via serial monitor, and try BLE scanning.
  Serial.println("connected to the network");
  Serial.println("Starting BLE.");

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");

    while (1);
  }

  // The device will get stucked because the WiFi library is now unresponsive...
  //   since the BLE stole the access right to the antena.
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Disconnected from network!!");
  }
  
  // Won't do cause the device's stucked...
  Serial.println("Starting BLE Scanning...");
  BLE.scan();
}


void loop() {}
