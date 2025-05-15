# 💧 Monitoramento Inteligente de Nível de Água com ESP32 + MQTT

Este projeto tem como objetivo monitorar, em tempo real, o nível de água de reservatórios residenciais utilizando a plataforma ESP32 com sensor ultrassônico HC-SR04, acionando automaticamente uma bomba d'água via relé quando o nível estiver baixo. A comunicação é feita via protocolo MQTT.

---

## 🔧 Componentes Utilizados

- ESP32 (com Wi-Fi integrado)
- Sensor Ultrassônico HC-SR04
- Relé 5V
- Bomba d'água (ou LED simulando a bomba)
- Fonte de alimentação 5V/2A
- Broker MQTT (Mosquitto)
- Jumpers, resistores e protoboard

---

## 📡 Funcionamento

1. O sensor HC-SR04 mede a distância até a superfície da água.
2. O ESP32 interpreta essa distância e calcula o nível do reservatório.
3. Os dados são enviados via MQTT para o broker.
4. Se o nível estiver abaixo de um limite crítico, o relé é acionado para ligar a bomba.
5. Um aplicativo web (ou dashboard MQTT) pode ser utilizado para visualizar os dados em tempo real.

---

## 🌐 MQTT

- Broker usado: [Mosquitto](https://mosquitto.org/)
- Tópico de publicação: `reservatorio/nivel`
- Mensagens publicadas a cada 5 segundos com o nível do reservatório em centímetros.

---

## 🛠️ Instalação e Uso

### 1. Código-fonte

Clone o repositório e abra o arquivo `main.ino` no Arduino IDE.

```bash
git clone https://github.com/seuusuario/iot-monitoramento-nivel-agua.git
