const LEDRGBModule = require('bindings')('RGBModule');

/**
 * Converts a hx valuer to RGB value.
 * @param {int} hx The second argument.
 * @returns {Array} RBG Array string.
 */
const hexToRGB = function hexToRGB(hx) {
  const hex = hx.replace('#', '');
  return [
    parseInt(hex.substring(0, 2), 16),
    parseInt(hex.substring(2, 4), 16),
    parseInt(hex.substring(4, 6), 16),
  ];
};
/**
 * Creates an instance of RGBModule.
 * @param {int} portNumber The port number where is connected to the shield.
 * @returns {RGBModule} RGBModule object.
 */
function RGBModule(portNumber) {
  const self = this;

  this.rgb = new LEDRGBModule(portNumber);
  this.all_status = false; // Initially off
  this.ledsOn = {
    1: false,
    2: false,
    3: false,
    4: false,
  };

  process.on('SIGINT', () => {
    self.release();
  });

  process.on('SIGTERM', () => {
    self.release();
  });
}

// - Implementar la funcion turnOn => ["Nombre del led", "color en hexa"]
RGBModule.prototype.turnOnRGB = function turnOnRGB(_ledNumber, _red, _green, _blue) {
  this.rgb.turnOn(_ledNumber - 1, _red, _green, _blue);
};

RGBModule.prototype.turnOn = function turnOn(ledNumber, hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.turnOn(ledNumber - 1, rgbColor[0], rgbColor[1], rgbColor[2]);
};

RGBModule.prototype.turnOff = function turnOff(ledNumber) {
  this.rgb.turnOff(ledNumber - 1);
};

RGBModule.prototype.blink = function blink(ledNumber, hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.blink(ledNumber - 1, rgbColor[0], rgbColor[1], rgbColor[2]);
};

RGBModule.prototype.blinkRGB = function blinkRGB(ledNumber, red, green, blue) {
  this.rgb.blink(ledNumber - 1, red, green, blue);
};

RGBModule.prototype.allOn = function allOn(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.allOn(rgbColor[0], rgbColor[1], rgbColor[2]);
};

RGBModule.prototype.allOnRGB = function allOnRGB(red, green, blue) {
  this.rgb.allOn(red, green, blue);
};

RGBModule.prototype.allOff = function allOff() {
  this.rgb.allOff();
};

RGBModule.prototype.allBlink = function allBlink(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  console.log(rgbColor);
  this.rgb.allBlink(rgbColor[0], rgbColor[1], rgbColor[2]);
};

RGBModule.prototype.allBlinkRGB = function allBlinkRGB(red, green, blue) {
  this.rgb.allBlink(red, green, blue);
};

RGBModule.prototype.rainbow = function rainbow() {
  this.rgb.rainbow();
};

RGBModule.prototype.release = function release() {
  this.rgb.release();
};

module.exports = RGBModule;
