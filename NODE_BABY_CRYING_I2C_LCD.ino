/* www.learningbuz.com */
/*Impport following Libraries*/
const int ServoMotorpin = D8;
int humidity,temp,wl=0;
//const int bzr=D6;
const int ir=D5;
const int wmot=A0;
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27,16,2); 
#define DHTPIN D4                      // Digital Pin A1
#define DHTTYPE DHT11                  // We are Using DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() 
{
Serial.begin(9600);
 analogWrite(ServoMotorpin, 512);
 analogWriteFreq(50);
pinMode(ir,INPUT_PULLUP);
//pinMode(bzr,OUTPUT);
Wire.begin(D2,D1);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the 
delay(2000);
lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("  SMART CRADLE  "); //You can write 16 Characters per line .
lcd.setCursor(0,1);  //Defining positon to write from second row,first column .
lcd.print("     SYSTEM     ");
delay(3000); 


}

void loop() 
{
//Write your code

lcd.clear();  
lcd.setCursor(0,0);
lcd.print("T:    C H:    RH");
lcd.setCursor(0,1);
lcd.print("WET_L:      Cm  ");
delay(100);
analogWrite(ServoMotorpin, 40); 
//digitalWrite(bzr,0);
humidity =  dht.readHumidity();             // Reading Humidity Value
temp= dht.readTemperature();        // Reading Temperature Value
lcd.setCursor(11,0);
lcd.print(humidity);
lcd.setCursor(2,0);
lcd.print(temp);
lcd.setCursor(5,0);
lcd.print(char(223));
wl=analogRead(A0);
wl=map(wl,0,1023,200,0);
delay(100);
analogWrite(ServoMotorpin, 60);
lcd.setCursor(6,1);
lcd.print(wl);
delay(100);
analogWrite(ServoMotorpin, 40);
delay(100);
if(!digitalRead(ir))
{
//digitalWrite(bzr,1);
sendSMS();
}
else if(wl>=50)
{
//digitalWrite(bzr,1);
sendSMS1(); 
}
else if(temp>=35)
{
//digitalWrite(bzr,1);
sendSMS2(); 
}
else
{
//digitalWrite(bzr,0);
delay(200);  
}
}

void sendSMS()
{
  for(int x=0;x<2;x++)
  {
  lcd.clear();  
  lcd.setCursor(0,0);
  lcd.print(" Sending........");
  lcd.setCursor(0,1);
  lcd.print("SMS.............");
  delay(2000);
//  digitalWrite(bzr,1);

  Serial.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(1000);
  if(x==0)
  Serial.println("AT+CMGS=\"+919948724807\"");
  else
  Serial.println("AT+CMGS=\"+917036273544\"");  
  delay(1000);
  Serial.println(" Alert! Alert! Baby Moment detected (IR Sensor Activated !)");        // message to send
  delay(500);
  Serial.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(500); 
  Serial.println();
//  digitalWrite(bzr,0);
  digitalWrite(wmot,1);
  delay(2000);
  digitalWrite(wmot,0);
  lcd.clear();  
  lcd.setCursor(0,0);
  lcd.print("  Baby Moment   ");
  lcd.setCursor(0,1);
  lcd.print("Detected........");
  delay(2000);
}
Serial.println("ATD+919948724807;");
delay(10000);
Serial.println("ATH\r");
}
void sendSMS1()
{
  for(int x=0;x<2;x++)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sending SMS.....");
  lcd.setCursor(0,1);
  lcd.print("                ");
  //digitalWrite(bzr,1);
  delay(2000);
  

  Serial.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(1000);
  if(x==0)
  Serial.println("AT+CMGS=\"+919948724807\"");
  else
  Serial.println("AT+CMGS=\"+917036273544\"");  
  delay(1000);
  Serial.println(" Alert! Alert! Wetness Detected (Rain Sensor Activated !)");        // message to send
  delay(1000);
  Serial.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(500); 
  Serial.println();
  digitalWrite(wmot,1);
  delay(2000);  
  //digitalWrite(bzr,0);
  digitalWrite(wmot,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   WET Sensor   ");
  lcd.setCursor(0,1);
  lcd.print("Sensor Activated");
  delay(2000);
}}

void sendSMS2()
{
  for(int x=0;x<2;x++)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sending SMS.....");
  lcd.setCursor(0,1);
  lcd.print("                ");
  //digitalWrite(bzr,1);
  delay(2000);
  

  Serial.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(1000);
  if(x==0)
  Serial.println("AT+CMGS=\"+919948724807\"");
  else
  Serial.println("AT+CMGS=\"+917036273544\"");  
  delay(1000);
  Serial.println(" Alert! Alert! Temperature Exceeds >35 Deg.C (DHT11 Sensor Activated !)");        // message to send
  delay(1000);
  Serial.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(500); 
  Serial.println();
  digitalWrite(wmot,1);
  delay(2000);  
  //digitalWrite(bzr,0);
  digitalWrite(wmot,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  TEMP Sensor   ");
  lcd.setCursor(0,1);
  lcd.print("Sensor Activated");
  delay(2000);
}
Serial.println("ATD+919948724807;");
delay(10000);
Serial.println("ATH\r");
}
