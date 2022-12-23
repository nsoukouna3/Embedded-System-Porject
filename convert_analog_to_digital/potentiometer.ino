int led =10;
int brightness=0;
int fadeAmount=5;
int analog_input_Pin=A0;
void setup() {
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(analog_input_Pin, INPUT);
}

void loop() {
  // read the input on analog pin0
  int sensorValue= analogRead(analog_input_Pin);
  brightness= sensorValue >>2;
  brightness = brightness + fadeAmount;
  Serial.println(brightness);
  analogWrite(led, brightness);
  if(brightness ==0 || brightness ==255){
    fadeAmount = -fadeAmount;
    

  }
  delay(30);

}





