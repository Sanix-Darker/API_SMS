//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shields
//at 9600 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 
 
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
 
SoftwareSerial GPRS(7, 8);
unsigned char buffer[64]; // buffer array for data recieve over serial port
int count=0;              // counter for buffer array 

// Target Phone number
const char phoneNumberTarget = "+237690516182";

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// give the pin a name:
int led = 9;
// incoming serial byte
int inByte = 0;         
char c[33];

void setup()
{
  pinMode(9, OUTPUT);     
  lcd.begin(16, 2);
  lcd.print("SYSTEM STARTING.");
  lcd.setCursor(0, 1);
  lcd.print("    By S4n1X ");
  delay(1000); 
  // initialize the led pin as an output.
  pinMode(led, OUTPUT);  

  GPRS.begin(9600);     // the GPRS baud rate   
  Serial.begin(9600);   // the Serial port of Arduino baud rate. 
}


void loop()
{

  // Printing the SMS in the LCD
  if (GPRS.available())              // if date is comming from softwareserial port ==> data is comming from gprs shield
  {
    while(GPRS.available())          // reading data into char array 
    {
      buffer[count++]=GPRS.read();   // writing data into array
      if(count == 64)break;
    }
    Serial.write(buffer,count);   // if no data transmission ends, write buffer to hardware serial port
    clearBufferArray();           // call clearBufferArray function to clear the storaged data from the array
    count = 0;                    // set counter of while loop to zero
  }
  //if (Serial.available())         // if data is available on hardwareserial port ==> data is comming from PC or notebook
    //GPRS.write(Serial.read());    // write it to the GPRS shield

  // Testing the Module
  GPRS.write("AT+CMGF=1\r");
  delay(200);

  // Reading recents Unread SMS
  GPRS.write("AT+CMGR=1\r");
  int i = 0;
  while ( Serial.available()> 0){
    c[i] = Serial.read();
    Serial.print(c[i]);
    if(i==16){
      lcd.setCursor(0,1);
    }
    lcd.print(c[i]);
    i++;  
  }
  delay(300);
  
  // Sending a message
  GPRS.write("AT+CMGS=+237690516182");
  delay(200);
  GPRS.write("Test de message...");
  delay(5500);
//

  // Printing Message from the Serial Port
  if( Serial.available() ){
    lcd.clear();
    Serial.println("Serial available");
    int i = 0;
    while ( Serial.available()> 0){
      c[i] = Serial.read();
      Serial.print(c[i]);
      if(i==16){
        lcd.setCursor(0,1);
      }
      lcd.print(c[i]);
      i++;  
    }
    delay(3500);
  }else{
    lcd.clear();
    lcd.print ( "waiting..." );
  }
  delay(100);
}

void clearBufferArray()           // function to clear buffer array
{
  for (int i=0; i<count;i++)
    { buffer[i]=NULL;}            // clear all index of array with command NULL
}
