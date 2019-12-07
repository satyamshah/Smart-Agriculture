#include <ESP8266WiFi.h>
//--------------Your Data----------------//
String apiKey = "4E5ECTO029RANUCT"; // <<<<< YOUR API KEY
const char* ssid = "Serbius"; // <<<<<<<< Your Wi-Fi SSID 
const char* password = "..Password"; // <<<<<<<< Your Wi-Fi Pasword
//--------------------------------------//
const char* server = "api.thingspeak.com";
int data1, data2, data3, data4, data5, ok;
WiFiClient client;
unsigned char buff[10], i;
String buffer1, buffer2;
void setup()
{
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
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
  if (Serial.available() > 0)
  {
    delay(100);
    while (Serial.available() > 0)
    {
      buffer1 = Serial.readString();
      if (buffer1[0] == '*')
      {
        if (buffer1[9] == '#')
        {
          Serial.println(buffer1);
          data1 = ((buffer1[1] - 0x30) * 10 + (buffer1[2] - 0x30));
          data2 = ((buffer1[3] - 0x30) * 10 + (buffer1[4] - 0x30));
          data3 = ((buffer1[5] - 0x30) * 10 + (buffer1[6] - 0x30));
          data4 = ((buffer1[7] - 0x30) * 10 + (buffer1[8] - 0x30));
        }
      }
    }
  }
  if (client.connect(server, 80))
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(data1);
    postStr += "&field2=";
    postStr += String(data2);
    postStr += "&field3=";
    postStr += String(data3);
    postStr += "&field4=";
    postStr += String(data4);
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
    Serial.println(postStr);
  }
  client.stop();
  Serial.println("Waiting...");
  delay(2000);
}
