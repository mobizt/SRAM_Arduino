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

     23K256 chip has 256 kilobits, 32768 bytes (128 bytes per 1 kilobit) and 1024 pages (32 byts per page)
     23LC1024 chip has 1024 kilobits, 131072 bytes and 4096 pages
  */

  sram.init(cs, CLOCK_DIV2, SPI0, LSB, 1024);
}

void loop() {


  sram.writeInt(0, -12345);
  Serial.print("Int value -> ");
  Serial.println(sram.readInt(0));

  sram.writeFloat(0, 12345.67);
  Serial.print("Int value -> ");
  Serial.println(sram.readFloat(0));


  char dataIn[30] = "Hello World!";
  char dataOut[30] = "";

  uint32_t len = sizeof(dataIn) / sizeof(dataIn[0]);
  sram.writeChars(0, dataIn, len - 1);
  sram.readChars(0, dataOut, len - 1);

  Serial.print("string (char array) value -> ");
  for (uint16_t i = 0; i < len - 1; i++) {
    Serial.print(dataOut[i]);
  }
  Serial.println();


  char pageDataIn[32] = "";
  char pageDataOut[32] = "";


  for (uint8_t i = 0; i < 32; i++) {
    pageDataIn[i] = i;
  }

  for (uint16_t i = 0; i < 12; i++) {
    sram.writePage(i, pageDataIn);
  }

  for (uint16_t i = 0; i < 12; i++) {
    sram.readPage(i, pageDataOut);
    Serial.print("Page");
    Serial.print(i);
    Serial.print(" value -> ");
    for (uint16_t j = 0; j < 32; j++) {
      Serial.print((uint8_t)pageDataOut[j]);
      Serial.print(" ");
    }
    Serial.println();
  }


  uint16_t uint16DataIn[40];
  uint16_t uint16DataOut[40];
  for (uint16_t i = 0; i < 40; i++)
    uint16DataIn[i] = 65000 + i;

  sram.writeUnsignedInt16s(0, uint16DataIn, 40);
  sram.readUnsignedInt16s(0, uint16DataOut, 40);

  Serial.print("uint16_t array value -> ");
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

  Serial.print("uint32_t array value -> ");
  for (uint16_t i = 0; i < 40; i++) {
    Serial.print(uint32DataOut[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();

  delay(1000);

}
