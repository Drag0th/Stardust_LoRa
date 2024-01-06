#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  #if defined(LoRa_Receiver)
    int a = 1;
  #endif  
  #if defined(LoRa_Transmitter)
    int a = 2;
  #endif
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}