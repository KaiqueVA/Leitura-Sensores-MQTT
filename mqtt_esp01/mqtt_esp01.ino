#include <PubSubClient.h>
#include <SoftwareSerial.h>
//#include <WiFiClientSecure.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>


const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxxxxx";
const char* mqtt_server = "xxxxxxxxxxxxxx";
const int mqtt_port = xxxx;
const char* mqtt_client_id = "ESP-01_Teste";
const char* mqtt_topic_lux = "/lux/teste";
const char* mqtt_topic_Umidade = "/umidade/teste";
const char* mqtt_topic_Temperatura = "/temperatura/teste";
const char* mqtt_topic_voc = "/voc/teste";
const char* mqtt_topic_pressao = "/pressao/teste";


SoftwareSerial espSerial(4, 11);
WiFiClient espClient;
PubSubClient client(espClient);




void setup() {
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  espSerial.println("AT+RST");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqtt_server, mqtt_port);
//  client.setCallback(callback);
  
  while (!client.connected()) {
    if (client.connect(mqtt_client_id)) {
      Serial.println("Connected to MQTT server");
//      client.subscribe(mqtt_topic);
    } else {
      delay(1000);
      Serial.println("Connecting to MQTT server...");
    }
  }
    // Define o hostname (opcional)
  ArduinoOTA.setHostname("TESTE");

  // Define a senha (opcional)
  ArduinoOTA.setPassword("Smart*2021@");
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  //define o que será executado quando o ArduinoOTA iniciar
  ArduinoOTA.onStart([](){ startOTA(); }); //startOTA é uma função criada para simplificar o código 

  //define o que será executado quando o ArduinoOTA terminar
  ArduinoOTA.onEnd([](){ endOTA(); }); //endOTA é uma função criada para simplificar o código 

  //define o que será executado quando o ArduinoOTA estiver gravando
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) { progressOTA(progress,total); }); //progressOTA é uma função criada para simplificar o código 

  //define o que será executado quando o ArduinoOTA encontrar um erro
  ArduinoOTA.onError([](ota_error_t error){ errorOTA(error); });//errorOTA é uma função criada para simplificar o código 
  
  //inicializa ArduinoOTA
  ArduinoOTA.begin();

  //exibe pronto e o ip utilizado pelo ESP
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void startOTA()
{
   String type;
   
   //caso a atualização esteja sendo gravada na memória flash externa, então informa "flash"
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "flash";
    else  //caso a atualização seja feita pela memória interna (file system), então informa "filesystem"
      type = "filesystem"; // U_SPIFFS

    //exibe mensagem junto ao tipo de gravação
    Serial.println("Start updating " + type);
}

void endOTA()
{
  Serial.println("\nEnd");
}

void errorOTA(ota_error_t error)
{  
      Serial.printf("Error[%u]: ", error);
      
      if (error == OTA_AUTH_ERROR) 
        Serial.println("Auth Failed");
      else
      if (error == OTA_BEGIN_ERROR)
        Serial.println("Begin Failed");
      else 
      if (error == OTA_CONNECT_ERROR)
        Serial.println("Connect Failed");
      else
      if (error == OTA_RECEIVE_ERROR) 
        Serial.println("Receive Failed");
      else 
      if (error == OTA_END_ERROR)
        Serial.println("End Failed");
}

//exibe progresso em porcentagem
void progressOTA(unsigned int progress, unsigned int total){
   Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
}

void loop() {
  client.loop();
  char inicio = Serial.read();
  ArduinoOTA.handle();
    
  if(inicio == 'L')
  {
    String message = Serial.readStringUntil('\n');
    Serial.println(message);

    client.publish(mqtt_topic_lux, message.c_str());
  }
  if (inicio == 'U')
  {
    String message = Serial.readStringUntil('\n');
    Serial.println(message);

    client.publish(mqtt_topic_Umidade, message.c_str());
  }
  if (inicio == 'T')
  {
    String message = Serial.readStringUntil('\n');
    Serial.println(message);
    
    client.publish(mqtt_topic_Temperatura, message.c_str());

  }
  if (inicio == 'V')
  {
    String message = Serial.readStringUntil('\n');
    Serial.println(message);
    
    client.publish( mqtt_topic_voc, message.c_str());

  }
  if(inicio == 'M')
  {
    String message = Serial.readStringUntil('\n');
    Serial.println(message);
    
    client.publish(mqtt_topic_pressao, message.c_str());
  }
    
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(mqtt_client_id)) {
      Serial.println("Connected to MQTT server");
    } else {
      delay(1000);
      Serial.println("Connecting to MQTT server...");
    }
  }
  
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
