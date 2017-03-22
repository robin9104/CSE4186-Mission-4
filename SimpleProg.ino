const char *host = "api.thingspeak.com";
String url = "/update?api_key=YIT2PGAX14KHHQGA";
const int httpPort = 80;
int interval = 20000;

float data= 0;
int t = 0;

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char *ssid = "olleh_WiFi_88DF";
const char *password = "0000007063";

String working() {
  t++;
  if(t % 10 == 0)
  {
    data = 1 - data;
  }

  return (String("field1=") + String(data));
}

void delivering(String payload)
{
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpPort))
  {
    Serial.print("connection failed: ");
    Serial.println(payload);
    return;
  }

  String getheader = "GET " + String(url) + "&" + String(payload) + " HTTP/1.1";
  client.println(getheader);
  client.println("User-Agent: ESP8266 Seolgi Kim");
  client.println("Host: " + String(host));
  client.println("Connection: close");
  client.println();

  Serial.println(getheader);
  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
  Serial.println("Done cycle.");
}

void connect_ap()
{
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("\n Got WiFi, IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  connect_ap();
  
  Serial.println("ESPArduionoThingSpeak.cpp - 2017/3/18");
}

unsigned long mark = 0;
void loop() {
  if (millis() > mark)
  {
    mark = millis() + interval;
    String payload = working();
    delivering(payload);
  }
}
