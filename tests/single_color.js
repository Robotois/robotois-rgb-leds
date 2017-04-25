const RGB = require('../index');

const rgb = new RGB();

// rgb.setRGB(1, 204, 51, 153);
rgb.turnOn(1, '#cc3399');

setTimeout(() => {
  rgb.release();
}, 5000);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
