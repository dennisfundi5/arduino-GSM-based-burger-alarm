#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial SMS(9, 10);// rx(9) and tx(10)
                          // rx(9-arduino) connect to tx(gsm module)
    // tx(10-arduino) connect to rx(gsm module)
int _timeout;
String Arsp,GRsp;
String number = "+254713759499"; //-> change with your number
#define Switch 7
#define Buzzer 8
void setup()
{
pinMode(Switch, INPUT); 
pinMode(Buzzer, OUTPUT);
SMS.begin(9600);       // baud rate for gsm module  
Serial.begin(9600);    // baud rate for serial monitor 
lcd.begin(16,2);
delay(1000);
}
void loop()
{
  int x=digitalRead(7);
  lcd.setCursor(0,0);
  lcd.print("ACTIVATED");
 
  
  if (x==HIGH)
  {
    lcd.setCursor(0,1);
    lcd.print("Message sent");
    Serial.println("message sent");

    digitalWrite(Buzzer,1);
    delay(10000);
    noTone(Buzzer);
    delay(10000);
    sendmessage();
    recievemessage(); // to receive message enable receivemessage function 
                         // and "//" the sendmessage function
    //makecall();
    //receivecall();                     
  }
   if (SMS.available()>0){// verify any bits which income through pins 9 and 10
   Serial.write(SMS.read());// write income data on serial monitor
 }
}
 void sendmessage()
{
  SMS.println("AT+CMGF=1"); //AT command for text mode of gsm module 
  delay(1000);  
 SMS.println("AT+CMGS=\"+254782891836\""); //  x is your mobile number
  delay(1000);
  SMS.println("visitor on the gate");// the text you want to send
  delay(100);
  SMS.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void recievemessage()
{
   Serial.println ("SIM800L Read an SMS");
  delay (1000);
  SMS.println("AT+CNMI=2,2,0,0,0\r"); // AT command to receive SMS
  delay(1000);
  SMS.println("AT+CMGR=1\r");//AT command to read sms
  //IE=0X90;   // Enable serial interrupt
delay(5000);
 }
 

