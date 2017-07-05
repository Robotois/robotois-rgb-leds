const RGB = require('../index');

const rgb = new RGB();

rgb.allBlinkHex(`#${Math.floor(Math.random() * 16777215).toString(16)}`);

setTimeout(() => {
  rgb.allOff();
}, 5000);

setTimeout(() => {
  rgb.release();
}, 8000);

process.on('SIGINT', () => {
  process.exit();
});

process.on('SIGTERM', () => {
  process.exit();
});
