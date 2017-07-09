#include <Stepper.h>
#include <SoftwareSerial.h>

const int stepsPerRevolution = 200;
const int sensorPin = A0;

int monitoring;
int metalDetection = 1;
float metalDetected;
int force;
int resetSteps = 21;
int steps = 10;

Stepper myStepper(stepsPerRevolution, 3, 4); 
SoftwareSerial bluetooth(7, 6);
  
  void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 bluetooth.begin(9600);
 myStepper.setSpeed(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  monitoring = analogRead(metalDetection);
  force = analogRead(sensorPin);
  metalDetected = (float) monitoring*100/1024.0;
  
  if(metalDetected < 90){
    myStepper.step(-100);  
    Serial.println("moving");
    if(force == 0){
      bluetooth.println("Measuring");  
    }
    resetSteps--;
  }
  if(metalDetected < 90 && force > 0 && steps != 0){
    myStepper.step(-100);
    steps--;
    Serial.println(steps);  
  }

  if(metalDetected > 90 && resetSteps <= 20){
    myStepper.step(100);
    resetSteps++;
    Serial.println(resetSteps);
    steps = 50;
  }
    
  //Send pressure value to phone
      if(force < 10 ){
      bluetooth.print(0);
    }else if (force > 9){
      bluetooth.print(1);
    }
  Serial.println(force);

  
  
}
