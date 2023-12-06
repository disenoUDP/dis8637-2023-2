#ifndef ColorRGB_H
#define ColorRGB_H

#include "Arduino.h"

class ColorRGB {
public:
  ColorRGB(uint8_t r, uint8_t g, uint8_t b);
  uint8_t getR();
  uint8_t getG();
  uint8_t getB();
private:
  uint8_t _r;
  uint8_t _g;
  uint8_t _b;
};

#endif
