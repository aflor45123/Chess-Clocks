//Katherine Lee-Olmstead, kleeo2 660452626
//Lab 7 - Communication between Arduinos
//Description -  Send a signal between 2 Arduinos, using the button to toggle the other's LED.
//Assumptions - Both Arduinos and components are functional.
//Refrences
//  Profs, https://learn-us-east-1-prod-fleet02-xythos.content.blackboardcdn.com/5cc71db6522fe/55526862?X-Blackboard-S3-Bucket=learn-us-east-1-prod-fleet01-xythos&X-Blackboard-Expiration=1762203600000&X-Blackboard-Signature=8Jx9EasNDxd0qoteYvRASji5MxRYGYy5cVA7mYxIT64%3D&X-Blackboard-Client-Id=100219&X-Blackboard-S3-Region=us-east-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27CS%2520362%2520Lab%25207.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEJn%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJIMEYCIQCRtIcEuZI1t2FEKMr6ZieKZrmAsNJutMMoZ0yCNfy0xAIhAIoXV45h5jGxfF8GhREqLDBeJYqb1ex6unRGxBHdr1URKrQFCGIQBBoMNjM1NTY3OTI0MTgzIgzbZmwFRrCSvDU6xwEqkQVxlgJ95sBitTFmp9yQmccqn%2FHABiIAbZhgX%2BHAxWpVsJj6DIaAfq%2FyAM97Cbl7FSAJX2D9PXodZJttAGwQ4Q8ulLOjYbU9S%2FPPFQZ0rDzNnMSuwdXOWMh%2BPgqCF00J%2B3OZV4LVQoWE5zqOpIX5BX3VyBuy%2FzZ8rBgoqnfbhe5Y%2BSpLd7J%2Fbvza8hzTujCPCh7IeNmmBDH3%2F3HpFGl%2BIhFwEtTdV3qeTh2UB19PEIzBLNbBAnl%2Fu44HSLQB3loXPp%2B3edbsEtLhsvUq0d2MGkF6%2FxPmOxrngyrrtykKnJw7FI4NqUnghclGjqaRPiSVwsuw00qrAZ5u4DZ%2BfJijiZFrO8cGrP8FwQtZv8OMNT10O6CTQ%2FU5nRYv1%2F%2FD9U7hv7HqPmXtBOUeaE%2F6AtJnuBRbUPmZ0PsONw5G2X1DTt9HkuHF4b6n0qBkEQjoB4XF2474RhSlkgZGNQDwNm1fZHN%2BEL%2FeQsgmvRbXO8DfjpolpecDAEUEIPxqdK35IQ3alDpgddminxOAe6BgU%2BMm64q5BH0zt%2B2vacaHuFyj1kmRrWP%2FUXVUb5nbWKTSnjncZmzvFUxpCOYC1mKAm5GQHeG0A%2B75lEK78zpl3XFSTqHWw8m25lil%2Bc2RF%2FnTEpQVj5o64xkA0iSdX7SSimgqSRw3wRP%2Bz%2FzQc64pE%2Bpuvi9ae%2FNc2BPrh0WHPvB%2Fwasi1SkixQ87g4eJ07jE7SR4TYdY16Qq1C73OEy6PhEpSq6dFXtquKqXHWQeLx209vC%2B2hasHEF56f4E4zDlPxYalHPxmn0cI8UCKY1yiwQHdelRJrgquWPzsXMUqDO186CoT0TFYiwoMb%2F8mfvpeXX27qcaspU9SO0fLL%2FV56kH2%2Byr%2Bhkw6bKjyAY6sAFxRd1ZYpTfIPHy1bmGYnnAeW6DnQm6ifH1TtcG85mdq%2FccI7k4z4utfzvAfBmk6F1SpKjU7XHh8kIDbnMkYwcBTS15Aeyei1IVFnkI6tCdTXBT2p%2FOVKeku6hgIhG4OwqfwPXKNWSdXKnJbBV1YCgQH%2F0YFlT%2Fkk1FpqxLIIIPWtJuQbyq1241jRfwmMArTYFbgHJEpH%2Fql65OKchPAOF3mRTdpngwrvBa0tAiVpBfLA%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20251103T150000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PLUJXC4OG4%2F20251103%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=2d56a0cbaef648a5eb3e00ef36e4e5dcb296ce9c42f618f5bc3f9a2158398ef2
//   Jenn Case, https://robotic-controls.com/learn/arduino/arduino-arduino-serial-communication
//   Mikal Hart, https://docs.arduino.cc/learn/built-in-libraries/software-serial/#read
//TA name:

#include <SoftwareSerial.h>
using namespace std;

SoftwareSerial primary1 = SoftwareSerial(2, 3); //game between player 1 and player 2
SoftwareSerial primary2 = SoftwareSerial(4, 5); //game between player 3 and player 4

bool game1 = false;
bool game2 = false;
bool printed = false;

void setup() {
  primary1.begin(9600);
  primary2.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (primary1.available() > 0) {
    char recived = primary1.read();
    if(recived == 'w'){
      Serial.println("Game 1 concludes, player 1");
      game1 = true;
    }
    if(recived == 'l'){
      Serial.println("Game 1 concludes, player 2");
      game1 = true;
    }
  }

  if (primary2.available() > 0) {

    char recived = primary2.read();
    if(recived == 'w'){
      Serial.println("Game 1 concludes, player 3");
      game2 = true;
    }
    if(recived == 'l'){
      Serial.println("Game 1 concludes, player 4");
      game2 = true;
    }
  }

  if(game1 && game2 && (!printed)){
    Serial.println("Tournament round complete, both games concluded");
  }
}
