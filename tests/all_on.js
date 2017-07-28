const RGB = require('../index');

const rgb = new RGB();

rgb.allOn('#cc3399');

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
