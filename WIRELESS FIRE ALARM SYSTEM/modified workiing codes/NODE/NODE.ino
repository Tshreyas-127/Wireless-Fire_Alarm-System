//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//int LedPin = 13;
//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
int alarm = 10;
//address through which two modules communicate.
const byte address[6] = "00001";
const byte address1[6] = "00002";

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  pinMode(alarm, OUTPUT);
  digitalWrite(alarm, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();

  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
   // char text1[] = "FireInInnoLounge";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    //digitalWrite(LED_BUILTIN, HIGH);
    radio.stopListening();
    radio.openWritingPipe(address1);
    radio.write(&text, sizeof(text));
    digitalWrite(alarm, HIGH);
    //delay(1000);
  }
   
}