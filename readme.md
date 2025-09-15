# IoT Security Project: Detection Movement Alarm

[cite_start]Este proyecto implementa un sistema de alarma de seguridad simple utilizando un Arduino Uno WiFi Rev2, un sensor de movimiento PIR y un bróker de mensajes RabbitMQ[cite: 1, 2].

Cuando el sensor PIR detecta movimiento, el sistema activa una alarma local (un LED y un zumbador) y envía una notificación a través del protocolo MQTT a un tema específico en RabbitMQ. Esto permite que otros dispositivos o aplicaciones se suscriban y reaccionen a la alerta de intrusión.



---

## 🏛️ Arquitectura del Sistema

[cite_start]El flujo de datos del proyecto es el siguiente[cite: 15]:
1.  El **Sensor PIR** detecta movimiento y envía una señal `HIGH` al Arduino.
2.  El **Arduino Uno WiFi Rev2** recibe la señal, activa el LED y el zumbador, y se conecta a la red WiFi local.
3.  El Arduino publica un mensaje en el topic `seguridad/intrusos` en el bróker **RabbitMQ** usando el protocolo MQTT.
4.  Cualquier cliente suscrito a ese topic, como **MQTT Explorer**, recibirá el mensaje en tiempo real.

---

## ⚙️ Componentes Necesarios

### [cite_start]Hardware [cite: 6]
* [cite_start]**Arduino Uno WiFi Rev2** [cite: 8]
* [cite_start]**Sensor de movimiento PIR** [cite: 10]
* [cite_start]**LED rojo** [cite: 9]
* [cite_start]**Zumbador (Buzzer)** [cite: 14]
* [cite_start]Cables de conexión (Arduino Wires) [cite: 12]
* [cite_start]Cable USB y adaptador para alimentar el Arduino [cite: 13]

### Software y Protocolos
* Arduino IDE
* RabbitMQ Broker
* MQTT (protocolo de mensajería)
* Un cliente MQTT como MQTT Explorer para pruebas.

---

## 🛠️ Guía de Instalación y Configuración

### Paso 1: Montaje del Hardware

Conecta los componentes al Arduino de la siguiente manera:
* [cite_start]**Sensor PIR**: El pin de señal (OUT) al **pin digital 2** del Arduino[cite: 40].
* [cite_start]**LED**: El ánodo (pata larga) al **pin digital 13** del Arduino[cite: 54].
* [cite_start]**Zumbador (Buzzer)**: El pin positivo al **pin digital 8** del Arduino[cite: 58].
* Conecta los pines de alimentación (VCC) y tierra (GND) de los componentes a los pines 5V y GND del Arduino, respectivamente.

### Paso 2: Configuración del Bróker RabbitMQ

1.  **Instala RabbitMQ** en tu servidor o máquina local.
2.  **Habilita el plugin de MQTT**. Puedes hacerlo ejecutando el siguiente comando en la terminal o PowerShell:
    ```sh
    rabbitmq-plugins enable rabbitmq_mqtt
    ```
3.  **Configura el puerto MQTT**. Crea o edita el archivo `rabbitmq.config` en el directorio de configuración de RabbitMQ y asegúrate de que contenga la siguiente línea para habilitar el listener de MQTT en el puerto `1883`. Puedes usar el archivo proporcionado en la carpeta `rabbitmq_config`.

### Paso 3: Cargar el Código en Arduino

1.  **Abre el IDE de Arduino** y carga el archivo `iot_security_alarm.ino`.
2.  [cite_start]**Instala las librerías necesarias**: Desde el gestor de librerías, busca e instala `WiFiNINA` [cite: 20] (para la conectividad WiFi del Arduino Uno WiFi Rev2) [cite_start]y `PubSubClient` [cite: 23] (para la comunicación MQTT).
3.  **Configura tus credenciales**: Abre el archivo `config.h` y modifica los siguientes valores con tu información:
    * [cite_start]`WIFI_SSID`: El nombre de tu red WiFi[cite: 148].
    * [cite_start]`WIFI_PASSWORD`: La contraseña de tu red WiFi[cite: 148].
    * [cite_start]`MQTT_SERVER`: La dirección IP de tu servidor RabbitMQ[cite: 149].
    * [cite_start]`MQTT_USER` y `MQTT_PASS`: El usuario y contraseña para la conexión MQTT[cite: 151, 152].

4.  **Sube el código** a tu placa Arduino.

### Paso 4: Probar el Sistema

1.  [cite_start]Abre el **Monitor Serie** en el IDE de Arduino (a 9600 baudios) para ver los mensajes de estado como "Conectado a WiFi" o "¡Intrusos detectados!"[cite: 143, 144].
2.  [cite_start]Utiliza un cliente MQTT como **MQTT Explorer** para conectarte a tu bróker RabbitMQ en la IP y puerto configurados[cite: 220, 228].
3.  [cite_start]Suscríbete al topic `seguridad/intrusos`[cite: 247].
4.  Mueve la mano frente al sensor PIR. [cite_start]Deberías ver cómo el LED y el zumbador se activan, y recibirás el mensaje `"¡Intrusos detectados!"` en MQTT Explorer[cite: 106, 236]. [cite_start]Cuando no haya movimiento, recibirás el mensaje `"Modo vigilante"`[cite: 122, 125].