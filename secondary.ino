#include <time.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>

// pins
int buttonPin = 13;
int ledPin = 12;
int buzzerPin = 11;

// servo
Servo servo;
int pos = 0;

// led states
bool ledState = false;

// button states
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// time
tm currTime;
unsigned long lastUpdate = 0;

// lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

// segment
TM1637Display seg(9,8);
char timeBuf[10];



void displayTime() {
  int value = currTime.tm_min * 100 + currTime.tm_sec;
  seg.showNumberDecEx(value, 0b01000000, true);
}


void setup()
{
  Serial.begin(9600);
  
  currTime.tm_min = 10;
  currTime.tm_sec = 0;
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  servo.attach(10);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("name1 vs. name2");

  seg.setBrightness(true);
  displayTime();
}


void loop()
{
  unsigned long currMillis = millis();
  int reading = digitalRead(buttonPin);
  
  // button press
  if (reading == LOW && lastButtonState == HIGH) {
    if ((currMillis - lastDebounceTime) > debounceDelay) {
      lastDebounceTime = currMillis;
      
      // toggle LED
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      
      // buzz when turn starts/ends
      if (ledState)
        tone(buzzerPin, 700, 100);
      if (!ledState)
      	tone(buzzerPin, 500, 100);
    }
  }
  
  // update time
  if (millis() - lastUpdate >= 1000 && ledState) {
    lastUpdate = millis();
    
    // update seconds
    if (currTime.tm_min > 0 || currTime.tm_sec > 0) {
      currTime.tm_sec--;
      
      // servo tick
      pos += 180;
      if (pos > 180) {
        pos = 0;
      }
      servo.write(pos);
      
      // update minutes
      if (currTime.tm_sec < 0) {
      	currTime.tm_sec = 59;
      	currTime.tm_min--;
      }
    }
    
    // format time
    displayTime();
  	
  }
  
  lastButtonState = reading;
}