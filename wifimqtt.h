#ifndef WIFIMQTT_H
#define WIFIMQTT_H

#include <PubSubClient.h>

WiFiClient espClient;                                                         // 定义wifiClient实例
PubSubClient mqttclient(espClient);                                         // 定义PubSubClient的实例

void initMQTT(char* mqtt_server,unsigned int port){
  mqttclient.setServer(mqtt_server, port);                              //设定MQTT服务器与使用的端口，1883是默认的MQTT端口
  mqttclient.setCallback(callback);                                          //设定回调方式，当ESP8266收到订阅消息时会调用此方法
}

void MQTTsentAndLoop(char* TOPIC){
    if (!mqttclient.connected()) {
        reconnect();
    }
    mqttclient.loop();
    if(Serial.available()>0){
        mqttclient.publish(TOPIC, Serial.readStringUntil('?').c_str());
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
  char maxRange[32][32];
  int maxRanges = split(maxRange,string2char(topic),"/");
  Serial.print(maxRange[1]);   // 打印主题信息
  Serial.print("-");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]); // 打印主题内容
  }
  Serial.println();
}

void reconnect(char* TOPIC,char* client_id,char* username,char* password) {
  while (!mqttclient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttclient.connect(strcat(client_id,random(99999999)),username,password)) {
      Serial.println("connected");
      // 连接成功时订阅主题
      mqttclient.subscribe(TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

#endif
