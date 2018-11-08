# SRAM_Arduino
SPI Static RAM library for Arduino

This library provides microcontroller to read and write data to external Static RAM through SPI interface.

The library was test and work well with Microchip SRAM and WEMOS D1 Mini (ESP8266) using the Arduino's standard SPI library.

Copyright (c) 2018 K. Suwatchai (Mobizt)

## Test Devices
Microchip SRAM 23LC1024, WEMOS D1 Mini (ESP8266 based module). Other SRAMs with different capacity also work well.

## Public functions

```c++

void init(uint8_t csPin, uint32_t clockDivider, uint8_t spiMode, uint8_t bitOrder, uint16_t kBit);
uint8_t readByte(uint32_t address);
void writeByte(uint32_t address, uint8_t data);
uint16_t readUnsignedInt16(uint32_t address);
uint16_t writeUnsignedInt16(uint32_t address, uint16_t data);
void readUnsignedInt16s(uint32_t address, uint16_t *data, uint32_t len);
void writeUnsignedInt16s(uint32_t address, uint16_t *data, uint32_t len);
uint32_t readUnsignedInt32(uint32_t address);
uint32_t writeUnsignedInt32(uint32_t address, uint32_t data);
void readUnsignedInt32s(uint32_t address, uint32_t *data, uint32_t len);
void writeUnsignedInt32s(uint32_t address, uint32_t *data, uint32_t len);
int readInt(uint32_t address);
void writeInt(uint32_t address, int data);
void readInts(uint32_t address, int *data, uint32_t len);
void writeInts(uint32_t address, int *data, uint32_t len);
long readLong(uint32_t address);
void writeLong(uint32_t address, long data);
void readLongs(uint32_t address, long *data, uint32_t len);
void writeLongs(uint32_t address, long *data, uint32_t len);
float readFloat(uint32_t address);
void writeFloat(uint32_t address, float data);
void readFloats(uint32_t address, float *data, uint32_t len);
void writeFloats(uint32_t address, float *data, uint32_t len);
void readChars(uint32_t address, char *data, uint32_t len);
void writeChars(uint32_t address, char *data, uint32_t len);
void readPage(uint32_t address, char *data);
void writePage(uint32_t address, char *data);
    
```
## Usages

```c++

/*
   Test setup for WEMOS D1 Mini (ESP8266) and 23LC1024 SRAM (1 Mbit)

   ---------------------------------------------------------------------------------
   WEMOS D1 Mini          23LC1024              Supply
   ---------------------------------------------------------------------------------
   D3 (GPIO0)             1 (CS)
   D6 (MISO)              2 (Slave Out)
                          3 (SIO2)               Vcc (or through pull-up resistor)
   GND                    4 (Vss)                GND
   D7 (MOSI)              5 (Slave In)
   D5 (SCK)               6 (SCK)
                          7 (/HOLD)              Vcc (or through pull-up resistor)
                          8 (Vcc)                Vcc (+3.3 for 23Kxxx or +3 to +5V for 23LCxxx)
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

     23K256 chip has 256 kilobits, 32768 bytes (128 bytes per kilobit) and 1024 pages (32 byts per page)
     23LC512 chip  has 512 kilobits, 65536 bytes and 2048 pages
     23LC1024 chip has 1024 kilobits, 131072 bytes and 4096 pages
  */

  sram.init(cs, CLOCK_DIV2, SPI0, LSB, 1024);
}

void loop() {


  sram.writeInt(0, -12345);
  Serial.print("Int value -> ");
  Serial.println(sram.readInt(0));

  sram.writeFloat(0, 12345.67);
  Serial.print("Float value -> ");
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
  for (uint8_t i = 0; i < 32; i++) {
    pageDataIn[i] = i;
  }

  for (uint16_t i = 0; i < 3; i++) {
    uint16_t address = i * 32;
    sram.writePage(address, pageDataIn);
  }

  for (uint16_t i = 0; i < 3; i++) {
    char pageDataOut[32] = "";
    uint16_t address = i * 32;
    sram.readPage(address, pageDataOut);
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
 
```
