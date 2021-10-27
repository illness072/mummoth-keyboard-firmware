#include <mcp23017.hpp>

MCP23017Matrix::MCP23017Matrix(uint8_t i2c_address)
    : _i2c_address(i2c_address) {}

inline int MCP23017Matrix::colPin(size_t n) { return n; }
inline int MCP23017Matrix::rowPin(size_t n) { return n + 8; }

bool MCP23017Matrix::begin() {
  if (!_mcp.begin_I2C(_i2c_address)) {
    return false;
  }
  for (int i = 0; i < 8; i++) {
    _mcp.pinMode(colPin(i), INPUT_PULLUP); // Port A(C) as input, pullup
    _mcp.pinMode(rowPin(i), OUTPUT);       // Port B(R) as output
    _mcp.digitalWrite(rowPin(i), HIGH);    // active LOW
  }
  return true;
}

void MCP23017Matrix::writeRow(size_t r, uint8_t value) {
  _mcp.digitalWrite(rowPin(r), value);
}

uint8_t MCP23017Matrix::readCols() { return _mcp.readGPIOA(); }
