#include<Servo.h>
const int pingTrig = A0;
const int pingEcho = A1;
int buzzer= 9;
int YellowLED=10;
int GreenLED=11;

int distance;
Servo myservo;

void setup(){
  myservo.attach(3);
  Serial.begin(9600);
  //initialize serial communication
  Serial.begin(9600);
 // initialize sensor pins
  pinMode(pingTrig, OUTPUT); // change A0 pin mode to digital output
  pinMode(pingEcho, INPUT); // change A1 pin mode to digital input
  pinMode(buzzer,OUTPUT);
  pinMode(YellowLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  

}

void loop() {
 
  long duration, inches, cm;
 // The HC-SR04 is triggered by a HIGH pulse of 2 or more microseconds.
 // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
  
  digitalWrite(pingTrig, LOW);
  delayMicroseconds( 5);
  digitalWrite(pingTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrig, LOW);
  // The Echo pin is used to read the signal from HC-SR04; a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(pingEcho, HIGH);
  // convert the time into a distance
  inches = microsecondsToInches(duration);

  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();
  delay(100);
  
  distance=constrain(inches,2,22);
  if(distance>1 && distance <5){
    
    digitalWrite(YellowLED, LOW);
    digitalWrite(GreenLED,LOW);
    sweepingServoMotor(90,180);
    delay(2000);
    digitalWrite(pingTrig, LOW);
    delayMicroseconds( 5);
    digitalWrite(pingTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingTrig, LOW);
    duration = pulseIn(pingEcho, HIGH);
    // convert the time into a distance
    inches = microsecondsToInches(duration);
    distance=constrain(inches,2,22);
      
    if (distance<5){
      digitalWrite(buzzer,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
      delay(2000);
      sweepingServoMotor(135,45);
  
    }
    
    else if(distance>5 && distance <10){
      digitalWrite(YellowLED,HIGH);
      digitalWrite(buzzer,LOW);
      digitalWrite(GreenLED,LOW); 
    }
    else {
      digitalWrite(GreenLED, HIGH);
      digitalWrite(buzzer, LOW);
      digitalWrite(YellowLED, LOW);
      sweepingServoMotor(180,45);
      
    }   

  }
    
  else if(distance>5 && distance <10){
    digitalWrite(YellowLED,HIGH);
    digitalWrite(buzzer,LOW);
    digitalWrite(GreenLED,LOW); 
  }
  else {
    digitalWrite(GreenLED, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(YellowLED, LOW); 
    
  }

  
}

void sweepingServoMotor(int start,int end){
  //sweeps servo from start position to end
  if(start == end)
    return;

  int step,i;

  if(start < end)
    step = 1;

  else
    step = -1;

  for(i = start;i != end;i+=step){
    //loops from start position to end position
    //with delay of 30 ms
    myservo.write(i);
    delay(30);

  }

  //myservo.write(i);
}

long microsecondsToInches(long microseconds)
{
 // According to the Ping sensor datasheet, there are
 // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
 // second). This gives the distance travelled by the ping, outbound
 // and return, so we divide by 2 to get the distance of the obstacle.
 return microseconds / 74 / 2;
}
