#include "Arduino.h"
#include "ColorRGB.h"

ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b) {
  _r = r;
  _g = g;
  _b = b;
}

uint8_t ColorRGB::getR() {
  return _r;
}

uint8_t ColorRGB::getG() {
  return _g;
}

uint8_t ColorRGB::getB() {
  return _b;
}
