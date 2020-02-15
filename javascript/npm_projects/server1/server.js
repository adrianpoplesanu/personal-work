var http = require('http');

const PORT = 8080;

function handleRequest(request, response) {
    console.log(request.method + " " + request.headers.host + request.url + " HTTP " + request.httpVersion + "/" + request.httpVersionMajor);
    console.log("User-Agent: " + request.headers['user-agent']);
    response.end('Server working properly. Requested URL : ' + request.url);
}

var myFirstServer = http.createServer(handleRequest);

myFirstServer.listen(PORT, function() {
    console.log("Server listening on: http://localhost:%s", PORT);
});
