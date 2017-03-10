var _rgb = require('../index'),
  rgb = new _rgb();

setInterval(() => {
  rgb.allToggle("#ff33cc");
},500);

process.on('SIGTERM', function () {
  process.exit();
});

process.on('SIGINT', function () {
  process.exit();
});
