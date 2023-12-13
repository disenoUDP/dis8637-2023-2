#include <Adafruit_NeoPixel.h>

// el pin
#define PIN 6  // On Trinket or Gemma, suggest changing this to 1

// cuantos pixeles son
#define NUMPIXELS 30  // Popular NeoPixel ring size

#define DELAYVAL 50  // Time (in milliseconds) to pause between pixels

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
