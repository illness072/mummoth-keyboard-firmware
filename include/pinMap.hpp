#pragma once
#include <config.hpp>
#include <mcp23017.hpp>

class PinMap {
  uint8_t _pinMap[NUM_OF_ROW];

public:
  PinMap();
  void updatePinMap(MCP23017Matrix &matrix);
  void debugPrintPinMap(Serial_ *serial) const;
  bool pressed(size_t row, size_t col) const;
};
