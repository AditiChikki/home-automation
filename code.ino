
// Blynk Template Configuration
#define BLYNK_TEMPLATE_ID "TMPL34TQXUmqO"
#define BLYNK_TEMPLATE_NAME "HomeAutomation"
#define BLYNK_PRINT Serial

// Include libraries
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Pin definitions
#define DHTPIN D4         // DHT11 data pin
#define DHTTYPE DHT11
#define LDR_PIN A0        // LDR analog pin
#define TRIG_PIN D5       // Ultrasonic trigger
#define ECHO_PIN D6       // Ultrasonic echo
#define RELAY_PIN1 D1     // Relay for Light
#define RELAY_PIN2 D2     // Relay for Fan

// WiFi credentials and Blynk auth token
char ssid[] = "YOUR_WIFI_SSID"; // Replace with your WiFi name
char pass[] = "YOUR_WIFI_PASSWORD"; // Replace with your WiFi password
char auth[] = "sYFtbs1siF4g0sMpFCJXESijPbvppTr5"; // From screenshot

// Global variables
DHT dht(DHTPIN, DHTTYPE);
WiFiServer server(80);

bool isManualMode = false;

// Function to setup serial
void serialSetup() {
  Serial.begin(115200);
  Serial.println();
}

// Function to initialize DHT sensor
void DHTsetup() {
  Serial.println("DHTxx test!");
  dht.begin();
}

// Function to setup LDR pin
void LDRsetup() {
  pinMode(LDR_PIN, INPUT);
}

// Function to setup Ultrasonic sensor pins
void ultraSonicSensorSetup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

// Function to setup relay pins
void relaySetup() {
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  digitalWrite(RELAY_PIN1, HIGH); // OFF initially
  digitalWrite(RELAY_PIN2, HIGH); // OFF initially
}

// Function to connect to WiFi
void wifiSetup() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  server.begin();
  Blynk.begin(auth, ssid, pass);
}

// Get temperature
float getTemp() {
  delay(2000);
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }
  Serial.print("Temperature: ");
  Serial.println(temp);
  return temp;
}

// Detect darkness using LDR
bool isitDark() {
  int lightVal = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(lightVal);
  return (lightVal < 500); // Adjust threshold as needed
}

// Get distance from ultrasonic
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

// Set relay state
void setRelay(uint8_t relay_pin, uint8_t val) {
  digitalWrite(relay_pin, val);
  if (relay_pin == RELAY_PIN1) {
    Serial.print("Light relay: ");
    Serial.println(val);
  } else if (relay_pin == RELAY_PIN2) {
    Serial.print("Fan relay: ");
    Serial.println(val);
  }
}

// Switch between manual and auto mode
void switchMode(bool manual) {
  isManualMode = manual;
}

// Handle automatic mode logic
void handleAutoMode() {
  float distance = getDistance();
  float temperature = getTemp();
  bool dark = isitDark();

  if (distance <= 30) {
    if (temperature >= 60) {
      setRelay(RELAY_PIN2, LOW);
    } else {
      setRelay(RELAY_PIN2, HIGH);
    }
    if (dark) {
      setRelay(RELAY_PIN1, LOW);
    } else {
      setRelay(RELAY_PIN1, HIGH);
    }
  } else {
    setRelay(RELAY_PIN1, HIGH);
    setRelay(RELAY_PIN2, HIGH);
  }
}

// Handle manual mode via Blynk
BLYNK_WRITE(V0) {
  int lightControl = param.asInt();
  if (isManualMode) {
    setRelay(RELAY_PIN1, lightControl ? LOW : HIGH);
  }
}

BLYNK_WRITE(V1) {
  int fanControl = param.asInt();
  if (isManualMode) {
    setRelay(RELAY_PIN2, fanControl ? LOW : HIGH);
  }
}

BLYNK_WRITE(V2) {
  int mode = param.asInt();
  switchMode(mode);
}

// Arduino setup
void setup() {
  serialSetup();
  DHTsetup();
  LDRsetup();
  ultraSonicSensorSetup();
  relaySetup();
  wifiSetup();
}

// Arduino main loop
void loop() {
  Blynk.run();
  if (!isManualMode) {
    handleAutoMode();
  }
  delay(1000);
}
