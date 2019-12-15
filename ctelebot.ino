// nodmcu v3 requirements
#include "CTBot.h"
CTBot myBot;

String ssid  = "   ";
String pass  = "SayurBayem";
String token = "997080610:xxxxx";

void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection())
    Serial.println("Connected");
  else
    Serial.println("Failed");
}

void loop() {
  telebot();
}

void telebot(){
  TBMessage msg;
  if (myBot.getNewMessage(msg)) {
    myBot.sendMessage(msg.sender.id, msg.text);
  }
  delay(300);
}
