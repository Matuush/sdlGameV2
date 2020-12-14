const fs = require('fs');
const input = require('./input.json');
const mapGen = require('./generation');
const output = mapGen(input);
fs.writeFileSync("./output.json", JSON.stringify(output));