#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

// Replace with your WiFi credentials
char ssid[] = "Ritu Mobile";
char pass[] = "harekrishna";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "broker.mqttdashboard.com";
int port = 1883;
const char topic[] = "Gurnoor4778/wave";

const int trig = 4;  // Pin for Trigger of ultrasonic sensor
const int echo = 3;  // Pin for Echo of ultrasonic sensor
const long publishInterval = 5000;  // Time between publishes (5 seconds)

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Connect to WiFi
  Serial.print("Connecting to WiFi...");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT broker
  Serial.print("Connecting to MQTT broker...");
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("Connected to MQTT broker");

  // Set up ultrasonic sensor pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  mqttClient.poll();  // Keep MQTT connection alive

  // Publish a test message every 5 seconds
  static unsigned long lastPublish = 0;
  if (millis() - lastPublish > 5000) {
    lastPublish = millis();
    mqttClient.beginMessage(topic);
    mqttClient.print("Test message");
    mqttClient.endMessage();
    Serial.println("Published a test message");
    }
}