#include <Wire.h>
#include <SPI.h>
#include "RF24.h"  //Library for the transciever
#include <Adafruit_NeoPixel.h>
#define PIN 9
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

const int NeoPixel = 9;
const int LED =  5;  // LED or ignitor 
bool radioNumber = 0; // Channel for the radio
RF24 radio(9,10);     // clock and data pins for the transciever

byte addresses[][6] = {"1Node","2Node"};
int dataReceived;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pixel.begin();
  pixel.show(); // Initialize all pixels to 'off'
  radio.begin();
  
  radio.setChannel(108);
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1,addresses[0]);
  radio.startListening();
  delay(500);
}

void loop() {
  GreenPixel();
  
  if (radio.available()) // Check for incoming data from transmitter
    {
      while (radio.available())  // While there is data ready
        {
          radio.read( &dataReceived, sizeof(dataReceived) ); // Get the data payload (You must have defined that already!)
        }
      if (dataReceived == 1){
          digitalWrite(LED, HIGH);
          RedPixel();
          delay(5000);
          
          digitalWrite(LED, LOW);
          OffPixel();
          dataReceived = 0; 
        }
      if (dataReceived == 2){
          BluePixel();
          delay(150);
          
          OffPixel();
          delay(150);
        
          BluePixel();
          delay(150);
          
          OffPixel();
          dataReceived = 0; 
          delay(200);
        }
    }       
}

void RedPixel(){
  pixel.setPixelColor(0, pixel.Color(25,0,0));
  pixel.show();
}

void BluePixel(){
  pixel.setPixelColor(0, pixel.Color(0,0,25));
  pixel.show();
}

void YellowPixel(){
  pixel.setPixelColor(0, pixel.Color(25,20,0));
  pixel.show();
}

void GreenPixel(){
  pixel.setPixelColor(0, pixel.Color(0,25,0));
  pixel.show();
}

void OffPixel(){
  pixel.setPixelColor(0, pixel.Color(0,0,0));
  pixel.show();
}


