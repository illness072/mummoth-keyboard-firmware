#include <Arduino.h>
#include <Keyboard.h>
#include <keymap.hpp>
#include <mcp23017.hpp>
#include <pinMap.hpp>

MCP23017Matrix leftMatrix(0x26);  // VVG
MCP23017Matrix rightMatrix(0x24); // VGG
PinMap leftPinMap;
PinMap rightPinMap;

uint32_t leftPrevMap[NUM_OF_ROW][NUM_OF_COLUMN];
uint32_t rightPrevMap[NUM_OF_ROW][NUM_OF_COLUMN];

void setup() {
  Serial.begin(9600); // This pipes to the serial monitor
  while (!leftMatrix.begin()) {
    Serial.print(" Left Error. MCP23017 not detected: 0x");
    Serial.println(leftMatrix.i2cAddress(), HEX);
    delay(1000);
  }
  while (!rightMatrix.begin()) {
    Serial.println(" Right Error. MCP23017 not detected: 0x");
    Serial.println(rightMatrix.i2cAddress(), HEX);
    delay(1000);
  }
  for (size_t r = 0; r < NUM_OF_ROW; r++) {
    for (size_t c = 0; c < NUM_OF_COLUMN; c++) {
      leftPrevMap[r][c] = 0;
      rightPrevMap[r][c] = 0;
    }
  }
  Keyboard.begin();
}

struct event {
  size_t row;
  size_t col;
  bool pressed;
  uint32_t keep;
};
event eventlist[64];
size_t evCount;
uint8_t currentLayer = _QWERTY;

void getEventList(const PinMap &pinMap,
                  uint32_t prevMap[NUM_OF_ROW][NUM_OF_COLUMN], size_t rOffset) {
  for (size_t r = 0; r < NUM_OF_ROW; r++) {
    for (size_t c = 0; c < NUM_OF_COLUMN; c++) {
      auto pressed = pinMap.pressed(r, c);
      auto prev_pressed = prevMap[r][c] > 0;
      if (pressed ||
          prev_pressed) { // pressed, pressing, released. (not releasing)
        eventlist[evCount] = {r + rOffset, c, pressed, prevMap[r][c]};
        evCount++;
      }
      if (pressed) {
        prevMap[r][c] = prevMap[r][c] + 1;
      } else {
        prevMap[r][c] = 0;
      }
    }
  }
}

void debug_kc(event &e, bool pressed) {
  Serial.print(currentLayer);
  Serial.print(":");
  Serial.print(e.row);
  Serial.print(",");
  Serial.print(e.col);
  Serial.print(",");
  Serial.print(e.keep);
  Serial.print("...");
  if (pressed)
    Serial.print("+");
  else
    Serial.print("-");
  Serial.println();
}

void loop() {
  leftPinMap.updatePinMap(leftMatrix);
  // leftPinMap.debugPrintPinMap(&Serial);
  // Serial.print("--");
  rightPinMap.updatePinMap(rightMatrix);
  // rightPinMap.debugPrintPinMap(&Serial);
  // Serial.println("");
  evCount = 0;
  getEventList(leftPinMap, leftPrevMap, 0);
  getEventList(rightPinMap, rightPrevMap, NUM_OF_ROW);

  for (size_t i = 0; i < evCount; i++) {
    auto e = eventlist[i];
    auto kc = keyMaps[currentLayer][e.row][e.col];
    auto layer = ((kc >> 8) & 0xF);
    if (e.pressed) {
      if (e.keep == HOLD_THRESHOLD) {
        if (layer != _QWERTY) {
          currentLayer = layer;
        } else {
          Keyboard.press(kc);
        }
        debug_kc(e, true);
      }
    } else { // released
      if (e.keep <= HOLD_THRESHOLD) {
        Keyboard.press(kc);
        debug_kc(e, true);
      } else if (layer != _QWERTY) {
        currentLayer = _QWERTY;
        Keyboard.releaseAll();
      }
      Keyboard.release(kc);
      debug_kc(e, false);
    }
  }
}
