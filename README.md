# SRAM_Arduino
SPI Static RAM Library for Arduino

## Test Devices
23K256, 23LC512 and 23LC1024

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

     SPI Bit order
     MSB and LSB

     SRAM Capacity in kilobit
     128, 256, 1024...
  */

  sram.init(csPin, CLOCK_DIV2, SPI3, LSB, 1024);
}

void loop() {

  sram.writeInt(0, 12345);
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
