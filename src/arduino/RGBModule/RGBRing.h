#ifndef RGBRING_H
#define RGBRING_H

#include <Adafruit_NeoPixel.h>

#define PIN 6
#define ledCount 7

class RGBRing {
private:
  /* data */
  Adafruit_NeoPixel ring;

  uint16_t jIter, maxIter;
  uint16_t rainbowIter;
  bool rainbowEnable;

  uint32_t allColor;
  bool allBlinkEnable;
  bool allStatus;

  uint32_t ledColor[7];
  bool ledBlinkEnable[7];
  bool ledStatus[7];

  void timerInit();
  uint32_t wheel(byte WheelPos);
  void ledToggle(uint8_t ledNumber);
  void allToggle();
public:
  RGBRing ();
  virtual ~RGBRing ();

  void begin();

  void allOn(uint8_t red, uint8_t green, uint8_t blue);
  void allOn(uint32_t color);
  void allOff();

  void turnOn(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue);
  void turnOn(uint8_t ledNumber, uint32_t color);
  void turnOff(uint8_t ledNumber);

  void blink(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue);
  void allBlink(uint8_t red, uint8_t green, uint8_t blue);
  void blinkDisable(int ledNumber);

  void enableRainbow();
  void rainbow();

  void blinking();
};
#endif
