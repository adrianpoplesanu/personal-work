import * as express from 'express';
//import express from "express"; // this doesn't work

namespace Application {
  export class Console {
    name: string;
    port: number;
    router: Routing.RouterInterface;

    constructor(name: string, port: number = 8080) {
      this.name = name;
      this.port = port;
    }

    bind_router(app : express, r : Routing.RouterInterface) {
      console.log("router added...");
      r.bind('/', 'HomepageController', 'index', 'GET');
      r.connect(app);
    }

    listen () {

    }

    run() {
      let r = new Routing.Router();
      let app = express();
      //app.get("/", (req, res) => {
      //  res.send("Hello world with typescript architecture!");
      //});
      this.bind_router(app, r);
      app.listen(this.port, () => {
        console.log(`server is listening on port ${ this.port }...`);
      });
    }
  }
}

namespace Controllers {
  export class BaseController {
    // ...
  }

  export class HomepageController {
    index(req, res) {
      // ...
      return "Beautiful";
    }
  }
}

namespace Model {
  export class DataAccesor {
    // ...
  }
}

namespace Templating {
  export class TemplateRenderer {
    // ...
  }
}

namespace Routing {
  class Bind {
      path: string;
      controller: string;
      action: string;
      method: string;
      constructor(path : string, controller : string, action : string, method : string) {
        this.path = path;
        this.controller = controller;
        this.action = action;
        this.method = method;
      }
  }

  export interface RouterInterface {
    binds : Array<Bind>;
    bind(path : string, controller : string, action : string, method : string) : void;
    connect(app : express) : void;
  }

  export class Router implements RouterInterface {
    binds : Array<Bind>;

    constructor() {
        this.binds = new Array<Bind>();
    }

    bind (path : string, controller : string, action : string, method : string) {
      console.log("Router::bind()");
      let b = new Bind(path, controller, action, method);
      this.binds.push(b);
    }

    connect(app : express) {
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

        eval(
          'var c = new Controllers.' + value.controller + '();' +
          'if (value.method == "GET") {' +
          '  app.get("/", (req, res) => { res.send(c. ' + value.action + '(req, res)); } );' +
          '}'
        );
      });
    }
  }
}

let app = new Application.Console("Amazon Console");
app.run();
