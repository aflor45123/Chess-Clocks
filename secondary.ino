#include <time.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>
#include <SoftwareSerial.h>

// Setting up software serial
SoftwareSerial link(7,10);

// pins
int buttonPin = 13;
int ledPin = 12;
int buzzerPin = 11;
int victoryPin = 9;

// servo
Servo servo;
int pos = 0;

// led states
bool ledState = false;

// button states
int lastButtonState1 = 0;
int lastButtonState2 = 0;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay = 50;

// time
tm currTime;
unsigned long lastUpdate = 0;

// lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

// segment
TM1637Display seg(3,2);
char timeBuf[10];

// turn
bool isTurn = false;
char messageReceived;

void displayTime()
{
  int time = currTime.tm_min * 100 + currTime.tm_sec;
  seg.showNumberDecEx(time, 0b01000000, true);
}

void sendTurn() {
  link.write('T');
  Serial.println("Sent turn to P");
}

void setup()
{
  Serial.begin(9600);
  link.begin(9600);
  
  currTime.tm_min = 2;
  currTime.tm_sec = 0;
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  servo.attach(8);
  
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
  int reading1 = digitalRead(buttonPin);
  int reading2 = digitalRead(victoryPin);

  // Reading from P
  if (link.available()) {
    messageReceived = link.read();
    Serial.println(messageReceived);
    if (messageReceived == 'T') {
      Serial.println("Received turn from S");
      isTurn = true;
    }
  }
  
  // button press
  if (reading1 == LOW && lastButtonState1 == HIGH) {
    if ((currMillis - lastDebounceTime1) > debounceDelay) {
      lastDebounceTime1 = currMillis;
      
      // toggle LED
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      
      // buzz when turn starts/ends
      if (ledState) {
        tone(buzzerPin, 700, 100);
    }
      if (!ledState) {
      	tone(buzzerPin, 500, 100);
        // Send turn to P
        isTurn = false;
        sendTurn();
      }

    }
  }

  // victory button press
  if (reading2 == LOW && lastButtonState2 == HIGH) {
    if ((currMillis - lastDebounceTime2) > debounceDelay) {
      lastDebounceTime2 = currMillis;
      tone(buzzerPin, 1000, 500);
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
    if (currTime.tm_min < 1) {
      link.write('L');
      Serial.println("Sent time low to P");
    }
    // format time
    displayTime();
  }
  
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
}
