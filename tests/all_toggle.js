const RGB = require('../index');

const rgb = new RGB();

setInterval(() => {
  rgb.allToggle(`#${Math.floor(Math.random() * 16777215).toString(16)}`);
}, 500);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
