#include <cstdio>
#include <bcm2835.h>
#include <thread>
#include <chrono>

#include "./RGBModule.h"

void i2c_init();
void i2c_end();

int main(int argc, char const *argv[]) {
//    i2c_init();
    RGBModule *rgbModule = new RGBModule();
    rgbModule->allBlink(86,15,126);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    rgbModule->allOff();
    // while(true){
    //     rgbModule->rainbow();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //     rgbModule->allOn(64,224,208);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    //     rgbModule->allOn(128,0,128);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    //     rgbModule->allOff();
    //     rgbModule->turnOn(0,128,0,0);
    //     rgbModule->turnOn(1,0,128,0);
    //     rgbModule->turnOn(2,0,0,128);
    //     rgbModule->turnOn(3,128,0,0);
    //     rgbModule->turnOn(4,0,128,0);
    //     rgbModule->turnOn(5,0,0,128);
    //     rgbModule->turnOn(6,128,0,0);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    //     rgbModule->allBlink(64,224,208);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    //     rgbModule->allOff();
    //     rgbModule->blink(0,128,0,0);
    //     rgbModule->blink(1,0,128,0);
    //     rgbModule->blink(2,0,0,128);
    //     rgbModule->blink(3,128,0,0);
    //     rgbModule->blink(4,0,128,0);
    //     rgbModule->blink(5,0,0,128);
    //     rgbModule->blink(6,0,0,128);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    // }

    i2c_end();
    return 0;
}

void i2c_init() {
  uint16_t clkDiv = BCM2835_I2C_CLOCK_DIVIDER_626;

  if(!bcm2835_init()){
    printf("BCM2835 Error!!!\n");
  }

  bcm2835_i2c_begin();

  bcm2835_i2c_setClockDivider(clkDiv);
}

void i2c_end() {
  bcm2835_i2c_end();
  bcm2835_close();
}
