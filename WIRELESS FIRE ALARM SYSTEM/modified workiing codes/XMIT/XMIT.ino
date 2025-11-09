#define Threshold 275
#define MQ2pin 0

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int alarm = 10;

float sensorValue;                      //variable to store sensor value
RF24 radio(9, 8);                       // CE, CSN
const byte address[6] = "00001";

void setup()
{ 
  Serial.begin(9600);                   // sets the serial port to 9600
  Serial.println("MQ2 warming up!");
	delay(5000);                         // allow the MQ2 to warm up
  pinMode(alarm, OUTPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop()
{
  sensorValue = analogRead(MQ2pin); // read analog input pin 0
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if(sensorValue > Threshold)
    {
      Serial.println("Smoke detected!");
      const char text[] = "Fire in M Block";
      radio.write(&text, sizeof(text));
      digitalWrite(alarm, HIGH);
      delay(2000);
      digitalWrite(alarm, LOW);
      delay(500);

    }
     //delay(2000);
}