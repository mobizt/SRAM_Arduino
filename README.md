# SRAM_Arduino
SPI Static RAM Library for Arduino

## Test Devices
23K256, 23LC512 and 23LC1024

## Public functions

```c++

void init(uint8_t csPin, uint32_t clockDivider, uint8_t spiMode, uint8_t bitOrder, uint16_t kBit);

    uint8_t readByte(uint32_t address);

    void writeByte(uint32_t address, uint8_t data);

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
#include "SRAM.h"

SRAM sram;
uint8_t csPin = D3;

void setup() {
  Serial.begin(115200);

  /*
     Initialize parameters

     csPin: SRAM Chip Select Pin

     SPI Clock divider:
     CLOCK_DIV2, CLOCK_DIV4, CLOCK_DIV8.. ,CLOCK_DIV128

     SPI Mode: 
     SPI0 to SPI3

     SPI Bit order: MSB and LSB

     SRAM Capacity in kilobit:
     128, 256, 1024...
  */

  sram.init(csPin, CLOCK_DIV2, SPI3, LSB, 1024);
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

  delay(1000);

}
```
