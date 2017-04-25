const RGB = require('../index');

const rgb = new RGB();

setInterval(() => {
  rgb.toggle(1, `#${Math.floor(Math.random() * 16777215).toString(16)}`);
  rgb.toggle(2, `#${Math.floor(Math.random() * 16777215).toString(16)}`);
  rgb.toggle(3, `#${Math.floor(Math.random() * 16777215).toString(16)}`);
  rgb.toggle(4, `#${Math.floor(Math.random() * 16777215).toString(16)}`);
}, 500);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
