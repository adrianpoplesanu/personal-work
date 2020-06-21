console.log("running Amazon diagnostic...");

const http = require('http');
const { exec } = require("child_process");
//var execSync = require("exec-sync"); // nu merge

const requestListener = function (req, res) {
    console.log(req.url);

    if (req.url == '/') {
        // afiseaza linkul catre status pages
        res.writeHead(200);
        res.end('<html>Amazon simple checker<br><a href="/image-uploader/status">image-uploader</a><br><a href="/web-online-multiplayer/status">web-online-multiplayer</a></html>');
        return;
    }

    if (req.url == '/image-uploader/status') {
        var ps_ramona = "";
        var ps_web_online_multiplayer = "";
        exec("ps -ef | grep ramona", (error, stdout, stderr) => {
            if (error) {
                console.log(`error: ${error.message}`);
                ps_ramona = "error: ${error.message}";
                res.end(ps_ramona);
                return;
                //return;
            } else
            if (stderr) {
                console.log(`stderr: ${stderr}`);
                ps_ramona = "stderr: ${stderr}";
                res.end(ps_ramona);
                return;
                //return;
            } else {
                console.log(`stdout: ${stdout}`);
                if (stdout.indexOf("/home/ubuntu/tmp/go/bin/go run /home/ubuntu/Documents/git-projects/personal-work/golang/ramona1/main.go") != -1) {
                    console.log("running");
                    res.writeHead(200);
                    res.end('<html>running <a href="/">start</a> <a href="/">stop</a> <a href="/">back</a></html>');
                    return;
                } else {
                    console.log("stopped");
                    res.writeHead(200);
                    res.end('<html>stopped <a href="/">start</a> <a href="/">stop</a> <a href="/">back</a></html>');
                    return;
                }
            }
        });
    }
    /*if (req.url == '/web-online-multiplayer/inspect') {

    }
    if (req.url == '/image-uploader/inspect') {

    }*/
    if (req.url == '/web-online-multiplayer/start') {
        res.writeHead(200);
        res.end('<html>Console output:<br>bla bla<br><a href="/">back to checker</a></html>');
    }
    if (req.url == '/web-online-multiplayer/stop') {
        res.writeHead(200);
        res.end('<html>Console output:<br>bla bla<br><a href="/">back to checker</a></html>');    }
    if (req.url == '/image-uploader/start') {
        res.writeHead(200);
        res.end('<html>Console output:<br>bla bla<br><a href="/">back to checker</a></html>');
    }
    if (req.url == '/image-uploader/stop') {
        res.writeHead(200);
        res.end('<html>Console output:<br>bla bla<br><a href="/">back to checker</a></html>');
    }
    //res.end('');
    //return;
}

const server = http.createServer(requestListener);
server.listen(8093);