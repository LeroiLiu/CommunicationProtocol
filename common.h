#ifndef COMMON_H
#define COMMON_H

//初始化串口
void initSerialBaudRate(unsigned int BaudRate){
  Serial.begin(BaudRate);
  int br = Serial.baudRate();
  Serial.printf("Serial is %d bps", br);
  Serial.println();
}

//初始化AP并配置
void initAPInfo(char* ssid,char* password){
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP(ssid, password);
  if(result == true)
  {
    Serial.print("AP IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }
}

//初始化Station并连接
void initStationInfo(char* ssid,char* password,IPAddress staticIP, IPAddress gateway, IPAddress subnet){
  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void initWifiScan(){
  WiFi.mode(WIFI_STA);//WIFI_AP_STA,WIFI_AP,WIFI_STA,WIFI_OFF
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks(false, true);
  String ssid;
  uint8_t encryptionType;
  int32_t RSSI;
  uint8_t* BSSID;
  int32_t channel;
  bool isHidden;
  for (int i = 0; i < n; i++)
  {
    WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
    Serial.printf("%d: %s, Ch:%d (%ddBm) %s %s\n", i + 1, ssid.c_str(), channel, RSSI, encryptionType == ENC_TYPE_NONE ? "open" : "", isHidden ? "hidden" : "");
  }
}



#endif
