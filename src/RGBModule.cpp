/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RGBModule.cpp
 * Author: yovany
 * 
 * Created on July 4, 2017, 9:00 PM
 */

#include "RGBModule.h"

#include <bcm2835.h>
#include <iostream>
#include <thread>
#include <chrono>

RGBModule::RGBModule(uint8_t add) {
    slave_addr = RGB_ADDRESS | add;
    bcm_init();
    allOff();
}

RGBModule::RGBModule(const RGBModule& orig) {
}

RGBModule::~RGBModule() {
}

void RGBModule::allOn(uint8_t red, uint8_t green, uint8_t blue){
    selectModule();
    wBuf[0] = RGB_ALLON;
    wBuf[1] = red;
    wBuf[2] = green;
    wBuf[3] = blue;
    i2cWrite(4);
}

void RGBModule::allOff(){
    selectModule();
    wBuf[0] = RGB_ALLOFF;
    i2cWrite(1);
}

void RGBModule::allBlink(uint8_t red, uint8_t green, uint8_t blue){
    selectModule();
    wBuf[0] = RGB_ALLBLINK;
    wBuf[1] = red;
    wBuf[2] = green;
    wBuf[3] = blue;
    i2cWrite(4);
}

void RGBModule::rainbow(){
    selectModule();
    wBuf[0] = RGB_RAINBOW;
    i2cWrite(1);
}

void RGBModule::turnOn(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue){
    selectModule();
    wBuf[0] = RGB_TURNON;
    wBuf[1] = ledNumber;
    wBuf[2] = red;
    wBuf[3] = green;
    wBuf[4] = blue;
    i2cWrite(5);
}

void RGBModule::turnOff(uint8_t ledNumber){
    selectModule();
    wBuf[0] = RGB_TURNOFF;
    wBuf[1] = ledNumber;
    i2cWrite(2);
}

void RGBModule::blink(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue){
    selectModule();
    wBuf[0] = RGB_BLINK;
    wBuf[1] = ledNumber;
    wBuf[2] = red;
    wBuf[3] = green;
    wBuf[4] = blue;
    i2cWrite(5);
}

void RGBModule::i2cWrite(uint8_t byteCount){
    bcm2835_i2c_write(wBuf, byteCount);
    pause();
}

void RGBModule::pause(){
    std::this_thread::sleep_for(std::chrono::microseconds(200));
}

void RGBModule::selectModule(){
    bcm2835_i2c_setSlaveAddress(slave_addr);
}

void RGBModule::bcm_init(){
    uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_626;

    if (!bcm2835_init()){
        printf("BCM2835 Error!!...\n");
        exit(1);
    }

    bcm2835_i2c_begin();

    bcm2835_i2c_setClockDivider(clk_div);
}

void RGBModule::bcm_end(){
    bcm2835_i2c_end();
    bcm2835_close();
}

void RGBModule::release(){
    allOff();
    printf("[RGBModule] => Released\n");
}
