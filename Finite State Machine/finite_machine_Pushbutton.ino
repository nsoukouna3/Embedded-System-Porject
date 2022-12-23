#include <FiniteStateMachine.h>
#include <Button.h>
#include <LED.h>

const byte NUMBER_OF_STATES = 6;      // how many states are we cycling through?

// initialize states
State ledOn      = State(ledOn_fn);
State ledOff     = State(ledOff_fn);
State ledFadeIn  = State(ledFadeIn_fn);
State ledFadeOut = State(ledFadeOut_fn);
State buzzerOn = State(buzzerOn_fn);
State buzzerOff = State(buzzerOff_fn);

// declare objects and variables
FSM    ledStateMachine = FSM(ledOn);  // initialize state machine, start in state: On
Button button = Button(12, PULLDOWN); // initialize the button (wire between pin 12 and ground)
LED    led = LED(11);                 // initialize the LED

byte   buttonPresses = 0;             // counter variable, holds number of button presses
#define buzzer 10                     // initialize the pin 10 for buzzer
/********************************************************************************************/

void setup() {

  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);  // configure buzzer pin as output
}

/********************************************************************************************/

void loop() {
  if (button.uniquePress()) {
    // increment buttonPresses and constrain it to [ 0, 1, 2, 3 ]
    buttonPresses = ++buttonPresses % NUMBER_OF_STATES;
    switch (buttonPresses) {
      case 0: ledStateMachine.transitionTo(ledOn);      break;
      case 1: ledStateMachine.transitionTo(ledOff);     break;
      case 2: ledStateMachine.transitionTo(ledFadeIn);  break;
      case 3: ledStateMachine.transitionTo(ledFadeOut); break;
      case 4: ledStateMachine.transitionTo(buzzerOn);   break;
      case 5: ledStateMachine.transitionTo(buzzerOff);  break;
      
    }
  }
  ledStateMachine.update();
}

/********************************************************************************************/

// define state functions

void ledOn_fn()      { led.on();         Serial.println("led on");      }
void ledOff_fn()     { led.off();        Serial.println("led off");     }
void ledFadeIn_fn()  { led.fadeIn(250);  Serial.println("led fadeIn");  }
void ledFadeOut_fn() { led.fadeOut(500); Serial.println("led fadeOut"); }
void buzzerOn_fn() { digitalWrite(buzzer,HIGH); Serial.println("buzzer on"); } // buzzer turn On function
void buzzerOff_fn(){ digitalWrite(buzzer,LOW); Serial.println("buzzer off"); } // buzzer turn Off function

