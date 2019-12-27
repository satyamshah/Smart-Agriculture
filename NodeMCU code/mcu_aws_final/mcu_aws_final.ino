#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include <ESP8266AWSImplementations.h>

//--------------THINGSPEAK ----------------//
String apiKey = "4E5ECTO029RANUCT";                  //API KEY
const char* ssid = "Serbius";                        //Wi-Fi SSID 
const char* password = "..Password";                //Wi-Fi Pasword
const char* server = "api.thingspeak.com";          // Thingspeak api
//----------------------------------------//

//----------------AWS---------------------//

//----------------------------------------//

int data1, data2, data3, data4;


WiFiClient client;
unsigned char buff[10];
String buffer;

void setup()
{
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);                   //Connecting node to local wifi
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

  //---------------------------------------Connecting to aws----------------------------//
 
  //-----------------------------------------------------------------------------------//
  
}
void loop()
{
  
  //-------------------------------Recieve Data from NODE--------------------------------//
  if (Serial.available() > 0)
  {
    delay(100);
    while (Serial.available() > 0)
    {
      buffer = Serial.readString();
      if (buff[0] == '*')
      {
        if (buff[9] == '#')
        {
          Serial.println(buffer1);
          data1 = ((buff[1] - 0x30) * 10 + (buff[2] - 0x30));       //Reading 2 bit data
          data2 = ((buff[3] - 0x30) * 10 + (buff[4] - 0x30));       //Reading 2 bit data
          data3 = ((buff[5] - 0x30) * 10 + (buff[6] - 0x30));       //Reading 2 bit data
          data4 = ((buff[7] - 0x30) * 10 + (buff[8] - 0x30));       //Reading 2 bit data
        }
      }
    }
  }
  //------------------------------------------------------------------------------------//

  //-------------------------Sending data to AWS----------------------------------------//

  //------------------------------------------------------------------------------------//

  
  //-------------------------Sending data to Thingspeak---------------------------------//
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
  //---------------------------------------------------------------------------------------//
  
  client.stop();
  Serial.println("Waiting...");
  delay(2000);
}
