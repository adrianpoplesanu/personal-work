"use strict";
exports.__esModule = true;
var express = require("express");
//import express from "express"; // this doesn't work
var Application;
(function (Application) {
    var Console = /** @class */ (function () {
        function Console(name, port) {
            if (port === void 0) { port = 8080; }
            this.name = name;
            this.port = port;
        }
        Console.prototype.bind_router = function (app, r) {
            console.log("router added...");
            r.bind('/', 'HomepageController', 'index', 'GET');
            r.connect(app);
        };
        Console.prototype.listen = function () {
        };
        Console.prototype.run = function () {
            var _this = this;
            var r = new Routing.Router();
            var app = express();
            //app.get("/", (req, res) => {
            //  res.send("Hello world with typescript architecture!");
            //});
            this.bind_router(app, r);
            app.listen(this.port, function () {
                console.log("server is listening on port " + _this.port + "...");
            });
        };
        return Console;
    }());
    Application.Console = Console;
})(Application || (Application = {}));
var Controllers;
(function (Controllers) {
    var BaseController = /** @class */ (function () {
        function BaseController() {
        }
        return BaseController;
    }());
    Controllers.BaseController = BaseController;
    var HomepageController = /** @class */ (function () {
        function HomepageController() {
        }
        HomepageController.prototype.index = function (req, res) {
            // ...
            return "Beautiful";
        };
        return HomepageController;
    }());
    Controllers.HomepageController = HomepageController;
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
            /*app.get("/", (req, res) => {
              eval("console.log('neata!');");
              res.send("Hello world with typescript architecture from connect method!");
          });*/
            this.binds.forEach(function (value) {
                console.log(value.path);
                console.log(value.controller);
                console.log(value.action);
                console.log(value.method);
                eval('var c = new Controllers.HomepageController();' +
                    'if (value.method == "GET") {' +
                    '  app.get("/", (req, res) => { res.send(c. ' + value.action + '(req, res)); } );' +
                    '}');
            });
        };
        return Router;
    }());
    Routing.Router = Router;
})(Routing || (Routing = {}));
var app = new Application.Console("Amazon Console");
app.run();
