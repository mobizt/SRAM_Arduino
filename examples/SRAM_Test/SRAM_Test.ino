/*
   Test setup for WEMOS D1 Mini (ESP8266) and 23LC1024 SRAM (1 Mbit)

   ---------------------------------------------------------------------------------
   WEMOS D1 Mini          23LC1024              Supply
   ---------------------------------------------------------------------------------
   D3 (GPIO0)             1 (CS)
   D6 (MISO)              2 (Slave Out)
                          3 (SIO2)               +3.3 or +5V (or via pullup resistor)
   GND                    4 (Vss)                GND
   D7 (MOSI)              5 (Slave In)
   D5 (SCK)               6 (SCK)
                          7 (/HOLD)              +3.3 or +5V (or via pullup resistor)
                          8 (Vcc)                +3.3 or +5V
*/



#include "SRAM.h"

SRAM sram;
uint8_t cs = D3;

void setup() {
  Serial.begin(115200);

  /*
     Initialize parameters

     csPin: SRAM Chip Select Pin

     SPI Clock divider:
     CLOCK_DIV2, CLOCK_DIV4, CLOCK_DIV8.. ,CLOCK_DIV128

     SPI Mode:
     SPI0 to SPI3

     SPI Bit order
     MSB and LSB

     SRAM Capacity in kilobit
     128, 256, 1024...
  */

  sram.init(cs, CLOCK_DIV2, SPI3, LSB, 1024);
}

void loop() {

  sram.writeInt(0, -12345);
  int c = sram.readInt(0);
  Serial.println(sram.readInt(0));


  char dataIn[30] = "Hello World!";
  char dataOut[30] = "";

  uint32_t len = sizeof(dataIn) / sizeof(dataIn[0]);
  sram.writeChars(0, dataIn, len - 1);
  sram.readChars(0, dataOut, len - 1);

  for (uint16_t i = 0; i < len - 1; i++) {
    Serial.print(dataOut[i]);
  }
  Serial.println();


  char pageDataIn[32] = "";
  char pageDataOut[32] = "";
  for (uint16_t i = 0; i < 32; i++)
    pageDataIn[i] = i;

  sram.writePage(0, pageDataIn);
  sram.readPage(0, pageDataOut);

  for (uint16_t i = 0; i < 32; i++) {
    Serial.print((uint8_t)pageDataOut[i]);
    Serial.print(" ");
  }
  Serial.println();


  uint32_t uint16DataIn[40];
  uint32_t uint16DataOut[40];
  for (uint16_t i = 0; i < 40; i++)
    uint16DataIn[i] = 65000 + i;

  sram.writeUnsignedInt32s(0, uint16DataIn, 40);
  sram.readUnsignedInt32s(0, uint16DataOut, 40);

  for (uint16_t i = 0; i < 40; i++) {
    Serial.print(uint16DataOut[i]);
    Serial.print(" ");
  }
  Serial.println();

  uint32_t uint32DataIn[40];
  uint32_t uint32DataOut[40];
  for (uint16_t i = 0; i < 40; i++)
    uint32DataIn[i] = 1230000000 + i;

  sram.writeUnsignedInt32s(0, uint32DataIn, 40);
  sram.readUnsignedInt32s(0, uint32DataOut, 40);

  for (uint16_t i = 0; i < 40; i++) {
    Serial.print(uint32DataOut[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();

  delay(1000);

}
