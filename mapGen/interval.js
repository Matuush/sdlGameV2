const fs = require('fs');
const path = require('path');
const http = require('http');
const WebSocket = require('websocket');
const childProcess = require('child_process');
var input = require('./input.json');
const filename = "polygonBasedGeneration";
var prevMapGen;
var prevInput;
setInterval(() => {
    var curr = fs.readFileSync(`./${filename}.js`).toString();
    invalidateRequireCacheForFile(`./input.json`);
    input = require('./input.json');
    if (prevMapGen == curr && prevInput == input) return;
    prevMapGen = curr;
    prevInput = input;
    console.log("Reevaluating...");
    invalidateRequireCacheForFile(`./${filename}.js`);
    try {
        mapGen = require(`./${filename}.js`);
        output = mapGen(input);
    } catch (e) {
        console.log("Error with input processing. Error: " + e);
        return;
    }
    try {
        fs.writeFileSync("./output.json", JSON.stringify(output));
    } catch (e) {
        console.log("Error with output write.");
    }
    for (var c of wsConnections) {
        if (!c) continue;
        console.log("Sending output...")
        c.sendUTF(JSON.stringify({
            fieldSize: 50,
            map: output
        }))
    }
    console.log("Reevaluated.");
}, 300);
var invalidateRequireCacheForFile = function (filePath) {
    delete require.cache[path.resolve(filePath)];
};

//HTTP SERVER FOR LIVE PREVIEW OF OUTPUT
/**
 * @type {Array<WebSocket.connection>}
 */
var wsConnections = [];
const httpServer = http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    fs.createReadStream("./mapshow.html").pipe(res);
});
const wsServer = new WebSocket.server({
    httpServer: httpServer
});
wsServer.on("request", request => {
    var connection = request.accept("echo-protocol", request.origin);
    wsConnections.push(connection);
    connection.on("close", () => {
        delete wsConnections.find((n) => {
            return n === connection;
        });
    });
    connection.on("message", message => {
        connection.sendUTF("Method not supported. Use websocket only for updates.");
    });
    connection.on("open", () => {
        connection.sendUTF(JSON.stringify({
            fieldSize: 50,
            map: output
        }))
    })
});
httpServer.listen(5050);
childProcess.exec("start http://localhost:5050");