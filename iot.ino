#define BLYNK_TEMPLATE_ID "YourTemplateID" //enter ur template id
#define BLYNK_TEMPLATE_NAME "HomeAutomation"
#define BLYNK_AUTH_TOKEN "YourAuthToken"  //Enter ur authentification token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "YourWiFiName";  //Enter ur wifi name
char pass[] = "YourWiFiPassword";  //Enter ur wifi password

// Relay pins
int lightRelay = 5;
int fanRelay = 18;

void setup()
{
  Serial.begin(115200);

  // Set relay pins as output
  pinMode(lightRelay, OUTPUT);
  pinMode(fanRelay, OUTPUT);

  // Initially OFF
  digitalWrite(lightRelay, LOW);
  digitalWrite(fanRelay, LOW);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Connected to Blynk");
}

// Light Control
BLYNK_WRITE(V0)
{
  int value = param.asInt();

  if(value == 1)
  {
    digitalWrite(lightRelay, HIGH);
    Serial.println("Light ON");
  }
  else
  {
    digitalWrite(lightRelay, LOW);
    Serial.println("Light OFF");
  }
}

// Fan Control
BLYNK_WRITE(V1)
{
  int value = param.asInt();

  if(value == 1)
  {
    digitalWrite(fanRelay, HIGH);
    Serial.println("Fan ON");
  }
  else
  {
    digitalWrite(fanRelay, LOW);
    Serial.println("Fan OFF");
  }
}

void loop()
{
  Blynk.run();
}
