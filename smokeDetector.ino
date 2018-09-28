#include <Stepper.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int falseAlarmButton=2;
int triggerButton=3;
bool ledOn=true;
const int stepsPerRevolution = 400;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(falseAlarmButton, INPUT_PULLUP);
  pinMode(triggerButton, INPUT_PULLUP);
  digitalWrite(ledPin,LOW);
  myStepper.setSpeed(60);
  Serial.begin(9600);
}
bool isPushed(int pin)
{
  if(digitalRead(pin)==false)
    return true;

  return false;
}
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if(sensorValue>500)
  {
    digitalWrite(ledPin,HIGH);
   

  }
  if(isPushed(falseAlarmButton))
  {
    digitalWrite(ledPin,LOW); 
     Serial.println("False Alarm");
    while(digitalRead(falseAlarmButton) == false); 
    
    
  }
  if(isPushed(triggerButton) && digitalRead(ledPin)==true)
  {
    digitalWrite(ledPin,LOW); 
     Serial.println("Turning gas connection off");
    myStepper.step(stepsPerRevolution*5);
    while(digitalRead(triggerButton) == false); 
    
    
  }
  delay(50);
  

}
