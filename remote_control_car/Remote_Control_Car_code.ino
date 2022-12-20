#include <IRremote.h> // IR library
#include<Servo.h>     // Servo Library
int led=13;

unsigned long timer1; // timer1 is incremented every 100ms = 0.1s
// IR pin 
int RECV_PIN = 9;
// motor pins
int right_tires_pin = 3;
int left_tires_pin =4;
int right_motor_PWM = 5;
int left_motor_PWM= 6;
unsigned long hex_value;

IRrecv irrecv(RECV_PIN);
decode_results results;
decode_results mode;


void motorRun(int speedl, int speedr);
int distance;
long duration, inches;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(led,OUTPUT);        // Start the receiver
  // setting up the tire pins mode
  pinMode(left_tires_pin, OUTPUT);
  pinMode(left_motor_PWM, OUTPUT);
  pinMode(right_tires_pin, OUTPUT);
  pinMode(right_motor_PWM, OUTPUT);
  // Ultrasonic settup
  pinMode(pingTrig, OUTPUT);
  pinMode(pingEcho, INPUT); 

}

void loop() {
  timers();
  led_flash_led1();
  if (timer1>=1)
  {//timer1 = 0;
    if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      irrecv.resume(); // Receive the next value
    }
   hex_value= results.value;
  }

  switch(hex_value){
    case 0XFF02FD:
              //Move forward
              motorRun(100, 100); 
              break;
    case 0XFF906F:
              //Turn right
              motorRun(100, -100);
              break; 
    case 0XFF9867:
              //Move back
            motorRun(-100, -100); 
            break;
    case 0XFFE01F:
              //Turn left
              motorRun(-100, 100);
              break;
    case 0XFFA25D:
              motorRun(0,0);
              break;              
    default:
          break;
  }
     
}

// Run the motor function
void motorRun(int leftspeed, int rightspeed) {
  int dirL = 0, dirR = 0;
  if (leftspeed > 0) {
    dirL = 0;
  }
  else {
    dirL = 1;
    leftspeed = -leftspeed;
  }
  if (rightspeed > 0) {
    dirR = 1;
  }
  else {
    dirR = 0;
    rightspeed = -rightspeed;
  }
  digitalWrite(left_tires_pin, dirL);
  digitalWrite(right_tires_pin, dirR);
  analogWrite(left_motor_PWM, leftspeed);
  analogWrite(right_motor_PWM, rightspeed);
}

void timers(void)
{
	static unsigned long ms_runtime;
	static int one_ms_timer;
	if(millis() > ms_runtime)
	{//code falls in this if statement every 1 ms
		ms_runtime++;
		one_ms_timer++;  
	}
	else if( millis() < ms_runtime)
	{
		ms_runtime = millis();
		one_ms_timer++;  
	}
	//else only executes ~ every 50 days
	if(one_ms_timer > 99) // every 100 ms
	{
		timer1++;
		timer2++;
		timer3++;
		one_ms_timer = 0;
		/* extra precaution
		if(timer1 < 4000000000)
			timer1++
		*/
	}
}
void led_flash_led1() 
{
	if(timer1<1)			//first 10 (10 times 100 ms = 1s)
		digitalWrite(led,HIGH); 
	else
	{
		digitalWrite(led,LOW);
		if(timer1>=2) //(between 10 and 20 - another 1 s)
			timer1 = 0;	//When does the timer get cleared?
  } 
}


