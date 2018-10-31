#ifndef WIFIUDP_H
#define WIFIUDP_H

#include <WiFiUdp.h>

WiFiUDP Udp;

//设置监听端口
void UDPListen(unsigned int localUdpPort){
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

//UDP协议监听收到的数据
void UDPget(){
  char incomingPacket[255];  // buffer for incoming packets
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
  }
}

//UDP发送数据
void UDPsent(IPAddress RemoteIP,unsigned int RemotePort,char* PacketData){
  // send back a reply, to the IP address and port we got the packet from
  Udp.beginPacket(RemoteIP, RemotePort,);
  Udp.write(PacketData);
  Udp.endPacket();
}


#endif
