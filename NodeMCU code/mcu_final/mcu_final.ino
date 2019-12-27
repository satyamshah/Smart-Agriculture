#include <ESP8266WiFi.h>
#include <FirebaseArduino.h> 
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

#define  ssid "Serbius"                                             // input your home or public wifi name 
#define password "..Password"   
SoftwareSerial s(D6,D5); 

int data1, data2, data3, data4, motor;

String buff;
#define FIREBASE_HOST "irrigation-2b3f7.firebaseio.com"
#define FIREBASE_AUTH "b1uBhgnuEq5jmCIe1V5DcORGRlTEvEyRKTodKw2R"

int valueFromString(String string, int x, int y)
{
   int value=0;
   for(int n=0; n<y; n++)
   {
    value=value*10+string[x+n]-'0'; 
   }
   return value;
}

void setup()
{
  pinMode(4,OUTPUT);
  s.begin(115200);
  Serial.begin(115200);
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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop()
{
  
  //-------------------------------Recieve Data from NODE--------------------------------//
  if (s.available() > 0)
  {
    delay(100);
    while (s.available() > 0)
    {
      buff = s.readString();
      if (buff[0] == '*')
      {
        if (buff[9] == '#')
        {
          Serial.println(buff);
          data1 =  valueFromString(buff,1,2);     //Reading 2 bit data
          data2 = valueFromString(buff,3,2);       //Reading 2 bit data
          data3 = valueFromString(buff,5,2);       //Reading 2 bit data
          data4 = valueFromString(buff,7,2);       //Reading 2 bit data
        }
      }
    }
  }
  //------------------------------------------------------------------------------------//

  //---------------------------------------Debug-------------------------------------//
  Serial.println(data1);
  Serial.println(data2);
  Serial.println(data3);
  Serial.println(data4);

  //--------------------------Sending Data to FireBase----------------------------//
  delay(10000);
  Firebase.pushInt("Temperature",data1);
  Firebase.pushInt("Humidity",data2);
  Firebase.pushInt("Light",data3);
  Firebase.pushInt("Moisture",data4);
  if (Firebase.failed()) // Check for errors 
  {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;}
  //------------------------------------------------------------------------------//
  Serial.println("Waiting...");
  delay(2000);

  motor=Firebase.getString("S1").toInt();
  Serial.print(motor);
  if(motor==1)
    digitalWrite(4,HIGH);
  if(motor==0)
    digitalWrite(4,LOW);
    
}
