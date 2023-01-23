/** 
 * Author: MrFrenzoid 
 * Date: 04/03/2022
 * Device: Arduino NANO 33 IoT With headers.
 * Libraries: WiFiNINA
 */

#include <WiFiNINA.h>

// SSID and PASSWORD
#define SSID        "arduino"
#define PASSWORD    "okokokok"

// Wifi status, used to avoid executing reduntant tasks, such as printing messages and managing leds.
bool connected = false;

void setup() {
  // setup serial output
  Serial.begin(9600);
  
  // Setup leds
  pinMode(LED_BUILTIN, OUTPUT);

  // Turn led on on start.
  led_on();

  // Try connecting to wifi.
  wifi_connect();
}

void loop() {
  /** If the device is not connected to the wifi network,
   *  blink the led and try to connect,
   *  and if it succesfully connects, turn the led off.
   *  
   *  If the device was previusly connected, then show an error message.
   */
  if (WiFi.status() != WL_CONNECTED) {
    if(connected == true) {
      Serial.println("Connection lost!");
      connected = false;
    }
        
    led_off();    
    led_blink(100, 700); // With 100ms per blink sequence, and 700ms per sequece = (5+4+3+2+1) * 100 + 5 * 700 = 5000ms = 5 seconds per retry.
    Serial.println("Error connecting to wifi network '" + (String)SSID + "' after 5 seconds, retrying...");
    
    wifi_connect();

  } else {
    if (!connected) {
      connected = true;
      Serial.println("Wifi connected succefully!"); 
      led_off();
    }
  }
}

int wifi_connect() {
  return WiFi.begin(SSID, PASSWORD);
}

void led_on() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void led_off() {
  digitalWrite(LED_BUILTIN, LOW);
}

void led_blink(int del_time, int seq_time) {
  for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= i; j++ ) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(del_time);
      digitalWrite(LED_BUILTIN, LOW);
      delay(del_time);
    }
    
    // Time delay between blink sequences.
    delay(seq_time);
  }
}
