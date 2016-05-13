#include <SPI.h>
#include "RF24.h"  //Library for the transciever

const int LED =  3;  // LED or ignitor 
const int Ready = 4; // Use this for an LED that will glow when it's turned on, so I know it's armed. 
bool radioNumber = 0; // Channel for the radio
RF24 radio(9,10);     // clock and data pins for the transciever

byte addresses[][6] = {"1Node","2Node"};
int dataReceived;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(Ready, OUTPUT);
  radio.begin();
  
  radio.setChannel(108);
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1,addresses[0]);
  radio.startListening();
  delay(500);
}

void loop() {
  digitalWrite(Ready, HIGH); 
  
  if (radio.available()) // Check for incoming data from transmitter
    {
      while (radio.available())  // While there is data ready
      {
        radio.read( &dataReceived, sizeof(dataReceived) ); // Get the data payload (You must have defined that already!)
      }
      if (dataReceived == 1){
        digitalWrite(LED, HIGH);
        delay(700);
        digitalWrite(LED, LOW);
        dataReceived = 0; 
      }
      //Serial.print("Data received = ");
     //Serial.println(dataReceived);
    }       
}



