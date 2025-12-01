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
#include <time.h>
#include <TM1637Display.h>
#include <Servo.h>

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

// Button 1
const int buttonPIN_A = 8;
int buttonState = HIGH;
int prevButtonState = LOW;

// Button 2
const int buttonPIN_B = 4;
int buttonState_B = HIGH;
int prevButtonState_B = LOW;


// Servo
Servo servo;
int pos = 0;

// Time
unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTime_B = 0;
unsigned long debounceDelay = 50;
tm currTime;
unsigned long lastUpdate = 0;
bool turn = false;


// Time segment
TM1637Display seg(3,2);
char timeBuf[10];


void displayTime() {
  int value = currTime.tm_min * 100 + currTime.tm_sec;
  seg.showNumberDecEx(value, 0b01000000, true);
}


void setup() {
  pinMode(buttonPIN_A, INPUT_PULLUP);
  pinMode(buttonPIN_B, INPUT_PULLUP);
  pinMode(ledPIN_One, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);

  currTime.tm_min = 10;
  currTime.tm_sec = 0;
  servo.attach(11);

  seg.setBrightness(7);
  displayTime();
}


void loop() {
  unsigned long current_Millis = millis();
  int reading_A = digitalRead(buttonPIN_A);
  int reading_B = digitalRead(buttonPIN_B);
  String messageReceived = "turn done";
  String timeLow = "time low";
  String turnDone = "turn done";
  String win = "win";
  String lost = "lost";


  // Listen for message from S
  /*if (Serial.available() > 0) {*/
    
    // If message is 'time low', change RGB color to Secondary (Red)
    if (messageReceived == timeLow) {
      analogWrite(RGB_Red, 255);
      analogWrite(RGB_Green, 0);
      analogWrite(RGB_Blue, 0);
      //analogWrite(motorPin, 200);
    }

    // If turn is done, set turn to true
    if (messageReceived == turnDone) {
      turn = true;
    }

    // If message is 'win', send 'lost' to C
    if (messageReceived == win) {
      // Send lost to C
    }

    // If message is 'lost', send 'win' to C
    if (messageReceived == lost) {
      // Send win to C
    }

  //}

  if (turn == true) {

    // Time remaining
    if (currTime.tm_min == 0 && currTime.tm_sec == 0) {
      // Send lost to C
    }

    // If message is 'time low', change RGB color to Primary (Green)
    else if (messageReceived == timeLow) {
      analogWrite(RGB_Red, 0);
      analogWrite(RGB_Green, 255);
      analogWrite(RGB_Blue, 0);
      //analogWrite(motorPin, 150);
    }

    else {

      if (millis() - lastUpdate >= 1000) {
        lastUpdate = millis();


      // Updating seconds
        if  ((currTime.tm_min > 0) || (currTime.tm_sec > 0)) {
          currTime.tm_sec--;

          // servo tick
          pos += 180;
          if (pos > 180) {
            pos = 0;
          }
          servo.write(pos);

          // Updating minutes
          if (currTime.tm_sec < 0) {
      	    currTime.tm_sec = 59;
      	    currTime.tm_min--;
          }
        }
        displayTime();
      }

      // if button pressed double
      // send win to C
      if (reading_B != prevButtonState_B) {
        lastDebounceTime_B = millis();
      }

      if ((millis() - lastDebounceTime_B) > debounceDelay) {
        if (reading_B != buttonState_B) {
          buttonState_B = reading_B;
        }

          if (buttonState_B == HIGH) {
            // send win;
          }
      }

      // if button pressed once
      // stop timer, turn off led, turn = false, player buzzer, send turn done
      if (reading_A != prevButtonState) {
      lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {

        if (reading_A != buttonState) {
        buttonState = reading_A;
        

          if (buttonState == HIGH) {
            ledState_A = LOW;
            turn = false;
            //tone(7, melody, noteDuration);
            // send turn done to S
          }

        }
      }
    }
  }

  digitalWrite(ledPIN_One, ledState_A);
  prevButtonState = reading_A;
}











