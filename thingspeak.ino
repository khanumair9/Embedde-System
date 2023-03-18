#include <ESP8266WiFi.h>
#include <Servo.h>
#include <SimpleDHT.h>
#include <DHTesp.h>


int pinDHT11 = 0;//d3
SimpleDHT11 dht11; // Creats a DHT object
String apiKey="HFN9KOOHBBXM2XMI";
const char* ssid = "CIITATK";
const char* password ="haroon@0310";
const char* server= "api.thingspeak.com";

WiFiClient client;
void setup()
{
  Serial.begin(115200);
  delay(10);
 
  Serial.print("Connecting to the Newtork");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
}

void loop()
{



   // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }
  if (client.connect(server,80))
  {
   String sendData=apiKey+"&field1="+String(temperature)+"&field2="+String(humidity)+"\r\n\r\n";
  client.print("post /update HTTP/1.1\n");
    client.print("host: api.thingspeak.com\n");
     client.print("connection: close\n");
      client.print("x-thingspeakapikey: "+apiKey+"\n");
       client.print("content type: application/x-www-form-urlencoded\n");
        client.print("content-Length");
        client.print(sendData.length());
        client.print("\n\n");
        client.print(sendData);

   //Serial.print("Sample OK: ");
  Serial.print(temperature); 
  Serial.print(" *C, "); 
  Serial.print(humidity); 
  Serial.println(" %");
  Serial.print("connecting");
  }
  client.stop();
  Serial.println("sending");
  
  
  // DHT11 sampling rate is 1HZ.
  delay(1000);

}
