"use strict";
exports.__esModule = true;
//import express from "express";
//import path from "path";
var express = require("express");
var app = express();
var port = 8080; // default port to listen
// define a route handler for the default home page
app.get("/", function (req, res) {
    // render the index template
    //res.render( "index" );
    res.send('Hello world!');
});
// start the express server
app.listen(port, function () {
    // tslint:disable-next-line:no-console
    console.log("server started at http://localhost:" + port);
});
