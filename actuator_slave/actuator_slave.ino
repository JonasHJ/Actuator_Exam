//Libraries
#include <Wire.h>
 
// Pins
const char trigPin = 9;
const char echoPin = 10; 

// Global variables
unsigned long duration;

// Converting echo duration to cm
unsigned short cmDistance(unsigned long &duration)
{   
  return (duration*0.034)/2; 
}

void setup()
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  // Communication with master nr. 8
  Wire.begin(8);
  Serial.begin(9600);
}

void loop() 
{
  // When master requests, function requestEvent is called
  Wire.onRequest(requestEvent); 
}

void requestEvent() 
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin
  duration = pulseIn(echoPin, HIGH); 
  
  // Convert duration to cm
  unsigned short cmDist = cmDistance(duration);
  
  // Split distance to one byte (MSB)
  Wire.write(cmDist >> 8);
  
  // Split distance to the other byte (LSB)
  Wire.write(cmDist & 0xFF);
}
 






