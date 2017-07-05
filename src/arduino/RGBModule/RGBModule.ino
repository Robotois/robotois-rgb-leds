#include "RGBRing.h"
#include "Wire.h"

#define SLAVE_ADDRESS 0x12
#define A0_PIN 3
#define REG_MAP_SIZE 0x20
#define MAX_BYTES 10 // Max of  bytes

// #define SERIAL_LOG
// #ifdef SERIAL_LOG
// String serialLog;
// #endif

uint8_t receivedBytes[MAX_BYTES];

RGBRing rgbRing;
unsigned long prevMillis;
uint16_t currentMillis;

ISR(TIMER1_CAPT_vect){
  currentMillis = millis() - prevMillis;
  // #ifdef SERIAL_LOG
  //   serialLog = "Interrupt: " + String(currentMillis);
  //   Serial.println(serialLog);
  // #endif

  if(currentMillis >= 500){
    rgbRing.blinking();
    prevMillis = millis();
  }
}

void setup() {
  // #ifdef SERIAL_LOG
  //   Serial.begin(115200);
  //   Serial.println("Motor Module logs:");
  // #endif

  rgbRing.begin();
  prevMillis = millis();
  // Using pin A0_PIN you can connect up to two RGB modules, the default value for
  // A0_PIN is LOW, if the jumper is placed in the two pin connector then the value
  // for A0_PIN is HIGH, this means that the address for the current module will be
  // 0x13
  // Wire.setClock(400000);
  Wire.begin( SLAVE_ADDRESS | digitalRead(A0_PIN) );

  Wire.onReceive(receiveHandler);
}

void loop() {

}

/**
 * Get the byte sequence received from the master, in which the first byte corresponds
 * to the function/register address, and the following bytes are the data or params
 * to be written.
 * For the RGB module we are considering the data is received in Burst Write Operation mode:
 * [initialRegisterAddress] -> [Data0] -> [Data1] -> [Data2] ... -> [DataX]
 * @param byteCount
 */
void receiveHandler(int byteCount) {

  // #ifdef SERIAL_LOG
  //   serialLog = "I2C["+String(byteCount)+"]: ";
  // #endif

  for (uint8_t i = 0; i < byteCount; i++) {
    if ( i < MAX_BYTES ) {
      receivedBytes[i] = Wire.read();

      // #ifdef SERIAL_LOG
      //   serialLog += String(receivedBytes[i],HEX) + " => ";
      // #endif

    } else { // throw away the excess bytes
      Wire.read();
    }
  }

  // #ifdef SERIAL_LOG
  //   Serial.println(serialLog);
  // #endif

  // Function mapping
  uint8_t regAdd = receivedBytes[0];
  switch (regAdd) {
    case 0x00: // [red]->[green]->[blue]
      rgbRing.allOn(receivedBytes[1], receivedBytes[2], receivedBytes[3]);
      break;
    case 0x01:
      rgbRing.allOff();
      break;
    case 0x02: // [ledNumber]->[red]->[green]->[blue]
      rgbRing.turnOn(receivedBytes[1], receivedBytes[2], receivedBytes[3], receivedBytes[4]);
      break;
    case 0x03: // [ledNumber]
      rgbRing.turnOff(receivedBytes[1]);
      break;
    case 0x04: // [red]->[green]->[blue]
      rgbRing.allBlink(receivedBytes[1], receivedBytes[2], receivedBytes[3]);
      break;
    case 0x05: // [ledNumber]->[red]->[green]->[blue]
      rgbRing.blink(receivedBytes[1], receivedBytes[2], receivedBytes[3], receivedBytes[4]);
      break;
    case 0x06:
      rgbRing.rainbow();
      break;
  }
}
