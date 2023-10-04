//Control LED Brightness with Rotary Encoder //

#include <Encoder.h> //includes the Encoder Library
Encoder myEnc(3,2);  // defines the Encoder object

//defining variables//
long int oldPosition = -999;
long int newPosition;
int const led = 6;

void setup()
{
  Serial.begin(9600); // begins the serial monitor
  Serial.println("Encoder Positions:"); // displays on serial monitor
  pinMode(led,OUTPUT); // sets the pinmode to output
  
}

void loop()
{
  newPosition= myEnc.read(); // reads position of the encoder
  if (newPosition !=oldPosition)
  {
    oldPosition=newPosition;
    Serial.println(newPosition);
    analogWrite(led,newPosition); 
    // sets the level(brightness) of the
    // led as per the encoder postion
    
  }
  
}
