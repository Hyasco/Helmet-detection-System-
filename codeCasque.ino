#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "WENDYAM-2.4G";
const char* password = "Tp_l1nk@";

IPAddress local_ip(192, 168, 1, 50);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


const char* host = "192.168.1.100";

#define FSR_PIN A0
int threshold = 60;

void setup() {
  Serial.begin(115200);
  WiFi.config(local_ip, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnecté au WiFi !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int pressure = analogRead(FSR_PIN);
  Serial.print("Valeur pression : ");
  Serial.println(pressure);

  if (pressure > threshold) {
    Serial.println("Casque détecté ! Envoi du signal...");
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
      http.begin(client, "http://" + String(host) + "/detect");
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.println("Signal envoyé avec succès !");
      } else {
        Serial.print("Erreur lors de l'envoi : ");
        Serial.println(httpCode);
      }
      http.end();
    }
  } else {
    Serial.println("Casque non détecté.");