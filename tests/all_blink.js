const RGB = require('../index');

const rgb = new RGB();

rgb.allBlink(`#${Math.floor(Math.random() * 16777215).toString(16)}`);

setTimeout(() => {
  rgb.allBlinkOff(1);
}, 5000);

setTimeout(() => {
  rgb.release();
}, 8000);
