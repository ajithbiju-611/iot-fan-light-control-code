#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial

char auth[] = "YourAuthToken";
char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";

#define relay1 5
#define relay2 18
#define relay3 19
#define relay4 21

#define led1 2
#define buzzer 15

int sensorPin = 34;
int sensorValue = 0;

BlynkTimer timer;

void checkWiFiStatus() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Disconnected");
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
  } else {
    Serial.println("WiFi Connected");
  }
}

void readSensor() {
  sensorValue = analogRead(sensorPin);

  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  Blynk.virtualWrite(V5, sensorValue);

  if (sensorValue > 2000) {
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
  }
}

BLYNK_WRITE(V0) {
  int state = param.asInt();

  if (state == 1) {
    digitalWrite(relay1, HIGH);
    Serial.println("Relay 1 ON");
  } else {
    digitalWrite(relay1, LOW);
    Serial.println("Relay 1 OFF");
  }
}

BLYNK_WRITE(V1) {
  int state = param.asInt();

  if (state == 1) {
    digitalWrite(relay2, HIGH);
    Serial.println("Relay 2 ON");
  } else {
    digitalWrite(relay2, LOW);
    Serial.println("Relay 2 OFF");
  }
}

BLYNK_WRITE(V2) {
  int state = param.asInt();

  if (state == 1) {
    digitalWrite(relay3, HIGH);
    Serial.println("Relay 3 ON");
  } else {
    digitalWrite(relay3, LOW);
    Serial.println("Relay 3 OFF");
  }
}

BLYNK_WRITE(V3) {
  int state = param.asInt();

  if (state == 1) {
    digitalWrite(relay4, HIGH);
    Serial.println("Relay 4 ON");
  } else {
    digitalWrite(relay4, LOW);
    Serial.println("Relay 4 OFF");
  }
}

void startupAnimation() {
  digitalWrite(led1, HIGH);
  delay(200);
  digitalWrite(led1, LOW);
  delay(200);
  digitalWrite(led1, HIGH);
  delay(200);
  digitalWrite(led1, LOW);
}

void setup() {

  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);

  startupAnimation();

  WiFi.begin(ssid, pass);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected Successfully");

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(2000L, readSensor);
  timer.setInterval(5000L, checkWiFiStatus);

  Serial.println("ESP32 IoT Home Automation Started");
}

void loop() {

  Blynk.run();

  timer.run();

}
