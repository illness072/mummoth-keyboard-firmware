#pragma once
#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

class MCP23017Matrix {
  const uint8_t _i2c_address;
  Adafruit_MCP23X17 _mcp;

  // portA (pin 0..7): Column (input, pullup)
  inline static int colPin(size_t n);
  // portB (pin 8..15): Row (output)
  inline static int rowPin(size_t n);

public:
  MCP23017Matrix(uint8_t i2c_address);
  bool begin();
  void writeRow(size_t r, uint8_t value);
  uint8_t readCols();
  uint8_t i2cAddress() { return _i2c_address; }
};
