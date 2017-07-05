const RGB = require('../index');

const rgb = new RGB();

// rgb.setRGB(1, 204, 51, 153);
rgb.rainbow();

setTimeout(() => {
  rgb.release();
}, 10000);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
