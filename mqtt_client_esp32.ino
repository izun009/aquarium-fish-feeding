#include "EspMQTTClient.h"

EspMQTTClient client(
  "Bubu    ",
  "SayurBayem",
  "broker.mqtt-dashboard.com",  
  "TestClient",     
  1883              
);

void setup()
{
  Serial.begin(115200);
  client.enableDebuggingMessages(); 
  client.enableHTTPWebUpdater(); 
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline"); 
}

void onConnectionEstablished()
{
  client.subscribe("mytopic/test", [](const String & payload) {
    Serial.println(payload);
  });

  client.publish("mytopic/test", "This is a message"); 

  client.executeDelayed(5 * 1000, []() {
    client.publish("mytopic/test", "This is a message sent 5 seconds later");
  });
}

void loop()
{
  client.loop();
}
