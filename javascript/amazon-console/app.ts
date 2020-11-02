import * as express from 'express';
//import express from "express"; // this doesn't work

namespace Application {
  export class Application {
    name: string;
    port: number;
    router: Routing.RouterInterface;

    constructor(name: string, port: number = 8080) {
      this.name = name;
      this.port = port;
    }

    add_router(r : Routing.RouterInterface) {
      console.log("router added...");
      r.bind('/', 'HomepageController', 'index', 'GET');
      r.connect(this);
    }

    listen () {

    }

    run() {
      let r = new Routing.Router();
      this.add_router(r);
      let app = express();
      app.get("/", (req, res) => {
        res.send("Hello world with typescript architecture!");
      });
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
    connect(app : Application.Application) : void;
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

    connect(app : Application.Application) {
      /*for(bind in this.binds) {
          console.log(bind.path);
      }*/
      this.binds.forEach(function (value) {
        console.log(value.path);
      });
    }
  }
}

let app = new Application.Application("Amazon Console");
app.run();
