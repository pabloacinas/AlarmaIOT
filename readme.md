# IoT Security Project: Detection Movement Alarm

Este proyecto implementa un sistema de alarma de seguridad simple utilizando un Arduino Uno WiFi Rev2, un sensor de movimiento PIR y un bróker de mensajes RabbitMQ.

Cuando el sensor PIR detecta movimiento, el sistema activa una alarma local (un LED y un zumbador) y envía una notificación a través del protocolo MQTT a un tema específico en RabbitMQ. Esto permite que otros dispositivos o aplicaciones se suscriban y reaccionen a la alerta de intrusión.

[Image of a simple Arduino security project]

---

## 🏛️ Arquitectura del Sistema

El flujo de datos del proyecto es el siguiente:
1.  El **Sensor PIR** detecta movimiento y envía una señal al Arduino.
2.  El **Arduino Uno WiFi Rev2** recibe la señal, activa el LED y el zumbador, y se conecta a la red WiFi local.
3.  El Arduino publica un mensaje en el topic `seguridad/intrusos` en el bróker **RabbitMQ** usando el protocolo MQTT.
4.  Cualquier cliente suscrito a ese topic, como **MQTT Explorer**, recibirá el mensaje en tiempo real.

---

## ⚙️ Componentes Necesarios

### Hardware
* **Arduino Uno WiFi Rev2**
* **Sensor de movimiento PIR**
* **LED rojo**
* **Zumbador (Buzzer)**
* Cables de conexión (Arduino Wires)

### Software y Protocolos
* Arduino IDE
* RabbitMQ Broker
* MQTT (protocolo de mensajería)
* Un cliente MQTT como MQTT Explorer para pruebas.

---

## 🛠️ Guía de Instalación y Configuración

### Paso 1: Montaje del Hardware

Conecta los componentes al Arduino de la siguiente manera:
* **Sensor PIR**: El pin de señal (OUT) al **pin digital 2** del Arduino.
* **LED**: El ánodo (pata larga) al **pin digital 13** del Arduino.
* **Zumbador (Buzzer)**: El pin positivo al **pin digital 8** del Arduino.
* Conecta los pines de alimentación (VCC) y tierra (GND) de los componentes a los pines 5V y GND del Arduino.

### Paso 2: Configuración del Bróker RabbitMQ

1.  **Instala RabbitMQ** en tu servidor o máquina local.
2.  **Habilita el plugin de MQTT**. Ejecuta el siguiente comando en la terminal:
    ```sh
    rabbitmq-plugins enable rabbitmq_mqtt
    ```
3.  **Configura el puerto MQTT**. Crea o edita el archivo `rabbitmq.config` en el directorio de configuración de RabbitMQ y asegúrate de que contenga la línea del archivo proporcionado en la carpeta `rabbitmq_config`.

### Paso 3: Cargar el Código en Arduino

1.  **Abre el IDE de Arduino** y carga el archivo `iot_security_alarm.ino`.
2.  **Instala las librerías necesarias**: Desde el gestor de librerías, busca e instala `WiFiNINA` y `PubSubClient`.
3.  **Configura tus credenciales**: Abre el archivo `config.h` y modifica los valores con la información de tu red WiFi y servidor MQTT.
4.  **Sube el código** a tu placa Arduino.

### Paso 4: Probar el Sistema

1.  Abre el **Monitor Serie** en el IDE de Arduino (
