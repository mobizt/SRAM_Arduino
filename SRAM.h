#ifndef SRAM_H
#define SRAM_H

#include <Arduino.h>
#include <SPI.h>


// SRAM Instruction
#define READ  3
#define WRITE 2
#define RDMR  5 //Read Mode Register
#define WRMR  1 //Write Mode Register

// SRAM Hold line
#define HOLD 1

//Mode Register
#define BYTE_MODE (0x00 | HOLD)
#define PAGE_MODE (0x80| HOLD)
#define SEQUENTIAL_MODE (0x40| HOLD)

//SPI Clock divider
#define CLOCK_DIV2 SPI_CLOCK_DIV2
#define CLOCK_DIV4 SPI_CLOCK_DIV4
#define CLOCK_DIV8 SPI_CLOCK_DIV8
#define CLOCK_DIV16 SPI_CLOCK_DIV16
#define CLOCK_DIV32 SPI_CLOCK_DIV32
#define CLOCK_DIV64 SPI_CLOCK_DIV64
#define CLOCK_DIV128 SPI_CLOCK_DIV128

//SPI Mode
#define SPI0 SPI_MODE0
#define SPI1 SPI_MODE1
#define SPI2 SPI_MODE2
#define SPI3 SPI_MODE3

//SPI Bit order
#define MSB MSBFIRST 
#define LSB LSBFIRST 


typedef union {
  float floatData;
  long longData;
  int intData;
  byte byteData [sizeof(long)];
  uint16_t uint16Data;
  uint32_t uint32Data;
} dataUnion;


class SRAM
{
  private:
    uint8_t _sramCS;
    uint16_t _capacity;
    uint8_t _modeData;
    bool _sramState;
    dataUnion _sramData;
    void enableSRAM();
    void disableSRAM();
    void setAddress(uint32_t address);
    void setMode(uint8_t mode);
    void setModeRegister(uint8_t modeData);

  public:
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

};

#endif
