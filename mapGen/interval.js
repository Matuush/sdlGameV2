const fs = require('fs');
const path = require('path');
var input = require('./input.json');
var mapGen = require('./generation.js');
var output = mapGen(input);
fs.writeFileSync("./output.json", JSON.stringify(output));
var prevMapGen = fs.readFileSync("./generation.js").toString();
setInterval(() => {
    var curr = fs.readFileSync("./generation.js").toString();
    if (prevMapGen == curr) return;
    prevMapGen = curr;
    console.log("Reevaluating...");
    input = require('./input.json');
    invalidateRequireCacheForFile("./generation.js");
    mapGen = require('./generation.js');
    output = mapGen(input);
    fs.writeFileSync("./output.json", JSON.stringify(output));
    console.log("Reevaluated.");
}, 300);
var invalidateRequireCacheForFile = function(filePath){
	delete require.cache[path.resolve(filePath)];
};