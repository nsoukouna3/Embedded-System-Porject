const int Green_LED= 13;
const int Yellow_LED=12;
const int Red_LED=11;
const int USER_BUTTON_INPUT=2;
void setup()
{
  // initialize IO pins and serial port
  pinMode(Green_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(USER_BUTTON_INPUT, INPUT);
  Serial.begin(9600);
}
void loop()
{
  static int state;
  if(digitalRead(USER_BUTTON_INPUT)==1){
    state=1;
  }
  else{
    state=0;
  }
  if(state==1){
    for(int i=1; i<=3; i++){
      if(i==1){
        Serial.println("Green LED is ON.");
        digitalWrite(Green_LED, HIGH);
        delay(5000);
        Serial.println("Green LED is OFF");
        digitalWrite(Green_LED, LOW);
      }
      else if(i==2){
        Serial.println("Yellow LED is ON.");
        digitalWrite(Yellow_LED, HIGH);
        delay(1000);
        Serial.println("Yellow LED is OFF");
        digitalWrite(Yellow_LED, LOW);
      }
      else if(i==3){
        Serial.println("Red LED is ON.");
        digitalWrite(Red_LED, HIGH);
        delay(5000);
        Serial.println("Red LED is OFF");
        digitalWrite(Red_LED, LOW);
      }
    }
  }

