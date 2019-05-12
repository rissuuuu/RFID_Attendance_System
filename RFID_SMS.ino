#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x3F,20,4); 
#define SS_PIN 10
#define RST_PIN 9
SoftwareSerial mySerial(3, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String str1="a",str2="aa";
int buzzer=8;
 unsigned char i,j;
 
void setup() 
{
   //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Please Wait");
  delay(2000);
  lcd.setCursor(1,0);
  lcd.print("Scan your Card");
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  unsigned char i,j;
bool entered=true; 


// Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    // Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
   if (content.substring(1) == "50 D0 C8 57"){
  Serial.println("   Rishav Paudel");
  
 
   }
   if (content.substring(1) == "2B 73 02 89"){
  Serial.println("   Rishav Paudel");
   }
   
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "2B 73 02 89") //change here the UID of the card/cards that you want to give access
  {
    //Serial.println(" You Are Present");
    //delay(3000); 
    lcd.setCursor(1,0);
  lcd.print("               ");
    if(entered==true &&str1=="a"){
      Serial.println(" This is your 1st attendance");
      lcd.setCursor(1,0);
  lcd.print("Rishav Paudel");
      lcd.setCursor(2,1);
  lcd.print("1st attendance");
      beep();
      delay(3000);
       SendMessage();
      setin();
    str1="b";
    entered=false;
    }
    if(entered==true &&str1=="b"){
      Serial.println(" This is your 2nd attendance");
      lcd.setCursor(1,0);
  lcd.print("Rishav Paudel");
      lcd.setCursor(2,1);
  lcd.print("2nd attendance");
    beep();
    delay(3000);
       SendMessage();
    setin();
    str1="c";
    entered=false;
    }
    if(entered==true&&str1=="c"){
      Serial.println(" This is your 3rd attendance");
      lcd.setCursor(1,0);
  lcd.print("Rishav Paudel");
      lcd.setCursor(2,1);
  lcd.print("3rd attendance");
    beep();
    delay(3000);    
       SendMessage();
    setin();
  entered=false;
    str1="d";
    }
    if(entered==true && str1=="d"){
      Serial.println("Your Attendance limit for today has ended");
      lcd.setCursor(1,0);
  lcd.print("Rishav Paudel");
      lcd.setCursor(2,1);
  lcd.print("Limit Exceeded  ");
      beep();
      delay(100);
      beep();
      delay(100);
      beep();
       SendAlert();
      setin();
    }
    
    entered++;
    }
    else   {
   // Serial.println(" Access denied");
   // delay(3000);
  }
   //-----------------------------------------------------------------------------------------------------------------
   //-----------------------------------------------------------------------------------------------------------------
    
    if (content.substring(1) == "50 D0 C8 57") //change here the UID of the card/cards that you want to give access
  {
    //Serial.println(" You Are Present");
    //delay(3000);  
    lcd.setCursor(1,0);
  lcd.print("               ");
    if(entered==true &&str2=="aa"){
      Serial.println(" This is your 1st attendance");
      lcd.setCursor(1,0);
  lcd.print("Rishav Paudel");
      lcd.setCursor(2,1);
  lcd.print("1st attendance");
      beep();
      delay(3000);
       SendMessage();
      setin();
    str2="bb";
    entered=false;
    }
    if(entered==true &&str2=="bb"){
      Serial.println(" This is your 2nd attendance");
      lcd.setCursor(1,0);
  lcd.print("Rishav Paudel");
      lcd.setCursor(2,1);
  lcd.print("2nd attendance");
    beep();
    delay(3000);
       SendMessage();
    setin();
    str2="cc";
    entered=false;
    }
    if(entered==true&&str2=="cc"){
      Serial.println(" This is your 3rd attendance");
      lcd.setCursor(1,0);
  lcd.print("Rishav Paudel");
      lcd.setCursor(2,1);
  lcd.print("3rd attendance");
    beep();
    delay(3000);    
       SendMessage();
    setin();
  entered=false;
    str2="dd";
    }
    if(entered==true && str2=="dd"){
      Serial.println("Your Attendance limit for today has ended");
      lcd.setCursor(1,0);
  lcd.print("Rishav Paudel");
      lcd.setCursor(2,1);
  lcd.print("Limit Exceeded  ");
      beep();
      delay(100);
      beep();
      delay(100);
      beep();
       SendAlert();
      setin();
    }
    
    entered++;
    }
 
 else   {
    //Serial.println(" Access denied");
    //delay(3000);
  }
}
  void beep(){
    for(i=0;i<200;i++){
      digitalWrite(buzzer,HIGH);
    delay(1);
    digitalWrite(buzzer,LOW);
    delay(1);
      }
  }
  void setin(){
    lcd.setCursor(1,0);
  lcd.print("Scan your Card");
  lcd.setCursor(2,1);
  lcd.print("               ");
  }
  void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
void SendMessage()


{

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"9805398393\"\r"); // Replace x with mobile number

  delay(1000);

  mySerial.println("Rishav Paudel  is Present");// The SMS text you want to send

  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z

  delay(1000);

}
void SendAlert()


{

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"9805398393\"\r"); // Replace x with mobile number

  delay(1000);

  mySerial.println("Attendance Limit exceeded by rishav");// The SMS text you want to send

  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z

  delay(1000);

}
