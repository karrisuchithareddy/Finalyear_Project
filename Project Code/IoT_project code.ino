#include <LiquidCrystal.h>
#include <stdio.h>
//LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient http;

const char *ssid = "iotserver";
const char *password = "iotserver123";

int httpResponseCode;
String servername = "http://projectsfactoryserver.in/storedata.php?name=";
String accountname = "iot813";
String field1 = "&s1=";
String field2 = "&s2=";
String field3 = "&s3=";
String field4 = "&s4=";
String field5 = "&s5=";
String payload="";

/*
#include "DHTesp.h"
#define DHTpin 21
DHTesp dht;
*/

#include <Wire.h>

#include "DHT.h"
#define DHTPIN 21
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


int buzzer  = 23;
int mos     = 19;
int motor   = 18;


float tempc=0,humc=0;

unsigned char rcv,count,gchr,gchr1,robos='s';
 

int sti=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

/*
#define RXD2 16
#define TXD2 17
*/



int i=0,k=0,lop=0;

//int hbtc=0,hbtc1=0,rtrl=0;

unsigned char gv=0,msg1[10],msg2[11];
 
 int ii=0,rchkr=0;
 
void beep()
{
  digitalWrite(buzzer, LOW);delay(2000);digitalWrite(buzzer, HIGH);
}
void okcheck()
{
  unsigned char rcr;
  do{
      rcr = Serial.read();
    }while(rcr != 'K');
}


//int sts1=0,sts2=0,cntlmk=0;

int cntlmk=0;
int stn=0; 
int hbv=0;

String rain_string="";
String mos_string="";
//http://projectsfactoryserver.in/storedata.php?name=server65&lat=%s&lan=%s&s1=%s


void iot_send()
{
      lcd.setCursor(15,0);lcd.print("U");
      http.begin(servername + accountname + field1 + String(tempc) + field2 + String(humc) + field3 + mos_string);
      httpResponseCode = http.GET();
      if(httpResponseCode>0) 
        {
         payload="";
         //Serial.print("HTTP Response code: ");
         //Serial.println(httpResponseCode);
         payload = http.getString();
         //Serial.println(payload);
        }
      else 
        {
         ;
         //Serial.print("Error code: ");
         //Serial.println(httpResponseCode);
        }
      delay(3000); 
      lcd.setCursor(15,0);lcd.print(" ");
}         
         
void setup() 
{
  Serial.begin(9600);//serialEvent();
 // Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

+
  pinMode(motor, OUTPUT); pinMode(mos, INPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, HIGH);digitalWrite(motor, LOW);
  
  lcd.begin(16, 2);  
  lcd.print("   IOT Based");
  lcd.setCursor(0,1);
  lcd.print("   Agriculture");
  delay(2500);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) 
       {
           delay(500);
       }
  //Serial.println(WiFi.localIP());
  delay(3000);

  //dht.setup(DHTpin, DHTesp::DHT11);   
  dht.begin();
 
  lcd.clear(); 
  lcd.print("T:");
  lcd.setCursor(8,0);
  lcd.print("H:");
   
  lcd.setCursor(0,1);
  lcd.print("M:");//2
 
}

void loop() 
{  
  delay(500);  
   humc  = dht.readHumidity();
     tempc = dht.readTemperature();

  if(tempc == 295 || humc == 295)
    {
      goto mnp;
    }
  lcd.setCursor(2,0);convertl(tempc);
  lcd.setCursor(10,0);convertl(humc);

  if(tempc >= 38 || humc > 70)
    {
      beep();
      iot_send();
    }  
mnp:
 mos_string="";
 if(digitalRead(mos) == LOW)
   {
      lcd.setCursor(2,1);lcd.print("Wet");
      mos_string="Wet";digitalWrite(motor, LOW);
    //  iot_send();
   }   
 if(digitalRead(mos) == HIGH)
   {
      lcd.setCursor(2,1);lcd.print("Dry");
      mos_string="Dry";digitalWrite(motor, HIGH);
   }

 
 delay(1000);

 cntlmk++;

 if(cntlmk >= 40)
   {cntlmk = 0;
      iot_send();
   }
}




void serialEvent() 
{
  while (Serial.available()) 
        {
         
         char inChar = (char)Serial.read();
           if(inChar == '*')
             {
              gchr = Serial.read();
             }
           if(inChar == '#')
             {
              gchr1 = Serial.read();
             }   
        }
}



void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
  // lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}
