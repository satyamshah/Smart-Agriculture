#include <dht.h>                          //DHT library
#include <SoftwareSerial.h>               
#include <LiquidCrystal_I2C.h>            //LCD Library

SoftwareSerial mySerial(10, 11);          //Defininig serial port

LiquidCrystal_I2C lcd(0x27, 16, 2);
dht DHT;  
#define DHT22PIN A3
int ack, soil, light, motor=0;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(A0, INPUT);                   //Input for light sensor
  pinMode(A1, INPUT);                   //Input for soil moisture sensor
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Please wait for");
  lcd.setCursor(0, 1);
  lcd.print("2 seconds.");
  delay(2000);
  lcd.clear();
}

void loop()
{
  ack = 0;
  int chk = DHT.read22(DHT22PIN);

  //------------------------Check to see if dht is working-------------------------//
  switch (chk)
  {
    case DHTLIB_ERROR_CONNECT:
      ack = 1;
      break;
  }
  //------------------------------------------------------------------------------//

    light=analogRead(A1);                    //Reading light sensor data
    light=map(light, 0, 1023, 100, 0);
    
    soil=analogRead(A0);                    //Reading soil moisture data
    soil=map(soil, 0, 1023, 100, 0);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    
    lcd.print("Soil:");                   //Display soil data
    lcd.print(soil);
    lcd.print("%");
    
    lcd.setCursor(0, 1);
    lcd.print("Light:");                    //Display Light intensity
    lcd.print(light);
    lcd.print("%");
    
    delay(3000);
    lcd.clear();
    
    lcd.setCursor(0, 0);                      //Display dht data
    lcd.print("Temp:");
    lcd.print(DHT.temperature);
    lcd.print(" *C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity:");
    lcd.print(DHT.humidity);
    lcd.print("%");
    delay(3000);

    
  if (ack == 0)
  {
    Serial.print("Temperature(*C) = ");
    Serial.println(DHT.temperature, 0);
    Serial.print("Humidity(%) = ");
    Serial.println(DHT.humidity, 0);
    Serial.print("Soil(%) = ");
    Serial.println(soil);
    Serial.print("Light = ");
    Serial.println(light);
    Serial.println("-------------------------------");

    
    //------Sending Data to ESP8266--------//
    mySerial.print('*'); // Starting char
    mySerial.print(DHT.temperature, 0); //2 digit data
    mySerial.print(DHT.humidity, 0); //2 digit data
    mySerial.print(light);
    mySerial.print(soil);
    mySerial.println('#'); // Ending char
    //------------------------------------//

 
    delay(2000);                         //Sending data at interval of 2 seconds

    //-------------------------Sending Data from blynk--------------------------//
      
    //-------------------------------------------------------------------------//
  }
  
  if (ack == 1)
  {
    Serial.print("NO DATA");
    Serial.print("\n\n");
    delay(2000);
  }
}
