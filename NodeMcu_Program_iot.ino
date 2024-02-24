#include <ESP8266WiFi.h>
//Wifi Cedentials
const char* ssid = "Oppo A5 2020"; // your SSID
const char* password = "0405077071"; // your wIFi password
//Thingspeak
String apiKey = " VCCXNWEDC7IW5SUS "; // API key
const char* server = "api.thingspeak.com";
WiFiClient client;
float Level;
void setup()
{
Serial.begin(115200);
delay(10);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
}
void loop()
{
float reading = analogRead(A0);
Level = ((reading/1023)*100);
if (isnan(Level))
{
Serial.println("Failed to read from MQ-4 sensor!");
return;
}
if (client.connect(server, 80)) // "184.106.153.149" or api.thingspeak.com
{
 String postStr = apiKey;
 postStr +="&field1=";
 postStr += String(Level);
 postStr += "\r\n\r\n";
 client.print("POST /update HTTP/1.1\n");
 client.print("Host: api.thingspeak.com\n");
 client.print("Connection: close\n");
 client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
 client.print("Content-Type: application/x-www-form-urlencoded\n");
 client.print("Content-Length: ");
 client.print(postStr.length());
 client.print("\n\n");
 client.print(postStr);
Serial.print("ETHYLENE: ");
Serial.println(Level);
Serial.println("Data Send to Thingspeak");
}
delay(500);
client.stop();
Serial.println("Waiting...");
// thingspeak needs minimum 15 sec delay between updates.
delay(1500);
}