// pre-processor directives
// pin name definitions
#define LDR_pin A0
#define LED_RED_pin 9
#define LED_YELLOW_pin 10
#define LED_GREEN_pin 11
#define LED_BUILTIN_pin 13  // Arduino board LED_BUILTIN
// class/object declarations: none
// global variables:
int  sensorVal;
char command = '0';
void setup() {   // code in setup() function runs only once

  // configure hardware peripherals, initialize LED pins as OUTPUTs
  pinMode(LED_RED_pin, OUTPUT);
  pinMode(LED_YELLOW_pin, OUTPUT);
  pinMode(LED_GREEN_pin, OUTPUT);
  pinMode(LED_BUILTIN_pin, OUTPUT);
  // configure data communication
  Serial.begin(9600);  // initialize serial port
  Serial.println("Test Program for Data Comm Sub-system"); // print message on Serial Mon-itor
}

void loop() {
  // Read sensor value and send sensor value to PC
  // data input, data storage and data processing
  sensorVal = analogRead(LDR_pin); // read sensor value from analog pin A0
  sensorVal = sensorVal >> 2;      // convert sensor value from 10-bits to 8-bits ...
                                   // by using bit shift operation
  // data communication
  Serial.println(sensorVal);       // send sensor value to PC Serial Monitor
  // -----------------------------------------------------------
  // Read command keystroke from PC Serial Monitor and control output device (LED)
  if (Serial.available())
    command = Serial.read();         // read command character from PC keyboard
  Serial.println(command);
  // data processing and data output
  switch (command) {
    // activate output device according to command
    case '0':
      digitalWrite(LED_RED_pin, LOW);  // turn output device OFF
      break;
    case '1':
      digitalWrite(LED_RED_pin, HIGH); // turn output device ON
      break;

    case '2':
      digitalWrite(LED_YELLOW_pin, LOW);
      break; 
    case '3':
      digitalWrite(LED_YELLOW_pin, HIGH);
    case '4':
      digitalWrite(LED_GREEN_pin, LOW);
      break;      
    case '5':
      digitalWrite(LED_GREEN_pin, HIGH);

    
    default:
      // do nothing for other command values
      break;
  }
  // -----------------------------------------------------------
  // toggle LED_C_pin 13 heartbeat LED to indicate that the code is running
  digitalWrite(LED_BUILTIN_pin, HIGH); delay(100);
  digitalWrite(LED_BUILTIN_pin, LOW);  delay(100);
}
// user defined functions: none


