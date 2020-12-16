const fs = require('fs');
const input = require('./input.json');
const filename = "polgonBasedGeneration";
const mapGen = require(`./${filename}.js`);
const output = mapGen(input);
fs.writeFileSync("./output.json", JSON.stringify(output));