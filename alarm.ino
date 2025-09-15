#include <WiFiNINA.h>
#include <PubSubClient.h>
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

int pir_pin = 2;
int led_pin = 13;
int buzzer_pin = 8;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conectar al servidor MQTT...");
    if (client.connect("ArduinoClient", MQTT_USER, MQTT_PASS)) {
      Serial.println("Conectado al servidor MQTT");
    } else {
      Serial.print("Error de conexión, intento en 5 segundos..., Código: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(pir_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  Serial.println("Conectando a WiFi...");
  while (WiFi.begin(WIFI_SSID, WIFI_PASSWORD) != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("Conectado a WiFi");

  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (digitalRead(pir_pin) == HIGH) {
    digitalWrite(led_pin, HIGH);
    digitalWrite(buzzer_pin, HIGH);
    Serial.println("¡Intrusos detectados!");
    client.publish("seguridad/intrusos", "¡Intrusos detectados!");
  } else {
    digitalWrite(led_pin, LOW);
    digitalWrite(buzzer_pin, LOW);
    Serial.println("Modo vigilante");
    client.publish("seguridad/intrusos", "Modo vigilante");
  }

  delay(10000);
}