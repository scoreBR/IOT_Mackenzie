#include <WiFi.h>
#include <PubSubClient.h>

// ======= Configurações Wi-Fi =======
const char* ssid = "Splendor14";
const char* password = "leolucas1515";

// ======= Configurações MQTT =======
const char* mqtt_server = "192.168.15.10";
const int mqtt_port = 1883;
const char* mqtt_topic = "reservatorio/nivel";

WiFiClient espClient;
PubSubClient client(espClient);

// ======= Pinos do sensor ultrassônico =======
#define TRIG_PIN 5
#define ECHO_PIN 18

// ======= Pino do relé =======
#define RELAY_PIN 19

// ======= Limite de nível crítico (em cm) =======
const int nivel_critico = 20;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se ao Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("conectado.");
    } else {
      Serial.print("Falhou. Estado: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

long medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  long distancia = duracao * 0.034 / 2;  // cm
  return distancia;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long distancia = medirDistancia();
  Serial.print("Distância medida: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Publicar no MQTT
  char mensagem[50];
  sprintf(mensagem, "Distancia: %ld cm", distancia);
  client.publish(mqtt_topic, mensagem);

  // Controle do relé
  if (distancia > nivel_critico) {
    digitalWrite(RELAY_PIN, HIGH); // liga bomba
    Serial.println("Nível baixo - bomba acionada.");
  } else {
    digitalWrite(RELAY_PIN, LOW); // desliga bomba
    Serial.println("Nível OK - bomba desligada.");
  }

  delay(5000);  // intervalo de 5 segundos
}
