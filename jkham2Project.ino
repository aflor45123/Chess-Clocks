/* Sender code
This code is for the communications between Arduinos S & P using SoftwareSerial.
*/
#include <SoftwareSerial.h>

SoftwareSerial link(8, 9);

unsigned long lastSend = 0;
const unsigned long interval = 1000; // 1 second

void setup() {
  Serial.begin(9600);
  link.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSend >= interval) {
    lastSend = currentMillis;
    link.write('1');
    Serial.println("Sent: 1");
  }


  if (link.available()) {
    char received = link.read();
    Serial.print("Received: ");
    Serial.println(received);
  }
}
