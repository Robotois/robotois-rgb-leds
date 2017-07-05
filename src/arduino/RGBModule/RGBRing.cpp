#include "RGBRing.h"

RGBRing::RGBRing(){
  // Parameter 1 = number of pixels in strip
  // Parameter 2 = Arduino pin number (most are valid)
  // Parameter 3 = pixel type flags, add together as needed:
  //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
  //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
  //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
  //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
  //   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
  ring = Adafruit_NeoPixel(ledCount, PIN, NEO_GRB + NEO_KHZ800);
}

RGBRing::~RGBRing(){

}

void RGBRing::begin(){
  ring.begin();
  ring.setBrightness(200);
  allOff();
  timerInit();

  jIter = 0;
  maxIter = 256*5;
}

void RGBRing::timerInit(){
  // [COM1A1/COM1B1: 0, COM1A0/COM1B0: 0]
  // Normal port operation, OC1A/OC1B disconnected.
  // [WGM11: 0, WGM10: 0]
  // Operation Mode: CTC, Top: ICR1
  TCCR1A = 0x00;
	// [WGM13: 1, WGM12: 1]
  // Operation Mode: CTC, Top: ICR1
  // [CS12: 0, CS11: 1, CS10: 1]
  // Clk/64 prescaler => 250,000 Hz
	TCCR1B = 0x1B;
	TCCR1C = 0x00;
  // Max for counter comparison interrupt, the interruption period is for 50ms
  TCNT1 = 0;
  ICR1 = 6250;
  //  ICIE: Input Capture Interrupt Enable
  TIMSK1 = 0x20;
  interrupts();
}

void RGBRing::allOn(uint8_t red, uint8_t green, uint8_t blue) {
  allOn(ring.Color(red, green, blue));
}

void RGBRing::allOn(uint32_t color) {
  allBlinkEnable = false;
  for(uint8_t i=0; i < ledCount; i++) {
    ring.setPixelColor(i, color);
    ledStatus[i] = true;
    ledBlinkEnable[i] = false;
  }
  ring.show();
  allStatus = true;
  rainbowEnable = false;
}

void RGBRing::allOff() {
  allBlinkEnable = false;
  for(uint8_t i=0; i < ledCount; i++) {
    ring.setPixelColor(i, 0);
    ledStatus[i] = false;
    ledBlinkEnable[i] = false;
  }
  ring.show();
  allStatus = false;
  rainbowEnable = false;
}

void RGBRing::turnOn(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue){
  ring.setPixelColor(ledNumber, ring.Color(red, green, blue));
  ring.show();
  ledStatus[ledNumber] = true;
  ledBlinkEnable[ledNumber] = false;
}

void RGBRing::turnOn(uint8_t ledNumber, uint32_t color){
  ring.setPixelColor(ledNumber, color);
  ring.show();
  ledStatus[ledNumber] = true;
  ledBlinkEnable[ledNumber] = false;
}

void RGBRing::turnOff(uint8_t ledNumber){
  ring.setPixelColor(ledNumber, 0);
  ring.show();
  ledStatus[ledNumber] = false;
  ledBlinkEnable[ledNumber] = false;
}

void RGBRing::blink(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue){
  if(!ledBlinkEnable[ledNumber]) { // If led is not blinking already
    turnOff(ledNumber);
    ledBlinkEnable[ledNumber] = true;
  }
  ledColor[ledNumber] = ring.Color(red, green, blue);
}

void RGBRing::ledToggle(uint8_t ledNumber){
  if(!ledStatus[ledNumber]){
    ring.setPixelColor(ledNumber, ledColor[ledNumber]);
    ledStatus[ledNumber] = true;
  } else {
    ring.setPixelColor(ledNumber, 0);
    ledStatus[ledNumber] = false;
  }
}

void RGBRing::allBlink(uint8_t red, uint8_t green, uint8_t blue){
  if(!allBlinkEnable){
    allOff();
    allBlinkEnable = true;
  }
  allColor = ring.Color(red, green, blue);
}

void RGBRing::allToggle(){
  if(!allStatus){
    for(uint8_t i=0; i < ledCount; i++) {
      ring.setPixelColor(i, allColor);
    }
    allStatus = true;
  } else {
    for(uint8_t i=0; i < ledCount; i++) {
      ring.setPixelColor(i, 0);
    }
    allStatus = false;
  }
  ring.show();
}

void RGBRing::blinking(){
  if(allBlinkEnable){
    allToggle();
    return;
  }

  if(rainbowEnable){
    rainbow();
    return;
  }

  bool haveBlink = false;
  for (uint8_t i = 0; i < ledCount; i++) {
    if(ledBlinkEnable[i]){
      ledToggle(i);
      haveBlink = true;
    }
  }

  if(haveBlink){
    ring.show();
  }
}

void RGBRing::rainbow(){
  if(!rainbowEnable){
    allOff();
    rainbowEnable = true;
    jIter = 0;
    return;
  }

  if(jIter < maxIter){
    for(uint8_t i=0; i < ledCount; i++) {
      ring.setPixelColor(i, wheel(((i * 256 / ledCount) + jIter) & 255));
    }
    ring.show();
    jIter += 5;
  }else{
    jIter = 0;
  }
}

uint32_t RGBRing::wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return ring.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return ring.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return ring.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
