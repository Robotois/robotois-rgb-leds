/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RGBModule.h
 * Author: yovany
 *
 * Created on July 4, 2017, 9:00 PM
 */

#ifndef RGBMODULE_H
#define RGBMODULE_H

#include <cstdint>

#define RGB_ADDRESS 0x12
#define RGB_ALLON 0x00
#define RGB_ALLOFF 0x01
#define RGB_TURNON 0x02
#define RGB_TURNOFF 0x03
#define RGB_ALLBLINK 0x04
#define RGB_BLINK 0x05
#define RGB_RAINBOW 0x06

class RGBModule {
public:
    RGBModule(uint8_t _add = 0x00);
    RGBModule(const RGBModule& orig);
    virtual ~RGBModule();
    
    void allOn(uint8_t red, uint8_t green, uint8_t blue);
    void allOff();
    void allBlink(uint8_t red, uint8_t green, uint8_t blue);
    
    void rainbow();

    void turnOn(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue);
    void turnOff(uint8_t ledNumber);
    void blink(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue);
    
    void i2cWrite(uint8_t byteCount);
    
    void release();
private:
    uint8_t slave_addr;
    char rBuf[10]; // - Max length
    char wBuf[10]; // - Max length
    
    void pause();
    void selectModule();
    void bcm_init();
    void bcm_end();

};

#endif /* RGBMODULE_H */

