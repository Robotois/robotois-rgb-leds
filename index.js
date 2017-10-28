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
  this.ledsStatus = {};

  process.on('SIGINT', () => {
    self.release();
  });

  process.on('SIGTERM', () => {
    self.release();
  });
}

RGBModule.prototype.publishNow = function publishNow() {
  this.mqttClient.publish(this.myTopic, this.prevMessage);
};

RGBModule.prototype.setMqttClient = function setMqttClient(mqttConfig) {
  this.mqttClient = mqttConfig.mqttClient;
  this.myTopic = `digitalOutputs/rgbModule${mqttConfig.instance}`;
};

RGBModule.prototype.write = function write(ledNumber, hexColor, value) {
  if (value === 1) {
    this.turnOn(ledNumber, hexColor);
  } else {
    this.turnOff(ledNumber);
  }
};

RGBModule.prototype.allWrite = function write(hexColor, value) {
  if (value === 1) {
    this.allOn(hexColor);
  } else {
    this.allOff();
  }
};

RGBModule.prototype.turnOnRGB = function turnOnRGB(_ledNumber, _red, _green, _blue) {
  this.rgb.turnOn(_ledNumber - 1, _red, _green, _blue);
};

RGBModule.prototype.mqttMessage = function mqttMessage(ledNumber, color, status) {
  this.ledsStatus = ledNumber !== -1
  ? {
    all: undefined,
    ...this.ledsStatus,
    [`led${ledNumber}`]: {
      status,
      color,
    },
  }
  : {
    all: {
      status,
      color,
    },
  };
  if (this.mqttClient) {
    this.mqttClient.publish(this.myTopic, JSON.stringify(this.ledsStatus));
  }
};

RGBModule.prototype.turnOn = function turnOn(ledNumber, hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.turnOn(ledNumber - 1, rgbColor[0], rgbColor[1], rgbColor[2]);
  this.mqttMessage(ledNumber, hexColor, 'on');
};

RGBModule.prototype.turnOff = function turnOff(ledNumber) {
  this.rgb.turnOff(ledNumber - 1);
  this.mqttMessage(ledNumber, undefined, 'off');
};

RGBModule.prototype.blink = function blink(ledNumber, hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.blink(ledNumber - 1, rgbColor[0], rgbColor[1], rgbColor[2]);
  this.mqttMessage(ledNumber, hexColor, 'blink');
};

RGBModule.prototype.blinkRGB = function blinkRGB(ledNumber, red, green, blue) {
  this.rgb.blink(ledNumber - 1, red, green, blue);
};

RGBModule.prototype.allOn = function allOn(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.allOn(rgbColor[0], rgbColor[1], rgbColor[2]);
  this.mqttMessage(-1, hexColor, 'on');
};

RGBModule.prototype.allOnRGB = function allOnRGB(red, green, blue) {
  this.rgb.allOn(red, green, blue);
};

RGBModule.prototype.allOff = function allOff() {
  this.rgb.allOff();
  this.mqttMessage(-1, undefined, 'off');
};

RGBModule.prototype.allBlink = function allBlink(hexColor) {
  const rgbColor = hexToRGB(hexColor);
  this.rgb.allBlink(rgbColor[0], rgbColor[1], rgbColor[2]);
  this.mqttMessage(-1, hexColor, 'blink');
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
