#include <WiFiNINA.h>
#include <Wire.h>
#include <BH1750.h>

char wifiSSID[] = "Gurnoor Kaushal"; 
char wifiPassword[] = "gurnoork";

WiFiClient client;

BH1750 lightSensor; 
const int ledPinNumber = 2;
String queryParams = "?val1=57&val2=25"; 
const char* iftttHostName = "maker.ifttt.com"; 
String iftttEndpoint = "https://maker.ifttt.com/trigger/Light_sensor/with/key/m5aKFQw7anGcbxJtr7d9Oc2X8AbrdXAhCoYBjSGU3B3"; 

void setup() 
{
  WiFi.begin(wifiSSID, wifiPassword);
  Serial.begin(9600); 
  pinMode(ledPinNumber, OUTPUT);

  Wire.begin();
  lightSensor.begin();

  Serial.println(F("Light sensor is now set up"));

  connectToWiFi();
}

void loop() {
  float currentLightLevel = lightSensor.readLightLevel();
  Serial.print("Current Light Level: ");
  Serial.println(currentLightLevel);
  
  if (currentLightLevel >= 360) {
    sendNotification("Daylight");
  } else if (currentLightLevel < 80) {
    sendNotification("Nighttime");
  }
  delay(1000); // Pause before checking the light level again
}

void connectToWiFi() {
  Serial.println("Attempting to connect to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(wifiSSID, wifiPassword);
    delay(10000); // Retry connection every 10 seconds
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi successfully");
}

void sendNotification(String notificationType) 
{
  if (WiFi.status() != WL_CONNECTED) 
  {
    connectToWiFi();
  }
  
  if (client.connect(iftttHostName, 433)) {
    client.println("GET " + iftttEndpoint + queryParams + " HTTP/1.1");
    client.println("Host: " + String(iftttHostName));
    client.println("Connection: close");
    client.println();
    delay(500);
    client.stop();
    Serial.println("Notification sent");
  } else {
    Serial.println("Connection to server failed");
  }
}