
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "enter_your_wifi_ssid";
const char* password = "enter_your_wifi_network";

char* topic = "enter_your_mqtt_topic";
char* server = "mqtt.koor.io";
 
char message_buff[100];
const int LED_PIN = 5;
WiFiClient wifiClient;
 
String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}

void callback(char* topic, byte* payload, unsigned int length) { 
  int i = 0;

  Serial.println("Message arrived:  topic: " + String(topic));
  Serial.println("Length: " + String(length,DEC));
  
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
  String msgString = String(message_buff);
  
  Serial.println("Payload: " + msgString);
  if (msgString == "1"){    // if there is a "1" published to any topic (#) on the broker then:
    digitalWrite(LED_PIN, 1);     // set pin to the opposite state 
    Serial.println("Switching LED"); 
  }
  if (msgString == "0"){    // if there is a "1" published to any topic (#) on the broker then:
    digitalWrite(LED_PIN, 0);     // set pin to the opposite state 
    Serial.println("Switching LED"); 
  }
}

PubSubClient client(server, 1883, callback, wifiClient);

void setup() {
  Serial.begin(115200);
  delay(10);
    
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 0);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  //  connection to broker script.
  if (client.connect("arduinoClient")) {
    client.publish(topic,"hello world");
    client.subscribe(topic);
  }
}
 
void loop() {
  client.loop();
}



