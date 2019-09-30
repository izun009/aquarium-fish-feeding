// Ket* test mqtt-client menggunakan MQTTBox 
// host : broker.mqtt-dashboard.com

#include "EspMQTTClient.h"

EspMQTTClient client(
  "Bubu    ", // SSID
  "SayurBayem", // Password
  "broker.mqtt-dashboard.com",  
  "TestClient", // nama client, bebas    
  1883        // portnya 1883 default, liat di broker.mqtt-dashboard.com       
);

void setup()
{
  Serial.begin(115200);
  client.enableDebuggingMessages(); 
  client.enableHTTPWebUpdater(); 
  client.enableLastWillMessage("TestClient", "Server Offline"); 
}

void onConnectionEstablished()
{
  client.subscribe("test", [](const String & payload) {
    Serial.println(payload);
  });

  client.publish("test", "Tes pesan pertama"); 

  client.executeDelayed(5 * 1000, []() {
    client.publish("test", "Pesan akan dikirim 5 detik");
  });
}

void loop()
{
  client.loop();
}
