/* 
 FSM_RGB_LED
This program implements a Finite State Machine. External transition, caused by a user button press, will cause the FSM to advance to the next State.
*/

#include <FiniteStateMachine.h>
#include <Button.h>

const byte NUMBER_OF_STATES = 4;   //how many states are we cycling through?

//initialize states
State One    = State(One_fn);
State Two    = State(Two_fn);
State Three  = State(Three_fn);
State Four   = State(Four_fn);

FSM FSM_RGB_LED = FSM(One);        //initialize state machine, start in state: One

Button button = Button(A3,INPUT);  //initialize the button (wire between pin A3 and ground)
byte buttonPresses = 0;            //counter variable, holds number of button presses

// define LED pins
#define ledRed    9
#define ledGreen 10
#define ledBlue  11
#define analogPin A1
int brightness= 0;
int fadeAmount=5;
int sensorValue;

void led_brightness();

void setup(){ 
  pinMode(ledRed,   OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue,  OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  if (button.uniquePress()){
    //increment buttonPresses and constrain it to [ 0, 1, 2, 3 ]
    buttonPresses = ++buttonPresses % NUMBER_OF_STATES;
   
    switch (buttonPresses){
      case 0: FSM_RGB_LED.transitionTo(One);   break;
      case 1: FSM_RGB_LED.transitionTo(Two);   break;
      case 2: FSM_RGB_LED.transitionTo(Three); break;
      case 3: FSM_RGB_LED.transitionTo(Four);  break;
    }
  }
  FSM_RGB_LED.update();
}

//state functions
void One_fn()   { 
  led_brightness();
  analogWrite(ledRed,   brightness); Serial.println("Red LED on");}

void Two_fn()   { 
  led_brightness();
  analogWrite(ledGreen, brightness); Serial.println("Grn LED on");}

void Three_fn() {
  led_brightness(); 
  analogWrite(ledBlue,  brightness); Serial.println("Blu LED on");}

void led_brightness(){ 
  
  sensorValue = analogRead(analogPin);
  brightness= sensorValue >> 2;
  brightness = brightness + fadeAmount;
  Serial.print("Potention metter value: ");
  Serial.println(brightness);
}


void Four_fn()  { 
  digitalWrite(ledRed,   LOW); 
  digitalWrite(ledGreen, LOW); 
  digitalWrite(ledBlue,  LOW); 
  Serial.println("LEDs  off");
}
//end state functions
