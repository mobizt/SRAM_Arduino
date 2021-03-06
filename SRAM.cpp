/*
 * SPI Static RAM library for Arduino
 * 
 * This library provides microcontroller to read and write data to external Static RAM
 * through SPI interface. 
 * 
 * The library was test and work well with Microchip SRAM and WEMOS D1 Mini (ESP8266) using
 * the Arduino's standard SPI library.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2018 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include "SRAM.h"

void SRAM::init(uint8_t csPin, uint32_t clockDivider, uint8_t spiMode, uint8_t bitOrder, uint16_t kBit) {
  _sramCS = csPin;
  _capacity = kBit;
  pinMode( _sramCS, OUTPUT);
  _sramState = true;
  disableSRAM();
  SPI.setClockDivider(clockDivider);
  SPI.setDataMode(spiMode);
  SPI.setBitOrder(bitOrder);
  SPI.begin();
}

uint8_t SRAM::readByte(uint32_t address) {
  uint8_t data;
  setModeRegister(BYTE_MODE);
  SPI.transfer(READ);
  setAddress(address);
  data = SPI.transfer(0x00);
  disableSRAM();
  return data;
}

void SRAM::writeByte(uint32_t address, uint8_t data) {
  setModeRegister(BYTE_MODE);
  setMode(WRITE);
  setAddress(address);
  SPI.transfer(data);
  disableSRAM();
}

uint16_t SRAM::readUnsignedInt16(uint32_t address) {
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  _sramData.byteData[0] = SPI.transfer(0x00);
  _sramData.byteData[1] = SPI.transfer(0x00);
  disableSRAM();
  return _sramData.uint16Data;
}
uint16_t SRAM::writeUnsignedInt16(uint32_t address, uint16_t data) {
  _sramData.uint16Data = data;
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  SPI.transfer(_sramData.byteData[0]);
  SPI.transfer(_sramData.byteData[1]);
  disableSRAM();
}
void SRAM::readUnsignedInt16s(uint32_t address, uint16_t *data, uint32_t len) {
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.byteData[0] = SPI.transfer(0x00);
    _sramData.byteData[1] = SPI.transfer(0x00);
    data[i] = _sramData.uint16Data;
  }
  disableSRAM();
}
void SRAM::writeUnsignedInt16s(uint32_t address, uint16_t *data, uint32_t len) {
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.uint16Data = data[i];
    SPI.transfer(_sramData.byteData[0]);
    SPI.transfer(_sramData.byteData[1]);
  }
  disableSRAM();
}
uint32_t SRAM::readUnsignedInt32(uint32_t address) {
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  _sramData.byteData[0] = SPI.transfer(0x00);
  _sramData.byteData[1] = SPI.transfer(0x00);
  _sramData.byteData[2] = SPI.transfer(0x00);
  _sramData.byteData[3] = SPI.transfer(0x00);
  disableSRAM();
  return _sramData.uint32Data;
}
uint32_t SRAM::writeUnsignedInt32(uint32_t address, uint32_t data) {
  _sramData.uint32Data = data;
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  SPI.transfer(_sramData.byteData[0]);
  SPI.transfer(_sramData.byteData[1]);
  SPI.transfer(_sramData.byteData[2]);
  SPI.transfer(_sramData.byteData[3]);
  disableSRAM();
}
void SRAM::readUnsignedInt32s(uint32_t address, uint32_t *data, uint32_t len) {
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.byteData[0] = SPI.transfer(0x00);
    _sramData.byteData[1] = SPI.transfer(0x00);
    _sramData.byteData[2] = SPI.transfer(0x00);
    _sramData.byteData[3] = SPI.transfer(0x00);
    data[i] = _sramData.uint32Data;
  }
  disableSRAM();
}
void SRAM::writeUnsignedInt32s(uint32_t address, uint32_t *data, uint32_t len) {
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.uint32Data = data[i];
    SPI.transfer(_sramData.byteData[0]);
    SPI.transfer(_sramData.byteData[1]);
    SPI.transfer(_sramData.byteData[2]);
    SPI.transfer(_sramData.byteData[3]);
  }
  disableSRAM();
}

int SRAM::readInt(uint32_t address)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  _sramData.byteData[0] = SPI.transfer(0x00);
  _sramData.byteData[1] = SPI.transfer(0x00);
  disableSRAM();
  return _sramData.intData;

}

void SRAM::writeInt(uint32_t address, int data)
{
  _sramData.intData = data;
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  SPI.transfer(_sramData.byteData[0]);
  SPI.transfer(_sramData.byteData[1]);
  disableSRAM();
}

void SRAM::readInts(uint32_t address, int *data, uint32_t len)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.byteData[0] = SPI.transfer(0x00);
    _sramData.byteData[1] = SPI.transfer(0x00);
    data[i] = _sramData.intData;
  }
  disableSRAM();
}

void SRAM::writeInts(uint32_t address, int *data, uint32_t len)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.intData = data[i];
    SPI.transfer(_sramData.byteData[0]);
    SPI.transfer(_sramData.byteData[1]);
  }
  disableSRAM();
}

long SRAM::readLong(uint32_t address)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  _sramData.byteData[0] = SPI.transfer(0x00);
  _sramData.byteData[1] = SPI.transfer(0x00);
  _sramData.byteData[2] = SPI.transfer(0x00);
  _sramData.byteData[3] = SPI.transfer(0x00);
  disableSRAM();
  return _sramData.longData;
}

void SRAM::writeLong(uint32_t address, long data)
{
  _sramData.longData = data;
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  SPI.transfer(_sramData.byteData[0]);
  SPI.transfer(_sramData.byteData[1]);
  SPI.transfer(_sramData.byteData[2]);
  SPI.transfer(_sramData.byteData[3]);
  disableSRAM();
}

void SRAM::readLongs(uint32_t address, long *data, uint32_t len)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.byteData[0] = SPI.transfer(0x00);
    _sramData.byteData[1] = SPI.transfer(0x00);
    _sramData.byteData[2] = SPI.transfer(0x00);
    _sramData.byteData[3] = SPI.transfer(0x00);
    data[i] = _sramData.longData;
  }
  disableSRAM();
}

void SRAM::writeLongs(uint32_t address, long *data, uint32_t len)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.longData = data[i];
    SPI.transfer(_sramData.byteData[0]);
    SPI.transfer(_sramData.byteData[1]);
    SPI.transfer(_sramData.byteData[2]);
    SPI.transfer(_sramData.byteData[3]);
  }
  disableSRAM();
}

float SRAM::readFloat(uint32_t address)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  _sramData.byteData[0] = SPI.transfer(0x00);
  _sramData.byteData[1] = SPI.transfer(0x00);
  _sramData.byteData[2] = SPI.transfer(0x00);
  _sramData.byteData[3] = SPI.transfer(0x00);
  disableSRAM();
  return _sramData.floatData;
}

void SRAM::writeFloat(uint32_t address, float data)
{
  _sramData.floatData = data;
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  SPI.transfer(_sramData.byteData[0]);
  SPI.transfer(_sramData.byteData[1]);
  SPI.transfer(_sramData.byteData[2]);
  SPI.transfer(_sramData.byteData[3]);
  disableSRAM();
}

void SRAM::readFloats(uint32_t address, float *data, uint32_t len)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.byteData[0] = SPI.transfer(0x00);
    _sramData.byteData[1] = SPI.transfer(0x00);
    _sramData.byteData[2] = SPI.transfer(0x00);
    _sramData.byteData[3] = SPI.transfer(0x00);
    data[i] = _sramData.floatData;
  }
  disableSRAM();
}

void SRAM::writeFloats(uint32_t address, float *data, uint32_t len)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++) {
    _sramData.floatData = data[i];
    SPI.transfer(_sramData.byteData[0]);
    SPI.transfer(_sramData.byteData[1]);
    SPI.transfer(_sramData.byteData[2]);
    SPI.transfer(_sramData.byteData[3]);
  }
  disableSRAM();
}


void SRAM::readChars(uint32_t address, char *data, uint32_t len)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(READ);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++)
    data[i] = SPI.transfer(0x00);
  disableSRAM();
}

void SRAM::writeChars(uint32_t address, char *data, uint32_t len)
{
  setModeRegister(SEQUENTIAL_MODE);
  setMode(WRITE);
  setAddress(address);
  for (uint32_t i = 0; i < len; i++)
    SPI.transfer(data[i]);
  disableSRAM();
}

void SRAM::readPage(uint32_t address, char *data)
{
  setModeRegister(PAGE_MODE);
  setMode(READ);
  setAddress(address);
  for (uint8_t i = 0; i < 32; i++)
    data[i] = SPI.transfer(0x00);
  disableSRAM();
}

void SRAM::writePage(uint32_t address, char *data)
{
  setModeRegister(PAGE_MODE);
  setMode(WRITE);
  setAddress(address);
  for (uint8_t i = 0; i < 32; i++)
    SPI.transfer(data[i]);
  disableSRAM();
}


void SRAM::enableSRAM() {
  if (!_sramState) {
    _sramState = true;
    digitalWrite(_sramCS, LOW);
  }
}

void SRAM::disableSRAM() {
  if (_sramState) {
    _sramState = false;
    digitalWrite(_sramCS, HIGH);
  }
}

void SRAM::setAddress(uint32_t address) {
  if (_capacity > 512)
    SPI.transfer((uint8_t)(address >> 16) & 0xff);
  SPI.transfer((uint8_t)(address >> 8) & 0xff);
  SPI.transfer((uint8_t)address);
}

void SRAM::setMode(uint8_t mode) {
  SPI.transfer(mode);
}

void SRAM::setModeRegister(uint8_t modeData)
{
  enableSRAM();
  if (modeData != _modeData)
  {
    _modeData = modeData;
    SPI.transfer(WRMR);
    SPI.transfer(modeData);
    disableSRAM();
    enableSRAM();
  }
}
