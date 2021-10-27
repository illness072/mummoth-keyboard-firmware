#include <pinMap.hpp>

PinMap::PinMap() {
  for (size_t r = 0; r < NUM_OF_ROW; r++) {
    _pinMap[r] = 0x00;
  }
}

void PinMap::updatePinMap(MCP23017Matrix &matrix) {
  for (size_t r = 0; r < NUM_OF_ROW; r++) {
    matrix.writeRow(r, LOW); // active LOW
    _pinMap[r] = matrix.readCols();
    matrix.writeRow(r, HIGH);
  }
}

void PinMap::debugPrintPinMap(Serial_ *serial) const {
  for (size_t r = 0; r < NUM_OF_ROW; r++) {
    serial->print(_pinMap[r], BIN);
    serial->print("-");
  }
}

bool PinMap::pressed(size_t row, size_t col) const {
  return ((_pinMap[row] >> col) & 1) == LOW; // active low
}
