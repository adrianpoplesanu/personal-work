const WebSocket = require('ws');

//let socket = new WebSocket("ws://localhost:8090");
let socket = new WebSocket("ws://192.168.0.108:8090");

socket.onopen = function(e) {
    data = {"operation": "send-message", "message": "neata adrian!!!"};
    //var packet = JSON.parse(data);
    var packet = JSON.stringify(data);
    socket.send(packet);
};