This sample is base on [Sming MQTT Sample](https://github.com/SmingHub/Sming/tree/develop/samples/MqttClient_Hello) and [Koor.IO MQTT Service](https://koor.io)

As you know, Sming is a good Framework to work with ESP8266. In this example, we will use ESP8266 to push data to Koor.IO by MQTT Protocol.

### Prerequisites
To start this example, you need to install Sming Framework, and have an account on https://koor.io
- An Account on Koor.IO
- Create a Project, a Custom Field on Koor.IO
- Install Sming Framework on your machine

### Installation
You need to clone this source code to your machine. After that, you create your own `config.h` file.
```
cp include/config.h.sample include/config.h
```
Next, you custom `config.h` to match your Wifi network and your Project on Koor.IO
```
// WIFI config
#define WIFI_SSID "PleaseEnterWifiSSID"
#define WIFI_PWD "PleaseEnterWifiPassword"

// MQTT config
#define MQTT_HOST "PleaseEnterMQTTHost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "PleaseEnterMQTTTopic"
```

### Build
After the installation, you just need one command to build and charge your source code to ESP8266
```
make flash
```

### Test
You just need to open Web Browser and access Koor.IO, go to the detail page of the custom field to see the chart of the data.
