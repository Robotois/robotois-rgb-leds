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

  process.on('SIGINT', () => {
    self.rgb.release();
  });

  process.on('SIGTERM', () => {
    self.rgb.release();
  });
}

// - Implementar la funcion turnOn => ["Nombre del led", "color en hexa"]
RGBModule.prototype.setRGB = function setRGB(_ledNumber, _red, _green, _blue) {
  this.rgb.setRGB(_ledNumber, _red, _green, _blue);
};

RGBModule.prototype.blinkRGB = function blinkRGB(_ledNumber, _red, _green, _blue) {
  this.rgb.setRGB(_ledNumber, _red, _green, _blue);
  setTimeout(() => {
    this.rgb.ledOff(_ledNumber);
  }, 1000);
};

RGBModule.prototype.turnOff = function turnOff(ledNumber) {
  this.rgb.ledOff(ledNumber);
};

RGBModule.prototype.turnOn = function turnOn(ledNumber, hexColor) {
  const rgbColor = hexToRGB(hexColor);
  const led = ledNumber.replace('led', '') * 1;
  this.rgb.setRGB(led, rgbColor[0], rgbColor[1], rgbColor[2]);
};

RGBModule.prototype.allOn = function allOn(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.allOn(rgbColor[0], rgbColor[1], rgbColor[2]);
  this.all_status = true;
};

RGBModule.prototype.allToggle = function allToggle(hexColor) {
  if (!this.all_status) {
    const rgbColor = hexToRGB(hexColor);
    this.rgb.allOn(rgbColor[0], rgbColor[1], rgbColor[2]);
    this.all_status = true;
  } else {
    this.allOff();
  }
};

RGBModule.prototype.blink = function blink(ledNumber, hexColor) {
  const rgbColor = hexToRGB(hexColor);
  const led = ledNumber.replace('led', '') * 1;
  this.rgb.blinkRGB(led, rgbColor[0], rgbColor[1], rgbColor[2]);
};

RGBModule.prototype.allOff = function allOff() {
  this.rgb.allOff();
  this.all_status = false;
};

RGBModule.prototype.release = function release() {
  this.rgb.release();
};

module.exports = RGBModule;
