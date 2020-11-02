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
        Application.prototype.add_router = function (r) {
            console.log("router added...");
            r.bind('/', 'HomepageController', 'index', 'GET');
            r.connect(this);
        };
        Application.prototype.listen = function () {
        };
        Application.prototype.run = function () {
            var _this = this;
            var r = new Routing.Router();
            this.add_router(r);
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
var Templating;
(function (Templating) {
    var TemplateRenderer = /** @class */ (function () {
        function TemplateRenderer() {
        }
        return TemplateRenderer;
    }());
    Templating.TemplateRenderer = TemplateRenderer;
})(Templating || (Templating = {}));
var Routing;
(function (Routing) {
    var Bind = /** @class */ (function () {
        function Bind(path, controller, action, method) {
            this.path = path;
            this.controller = controller;
            this.action = action;
            this.method = method;
        }
        return Bind;
    }());
    var Router = /** @class */ (function () {
        function Router() {
            this.binds = new Array();
        }
        Router.prototype.bind = function (path, controller, action, method) {
            console.log("Router::bind()");
            var b = new Bind(path, controller, action, method);
            this.binds.push(b);
        };
        Router.prototype.connect = function (app) {
            /*for(bind in this.binds) {
                console.log(bind.path);
            }*/
            this.binds.forEach(function (value) {
                console.log(value.path);
            });
        };
        return Router;
    }());
    Routing.Router = Router;
})(Routing || (Routing = {}));
var app = new Application.Application("Amazon Console");
app.run();
