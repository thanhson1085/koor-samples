This sample is base on [Sming HTTP Sample](https://github.com/SmingHub/Sming/tree/develop/samples/HttpClient_ThingSpeak) and [Koor.IO Mockup Restful API](https://koor.io)

As you know, Sming is a good Framework to work with ESP8266. In this example, we will use ESP8266 to push data to Koor.IO by MQTT Protocol.

### Hardware
- NodeMCU ESP8266 Dev Kit
- DHT11
- Led
- Resistor

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

// Http Config
#define HTTP_URL "http://xxxx.koor.io/api/test"
#define CHANEL_ONE "chanel1"
#define CHANEL_TWO "chanel2"

```

### Build
After the installation, you just need one command to build and charge your source code to ESP8266
```
make flash
```

### Test
You just need to open Web Browser and access Koor.IO, go to the detail page of the custom field to see the chart of the data.
