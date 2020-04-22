const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 8090 });

console.log("running chat server on port 8090... ok");
var connections = [];

wss.on('connection', ws => {
    console.log("new connection establieshed...");
    connections.push(ws);

    ws.on('message', message => {
        //console.log(message);
        var data = JSON.parse(message);
        console.log(data["operation"]);
        console.log(data["message"]);
    });

    //ws.on('close')
});