#include <Arduino.h>
#include <LoRa_E22.h>
#include <config.h>

  HardwareSerial Serial1(USART1);
  LoRa_E22 LoRa(&Serial1, AUX, M0, M1);

void setup() {
  LoRa.begin();
}

void loop() {
  #if defined(LoRa_Receiver)
    int a = 1;
  #endif  
  #if defined(LoRa_Transmitter)
    int a = 2;
  #endif
}
