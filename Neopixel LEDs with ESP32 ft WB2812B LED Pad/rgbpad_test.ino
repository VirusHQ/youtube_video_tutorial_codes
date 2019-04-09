#include "FastLED.h"

#define NUM_LEDS 16
#define DATA_PIN 13

int i, j, k;
CRGB leds[NUM_LEDS];

void setup() {
  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
}

void loop() {
  for (i = 0 ; i < 256 ; i = i + 51) {
    for (j = 0 ; j < 256 ; j = j + 51) {
      for (k = 0 ; k < 256 ; k = k + 51) {
        leds[0] = CRGB(i, j, k);
        leds[1] = CRGB(i, j, k);
        leds[2] = CRGB(i, j, k);
        leds[3] = CRGB(i, j, k);
        leds[4] = CRGB(i, j, k);
        leds[5] = CRGB(i, j, k);
        leds[6] = CRGB(i, j, k);
        leds[7] = CRGB(i, j, k);
        leds[8] = CRGB(i, j, k);
        leds[9] = CRGB(i, j, k);
        leds[10] = CRGB(i, j, k);
        leds[11] = CRGB(i, j, k);
        leds[12] = CRGB(i, j, k);
        leds[13] = CRGB(i, j, k);
        leds[14] = CRGB(i, j, k);
        leds[15] = CRGB(i, j, k);
        FastLED.show();
        delay(1000);
      }
    }
  }
}
