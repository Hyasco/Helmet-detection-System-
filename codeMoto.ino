#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "WENDYAM-2.4G";
const char* password = "Tp_l1nk@";

IPAddress local_ip(192, 168, 1, 100);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

#define RELAY_PIN 4 // D2
#define BUZZER_PIN 12  // D12

void handleDetection() {
  Serial.println("Signal reçu : casque détecté !");
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(RELAY_PIN, HIGH);
  delay(600);
  digitalWrite(BUZZER_PIN, LOW);
  server.send(200, "text/plain", "Signal reçu");
}

void setup() {
  Serial.begin(115200);
  WiFi.config(local_ip, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnecté !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  server.on("/detect", handleDetection);
  server.begin();
  Serial.println("Serveur HTTP démarré !");
}

void loop() {
  server.handleClient();
}
