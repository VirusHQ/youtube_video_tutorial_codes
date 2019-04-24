#include "FastLED.h"

#define NUM_LEDS 16
#define DATA_PIN 13

#define r 4
#define g 0
#define b 2
#define bri 15

int r_value, g_value, b_value, bri_value;

CRGB leds[NUM_LEDS];

int fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
}

void loop() {
  r_value = analogRead(r);
  r_value = fmap(r_value, 0, 4095, 0, 255);
  g_value = analogRead(g);
  g_value = fmap(g_value, 0, 4095, 0, 255);
  b_value = analogRead(b);
  b_value = fmap(b_value, 0, 4095, 0, 255);
  bri_value = analogRead(bri);
  bri_value = fmap(bri_value, 0, 4095, 0, 100);
  
  Serial.print(r_value);
  Serial.print(',');
  Serial.print(g_value);
  Serial.print(',');
  Serial.print(b_value);
  Serial.print(',');
  Serial.println(bri_value);
  FastLED.setBrightness(bri_value);
  leds[0] = CRGB(r_value, g_value, b_value);
  leds[1] = CRGB(r_value, g_value, b_value);
  leds[2] = CRGB(r_value, g_value, b_value);
  leds[3] = CRGB(r_value, g_value, b_value);
  leds[4] = CRGB(r_value, g_value, b_value);
  leds[5] = CRGB(r_value, g_value, b_value);
  leds[6] = CRGB(r_value, g_value, b_value);
  leds[7] = CRGB(r_value, g_value, b_value);
  leds[8] = CRGB(r_value, g_value, b_value);
  leds[9] = CRGB(r_value, g_value, b_value);
  leds[10] = CRGB(r_value, g_value, b_value);
  leds[11] = CRGB(r_value, g_value, b_value);
  leds[12] = CRGB(r_value, g_value, b_value);
  leds[13] = CRGB(r_value, g_value, b_value);
  leds[14] = CRGB(r_value, g_value, b_value);
  leds[15] = CRGB(r_value, g_value, b_value);
  FastLED.show();
}
