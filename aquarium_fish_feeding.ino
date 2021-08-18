//----------- Feeding Fish Aquarium -------------------//
// Menggunakan aplikasi android untuk mengecek keberhasilan
// Dengan MQTT Dash, setting nama project terserah
// address yang digunakan sesuai dengan server dari MQTTCloud
// Sesuaikan PORT yang digunakan dengan MQTTCloud
// Username dan Password sesuaikan juga diaplikasi androidnya

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

// ganti
const char* ssid = "ssid";
const char* password =  "password";
const char* mqttServer = "server address";
const int mqttPort = 00000;
const char* mqttUser = "username";
const char* mqttPassword = "password";

WiFiClient espClient;
PubSubClient client(espClient);
Servo servo;

void setup() {
  delay(1000);
  servo.attach(2); // D1
  Serial.begin(115200);
  WifiSetup();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);
  //  MqttSetup();
}

void MQTTcallback(char* topic, byte* payload, unsigned int length) {

  Serial.println("=======================================");
  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");

  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];  //konversi byte ke String
  }
  Serial.print(message);
//  if (message == 1) { // pake button
//    servo.write(90);
//    delay(100);
//    servo.write(0);
//    delay(100);
//  }
  if (message == "on") {
    servo.write(45);
    delay(300);
    servo.write(0);
    delay(300);
  }
  Serial.println();
  Serial.println("=======================================");
}



void WifiSetup() {
  // Kegunaan dari Wifi mode WIFI_STA adalah
  // Agar dapat juga terkoneksi dengan hidden wifi
  delay(200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Request Time Out");
  }
  Serial.println("Connecting to WiFi : ");
  Serial.print(WiFi.SSID());
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void MqttSetup() {
  //  client.setServer(mqttServer, mqttPort);
  //  client.setCallback(MQTTcallback);
  while (!client.connected()) {
    Serial.println("Connecting to MqttCloud...");
    if (client.connect("ESP8266", mqttUser, mqttPassword )) {
      Serial.println("connected");
      Serial.println("");
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      Serial.println(" try again in 3 seconds");
      delay(3000);
    }
  }
  // untuk topic esp/test itu harus sesuai dengan yang ada di cloud, karena
  // jika tidak maka esp tidak dapat menerima pesan dari cloudmqtt/broker
  // lalu pada publish terdapat hello from ESP8266 itu berfungsi untuk mengecek apakah
  // program awal dapat berjalan dengan sesuai
  // pada subscribe juga topic harus sesuai dengan cloud/broker maupun settinggan dari codenya
  // -----------------------------------------------------------------------------------------
  client.publish("esp82/test", "Device ESP8266 !");
  client.subscribe("esp82/test");
}

void loop() {
  if (!client.connected()) {
    MqttSetup();
  }
  client.loop();
}
