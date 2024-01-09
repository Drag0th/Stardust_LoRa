#include <Arduino.h>
#include <LoRa_E22.h>
#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

#define M0 13
#define M1 14
#define AUX 15

#define I2C 0x3C

HardwareSerial Serial2(USART2);  
LoRa_E22 LoRa(&Serial2, AUX, M0, M1);
SSD1306AsciiWire Oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  Oled.begin(&Adafruit128x32, I2C);
  Oled.setFont(System5x7);
  Oled.clear();
  Oled.print("Setup in progress!");
  LoRa.begin();

  ResponseStructContainer Response_Container;
	Response_Container = LoRa.getConfiguration();
	Configuration configuration = *(Configuration*) Response_Container.data;
	configuration.ADDL = 3;
	configuration.ADDH = 0;
	configuration.CHAN = 0x04;
	configuration.TRANSMISSION_MODE.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
  configuration.OPTION.transmissionPower = POWER_22;
  configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
  configuration.SPED.uartBaudRate = UART_BPS_9600;
  configuration.SPED.uartParity = MODE_00_8N1;
  LoRa.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
	Response_Container.close();
}

void loop() {
  
}
