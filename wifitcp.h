#ifndef WIFITCP_H
#define WIFITCP_H

WiFiServer tcpserver();  

String replydata(String line){
  return "start-"+comedata+"-end\n";
}

void TCPListen(unsigned int localTcpPort){
  WiFiServer tcpserver(localTCPPort);
  tcpserver.begin();
  Serial.printf("Tcp server started : %s \n", WiFi.localIP().toString().c_str());
}

void TCPget(){
  WiFiClient tcpclient = tcpserver.available();
  // wait for a client to connect
  if (tcpclient)
  {
    Serial.println("\n[Client connected]");
    while (tcpclient.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (tcpclient.available())
      {
        String line = tcpclient.readStringUntil('\r');
        Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          client.println(replydata(line));
          break;
        }
      }
    }
    delay(1); // give the web browser time to receive the data
    // close the connection:
    tcpclient.stop();
    Serial.println("[Client disonnected]");
  }
}

void TCPsent(char* host,unsigned int remoteTcpPort,String data){
  WiFiClient tcpclient;
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, remoteTcpPort))
  {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
    tcpclient.print(data+"\r\n");
    Serial.println("[Response:]");
    while (tcpclient.connected())
    {
      if (tcpclient.available())
      {
        String line = tcpclient.readStringUntil('\n');
        Serial.println(line);
      }
    }
    tcpclient.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  //delay(5000);
}

#endif
