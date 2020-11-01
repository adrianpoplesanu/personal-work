"use strict";
exports.__esModule = true;
var express = require("express");
//import express from "express"; // this doesn't work
var Application;
(function (Application_1) {
    var Application = /** @class */ (function () {
        function Application(name, port) {
            if (port === void 0) { port = 8080; }
            this.name = name;
            this.port = port;
        }
        Application.prototype.run = function () {
            var _this = this;
            var app = express();
            app.get("/", function (req, res) {
                res.send("Hello world with typescript architecture!");
            });
            app.listen(this.port, function () {
                console.log("server is listening on port " + _this.port + "...");
            });
        };
        return Application;
    }());
    Application_1.Application = Application;
})(Application || (Application = {}));
var Controllers;
(function (Controllers) {
    var BaseController = /** @class */ (function () {
        function BaseController() {
        }
        return BaseController;
    }());
    Controllers.BaseController = BaseController;
})(Controllers || (Controllers = {}));
var Model;
(function (Model) {
    var DataAccesor = /** @class */ (function () {
        function DataAccesor() {
        }
        return DataAccesor;
    }());
    Model.DataAccesor = DataAccesor;
})(Model || (Model = {}));
var Templates;
(function (Templates) {
    var TemplateRenderer = /** @class */ (function () {
        function TemplateRenderer() {
        }
        return TemplateRenderer;
    }());
    Templates.TemplateRenderer = TemplateRenderer;
})(Templates || (Templates = {}));
var Router;
(function (Router) {
    var RouterImpl = /** @class */ (function () {
        function RouterImpl() {
        }
        return RouterImpl;
    }());
    Router.RouterImpl = RouterImpl;
})(Router || (Router = {}));
var app = new Application.Application("Amazon Console");
app.run();
