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
  this.interval = {};
  this.allInterval = null;

  process.on('SIGINT', () => {
    self.release();
  });

  process.on('SIGTERM', () => {
    self.release();
  });
}

// - Implementar la funcion turnOn => ["Nombre del led", "color en hexa"]
RGBModule.prototype.setRGB = function setRGB(_ledNumber, _red, _green, _blue) {
  this.rgb.setRGB(_ledNumber, _red, _green, _blue);
};

RGBModule.prototype.turnOn = function turnOn(ledNumber, hexColor) {
  const rgbColor = hexToRGB(hexColor);
  // console.log("LED Number: " + ledNumber);
  this.rgb.setRGB(ledNumber, rgbColor[0], rgbColor[1], rgbColor[2]);
  this.ledsOn[ledNumber] = true;
};

RGBModule.prototype.turnOff = function turnOff(ledNumber) {
  this.rgb.ledOff(ledNumber);
  this.ledsOn[ledNumber] = false;
};

RGBModule.prototype.toggle = function toggle(ledNumber, hexColor) {
  if (this.ledsOn[ledNumber]) {
    this.turnOff(ledNumber);
  } else {
    this.turnOn(ledNumber, hexColor);
  }
};

RGBModule.prototype.blink = function blink(ledNumber, hexColor) {
  if (!this.interval[ledNumber]) {
    this.interval[ledNumber] = setInterval(() => {
      this.toggle(ledNumber, hexColor);
    }, 400); // cambiar estado cada 400ms
  }
};

RGBModule.prototype.blinkOff = function blinkOff(ledNumber) {
  if (this.interval != null) {
    clearInterval(this.interval[ledNumber]);
    this.interval[ledNumber] = null;
  }
  this.turnOff(ledNumber);
};

RGBModule.prototype.allOn = function allOn(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.allOn(rgbColor[0], rgbColor[1], rgbColor[2]);
  this.all_status = true;
};

RGBModule.prototype.allOff = function allOff() {
  this.rgb.allOff();
  this.all_status = false;
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

RGBModule.prototype.allBlink = function allBlink(hexColor) {
  if (!this.allInterval) {
    this.allInterval = setInterval(() => {
      this.allToggle(hexColor);
    }, 500);
  }
};

RGBModule.prototype.allBlinkOff = function allBlinkOff() {
  if (this.allInterval != null) {
    clearInterval(this.allInterval);
    this.allInterval = null;
  }
  this.allOff();
};


RGBModule.prototype.release = function release() {
  this.rgb.release();
  [1, 2, 3, 4].forEach(i => clearInterval(this.interval[i]));
  clearInterval(this.allInterval);
};

module.exports = RGBModule;
