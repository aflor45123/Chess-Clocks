/*-----------------------------------------------
Name 1: Andres Flores / aflor45 / aflor45@uic.edu
Code contribution: Primary Arduino code

Name 2: Paola Magana  / pmaga2 / pmaga2@uic.edu
Code contribution: Secondary Arduino code

Name 3: Katie Lee-Olmstead / kleeo2@uic.edu
Code contribution: Communication between controller and primary

Name 4: Jennifer Khamdaraphone / jkham2 / jkham2@uic.edu
Code contribution: Communication between primary and secondary

Group number: 10

Project: The Final Countdown
Description: With this project, we are creating our own version of a chess clock. 
This chess clock will have multiple features such as: player name display, digital 
and analog time display, fan, and LEDs.

References:
- https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay/ 
- https://docs.arduino.cc/built-in-examples/digital/Button/
- https://docs.arduino.cc/built-in-examples/digital/Debounce/
- https://docs.arduino.cc/learn/electronics/lcd-displays/
- https://docs.arduino.cc/language-reference/en/functions/advanced-io/tone/
- https://docs.arduino.cc/libraries/servo/
- https://docs.arduino.cc/language-reference/en/functions/communication/serial/
- https://projecthub.arduino.cc/herolivechannel/chess-alarm-clock-using-arduino-rotary-encoder-7-segment-1511f2
- https://docs.arduino.cc/learn/communication/wire/
- https://www.instructables.com/I2C-between-Arduinos/
- https://github.com/fmalpartida/New-LiquidCrystal
----------------------------------------------*/

#define NOTE_C4  262

// LED
const int ledPIN_One = 12;
int ledState_A = HIGH;

// LED RGB
const int RGB_Red = 5;
const int RGB_Green = 6;
const int RGB_Blue = 9;
int red = 0;
int green = 0;
int blue = 0;

// Fan
int motorPin = 10;

// Buzzer
int melody = NOTE_C4;
int noteDuration = 60;

// Button
const int buttonPIN_A = 8;
int buttonState = HIGH;
int prevButtonState = LOW;

// Time
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long previous_Millis;
unsigned long time = 3000; // 3 seconds
unsigned long startTime;
unsigned long interval = 1000;


void setup() {
  pinMode(buttonPIN_A, INPUT_PULLUP);
  pinMode(ledPIN_One, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  startTime = millis();

}


void loop() {
  //unsigned long current_Millis = millis();
  unsigned long timeElapsed = millis() - startTime;
  unsigned long remaining;
  String messageReceived = "time low";
  String timeLow = "time low";
  String turnDone = "turn done";
  String win = "win";
  String lost = "lost";
  bool turn = false;


  // Listen for message from S
  /*if (Serial.available() > 0) {*/
    
    // If message is 'time low', change RGB color to Secondary (Red)
    if (messageReceived.compareTo(timeLow) == 0) {
      analogWrite(RGB_Red, 255);
      analogWrite(RGB_Green, 0);
      analogWrite(RGB_Blue, 0);
      //analogWrite(motorPin, 200);
    }

    // If turn is done, set turn to true
    if (messageReceived.compareTo(turnDone) == 0) {
      turn = true;
    }

    // If message is 'win', send 'lost' to C
    if (messageReceived.compareTo(win) == 0) {
      // Send lost to C
    }

    // If message is 'lost', send 'win' to C
    if (messageReceived.compareTo(lost) == 0) {
      // Send win to C
    }

  //}

  if (turn == true) {
    // Get time
    remaining = ((time - timeElapsed) / 1000);


    // time remaining
    if (remaining == 0) {
      // Send lost to C
    }

    // If message is 'time low', change RGB color to Primary (Green)
    else if (messageReceived.compareTo(timeLow)) {
      analogWrite(RGB_Red, 0);
      analogWrite(RGB_Green, 255);
      analogWrite(RGB_Blue, 0);
      //analogWrite(motorPin, 200);
    }

    else {
      // update analog time
      // update digital time


      // if button pressed double
        // send win to C

      // if button pressed once
        // stop timer, turn off led, turn = false, player buzzer, send turn done




    }

  }



  /*if (current_Millis - previous_Millis >= interval) {
    previous_Millis = current_Millis;

    if (current_Millis == 10000) {

    }

    if (current_Millis == 15000) {
      analogWrite(motorPin, 0);
    }
  }*/

  





  /*int reading_A = digitalRead(buttonPIN_A);

  if (reading_A != prevButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading_A != buttonState) {
      buttonState = reading_A;

      if (buttonState == HIGH) {
          ledState_A = !ledState_A;
      }
    }
  }

  tone(7, melody, noteDuration);
  
  digitalWrite(ledPIN_One, ledState_A);


  prevButtonState = reading_A;*/
}











