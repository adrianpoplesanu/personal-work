const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 8090 });

wss.on('connection', ws => {
    console.log("connection");

    ws.on('message', message => {
        console.log(message);
    });
});