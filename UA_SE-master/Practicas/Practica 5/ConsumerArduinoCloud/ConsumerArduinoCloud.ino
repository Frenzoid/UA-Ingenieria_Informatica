#include "thingProperties.h";
#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
  #include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
  #include <WiFi101.h>
#elif defined(ARDUINO_ESP8266_ESP12)
  #include <ESP8266WiFi.h>
#endif

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "SE/practicaUA2022/murcia";

String     arduino;
String     numbers[3];

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

void setup() {
  Serial.begin(9600);
  delay(1500);
  
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(SSID);
  while (WiFi.begin(SSID, PASS) != WL_CONNECTED) {
    // failed, retry
    Serial.print("Failed connection to WiFi, retrying...\n");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

 
  initProperties();
  ArduinoCloud.begin(wifi);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  Serial.println();


  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  mqttClient.subscribe(topic);
  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  ArduinoCloud.update();
  
  if (mqttClient.parseMessage()) {
    bool nextIsNumber = FALSE;
    char character;
    
    // Obtain data per character.
    while (mqttClient.available()) {
      character = (char)mqttClient.read();
      
      // Message format is device:number.
      // Ex: Fran:23.
      if (character != ':' && !nextIsNumber) {
        arduino += (char)mqttClient.read();
      } else if (character == ':') {
        nextIsNumber = TRUE;
      } else if ( character != ':' && nextIsNumber) {
        switch (arduino) {
          "fran": numbers[0] += character; break;
          "alex": numbers[0] += character; break;
          "javi": numbers[0] += character; break;
        }
      }
      
    }
    
    // Do median, and publish to observable.
    if (numbers[0] && numbers[1] & numbers[2])  {
      float sum = (numbers[0].toFloat() + numbers[1].toFloat() + numbers[2].toFloat());
      ejercicio = sum / 3;

      // Reset array of numbers
      numbers = {"", "", ""};
    }
  }
}

void onDataChange()  {}
void onEjercicioChange()  {}
