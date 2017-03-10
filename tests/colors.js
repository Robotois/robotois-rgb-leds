const RGB = require('../index');

const rgb = new RGB();

setInterval(() => {
  rgb.allToggle('#ff33cc');
}, 500);

process.on('SIGTERM', () => {
  process.exit();
});

process.on('SIGINT', () => {
  process.exit();
});
