#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <LiquidCrystal_I2C.h>
int alarm = 10;

RF24 radio(9, 8);  // CE, CSN
const byte address1[6] = "00002";

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  pinMode(alarm, OUTPUT);
  digitalWrite(alarm, LOW);
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Wireless Fire");
  
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("System");
  delay(2000);
  lcd.clear();

  radio.begin();
  radio.openReadingPipe(0, address1);
  radio.startListening();
}

void loop()
{
  
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(text);
    lcd.setCursor(0, 0);
    lcd.print("Fire in M Block");
    digitalWrite(alarm, HIGH);
  }
    
}
