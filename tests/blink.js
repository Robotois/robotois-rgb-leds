const RGB = require('../index');

const rgb = new RGB();

rgb.blink(1, `#${Math.floor(Math.random() * 16777215).toString(16)}`);

setTimeout(() => {
  rgb.blinkOff(1);
}, 5000);

setTimeout(() => {
  rgb.release();
}, 8000);
