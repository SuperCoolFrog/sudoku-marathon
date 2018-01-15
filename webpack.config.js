const path = require('path');

module.exports = {
  entry: {
    index: './src/index.bs.js',
    CreateSudokuWorker: './src/workers/CreateSudokuWorker/CreateSudokuWorker.bs.js'
  },
  output: {
    path: path.join(__dirname, "build"),
    filename: "[name].bs.js",
  },
};
