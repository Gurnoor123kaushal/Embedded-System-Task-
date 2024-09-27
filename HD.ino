#include <Arduino.h>
#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

// Firebase settings
const char* FIREBASE_URL = "trafficlight-1b841-default-rtdb.firebaseio.com";
const char* FIREBASE_SECRET = "NZwCPCBdtGJMRdA4MTNkLTjrYmaYIeoK0sgEU8RT";

// WiFi credentials
const char* WIFI_NAME = "Gurnoor ";
const char* WIFI_PASS = "GunroorIphone";

// Firebase data location
const String FIREBASE_DATA_PATH = "/TrafficSignal/State";

// LED pin assignments
const int RED_LED_PIN = 5;
const int BLUE_LED_PIN = 6;
const int GREEN_LED_PIN = 7;

FirebaseData fbData;

void setupNetworkAndDatabase();
void updateDatabaseState(const String& state);
String readDatabaseState();
void setLightStates(bool red, bool yellow, bool green);

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  setupNetworkAndDatabase();
  updateDatabaseState("OFF");
}

void loop() {
  String currentState = readDatabaseState();
  
  if (currentState == "red") {
    setLightStates(true, false, false);
    Serial.println("Red light activated");
  } else if (currentState == "yellow") {
    setLightStates(false, true, false);
    Serial.println("Yellow light activated");
  } else if (currentState == "green") {
    setLightStates(false, false, true);
    Serial.println("Green light activated");
  } else if (currentState == "OFF") {
    setLightStates(false, false, false);
    Serial.println("All lights deactivated");
  } else {
    Serial.println("Unrecognized state from Firebase: " + currentState);
  }
  
  delay(500);
}

void setupNetworkAndDatabase() {
  Serial.print("Establishing WiFi connection");
  WiFi.begin(WIFI_NAME, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected successfully");
  Serial.print("Device IP: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_URL, FIREBASE_SECRET, WIFI_NAME, WIFI_PASS);
  Firebase.reconnectWiFi(true);
}

void updateDatabaseState(const String& state) {
  if (Firebase.setString(fbData, FIREBASE_DATA_PATH, state)) {
    Serial.println("Firebase state updated to: " + state);
  } else {
    Serial.println("Failed to update Firebase state. Reason: " + fbData.errorReason());
  }
}

String readDatabaseState() {
  if (Firebase.getString(fbData, FIREBASE_DATA_PATH)) {
    return fbData.stringData();
  } else {
    Serial.println("Failed to fetch Firebase state. Reason: " + fbData.errorReason());
    return "ERROR";
  }
}

void setLightStates(bool red, bool yellow, bool green) {
  digitalWrite(LED_RED, red ? HIGH : LOW);
  digitalWrite(LED_YELLOW, yellow ? HIGH : LOW);
  digitalWrite(LED_GREEN, green ? HIGH : LOW);
}
