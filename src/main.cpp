#define E22_30

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

int counter;
String status;

void display_data(SSD1306AsciiWire &display, ResponseContainer &data);

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
	configuration.ADDL = 2;
	configuration.ADDH = 2;
	configuration.CHAN = 0x17;
	configuration.TRANSMISSION_MODE.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
  configuration.OPTION.transmissionPower = POWER_30;
  configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
  configuration.SPED.uartBaudRate = UART_BPS_115200;
  configuration.SPED.uartParity = MODE_01_8O1;
  LoRa.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
	Response_Container.close();
}

void loop() {
  if (LoRa.available() > 0) {
		ResponseContainer Received_Data = LoRa.receiveMessage();
		if (Received_Data.status.code != 1) {
			Received_Data.status.getResponseDescription();
		} 
    else {
			Serial.println(Received_Data.data);
		}
    display_data(Oled, Received_Data);
	}
  counter++;
  delay(100);
  #if defined(LoRa_Receiver)
    LoRa.sendMessage("Pong! " + counter);
  #endif  
  #if defined(LoRa_Transmitter)
    LoRa.sendMessage("Ping! " + counter);
  #endif
}

void display_data(SSD1306AsciiWire &display, ResponseContainer &received_data) {
  display.setFont(System5x7);
  display.clear();
  display.println(received_data.data);
  display.println(received_data.rssi);
  display.println(received_data.status.getResponseDescription());
}