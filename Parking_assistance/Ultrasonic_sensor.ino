const int pingTrig = A0;
const int pingEcho = A1;
int RedLED= 9;
int YellowLED=10;
int GreenLED=11;
int distance;
int ledDistance;
int brightness_values;

void Led_Control_Distance(int ditance);
void setup() {
  // initialize serial communication
  Serial.begin(9600);
  // initialize sensor pins
  pinMode(pingTrig, OUTPUT); // change A0 pin mode to digital output
  pinMode(pingEcho,  INPUT); // change A1 pin mode to digital input
  pinMode(RedLED,OUTPUT);
  pinMode(YellowLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The HC-SR04 is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
  digitalWrite(pingTrig,  LOW);
  delayMicroseconds( 5);
  digitalWrite(pingTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrig,  LOW);

  // The Echo pin is used to read the signal from HC-SR04; a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(pingEcho, HIGH);
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
  distance=constrain(inches,2,22);
  Led_Control_Distance(distance);
}
long microsecondsToInches(long microseconds)
{
  // According to the Ping sensor datasheet, there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.

  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  
  return microseconds / 29 / 2;
}
void Led_Control_Distance(int distance){
  if(distance>=2 && distance <=8){
    digitalWrite(RedLED, HIGH);
    digitalWrite(YellowLED, LOW);
    digitalWrite(GreenLED,LOW);
  }
  else if(distance>=9 && distance <=15){
    digitalWrite(YellowLED,HIGH);
    digitalWrite(RedLED,LOW);
    digitalWrite(GreenLED,LOW);   
  }
  else if(distance >=16 && distance<22){
    digitalWrite(GreenLED, HIGH);
    digitalWrite(RedLED, LOW);
    digitalWrite(YellowLED, LOW);
  }
  else if (distance>=22){
    digitalWrite(RedLED,LOW);
    digitalWrite(YellowLED,LOW);
    digitalWrite(GreenLED,LOW);

  }
}
