#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Configurações de Wi-Fi
const char* ssid = "MINHA_REDE";
const char* password = "MINHA_SENHA";

// URL da sua API backend
const char* serverUrl = "http://0.0.0.0:3000/api/som";

// Pino analógico
const int pinoSom = A0;

// Limiar que você identificou
const int LIMIAR_SILENCIO = 541;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("IP do ESP8266:");
  Serial.println(WiFi.localIP());
  Serial.println("\nWi-Fi conectado!");
}

void loop() {
  int leitura = analogRead(pinoSom);
  Serial.print("Leitura: ");
  Serial.println(leitura);

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"valor\":" + String(leitura) + "}";
    int statusCode = http.POST(json);

    Serial.print("POST enviado, status: ");
    Serial.println(statusCode);

    http.end();
  } else {
    Serial.println("Wi-Fi desconectado!");
  }

  delay(500);
}
