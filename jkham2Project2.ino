/* Receiver code
This code is for the communications between Arduinos S & P using SoftwareSerial.
*/
#include <SoftwareSerial.h>

SoftwareSerial link(8, 9);

void setup() {
  Serial.begin(9600);
  link.begin(9600);
}

void loop() {

  if (link.available()) {
    char received = link.read();
    Serial.print("Received: ");
    Serial.println(received);

    link.write(received);
    Serial.println("Sent back");
  }

}
