/*
 Puffer pulse generator
 
 Turns on an LED and a digital output on for defined duration.
 Does once per button push, detected as a closure on DIO 1
 Duration of the pulse is set by the voltage on A0 (analog input)
 Fixed durations for a range of 5 voltages.
 
 The circuit:
 * LED connected from digital pin 13 to ground.
 * Pushbutton input (NO) Pin 9 to graound
 * Potentiometer (1MOhm) Wiper to A0, left to ground, right to 3.3V (NOT 5)
 
   The potentiometer reports from 0 to 667. We use this to scale the pulse
   duration, from 10 to 500 msec. 
 * Note: On most Arduino boards, there is already an LED on the board
 connected to pin 13, so you don't need any extra components.
 
Based on the arduino tutorial for "blink"
 
 pbm 26 Jan 2017.
 
 */

// Pin definitions:
int ledPin =  13;    // LED connected to digital pin 13
int pufferPin = 12; // use pin 12 for output
int triggerPin = 9; // use pin 9 as input for triggering
int durationms = 10;  // duration of the output pulse
int potentiometer = 0; // read A0

// Variables :
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


// The setup() method runs once, when the sketch starts
// Serial is disabled as not needed except for testing
void setup()   {                
  // initialize the digital pin as an output:
  pinMode(ledPin, OUTPUT);    
  pinMode(triggerPin, INPUT_PULLUP);    
  pinMode(pufferPin, OUTPUT);
//  Serial.begin(9600);
}

// the loop() method runs over and over again,
// as long as the Arduino has power
// potentiometer range is 0-667

void loop()                     
{
  // code copied from debounce example on arduino site
  // read the state of the switch into a local variable:
  int reading = digitalRead(triggerPin);
  int pot = analogRead(potentiometer);
//  Serial.println(pot); // enable for testing
  
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is LOW
      if (buttonState == LOW) {
        ledState = !ledState;
        digitalWrite(ledPin, HIGH);   // set the LED on
        digitalWrite(pufferPin, HIGH);
        // convert A0 to 10-500 msec in 10 msec steps
        durationms = map(pot, 0, 667, 0, 10);
        durationms = constrain(durationms*50 + 10, 10, 500);
        delay(durationms);                  // wait for a second
        digitalWrite(ledPin, LOW);    // set the LED off
        digitalWrite(pufferPin, LOW);
        delay(500);  // force 1 sec delay after each pulse
      }
    }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
