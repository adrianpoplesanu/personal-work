import * as express from 'express';
//import express from "express"; // this doesn't work

namespace Application {
  export class Application {
    name: string;
    port: number;

    constructor(name: string, port: number = 8080) {
      this.name = name;
      this.port = port;
    }

    add_router() {
      console.log("router added...");
    }

    run() {
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
  interface RouterInterface {
    bind(path : string, controller : string, action : string, method : string) : void;
  }

  export class Router implements RouterInterface {
    bind (path : string, controller : string, action : string, method : string) {
      console.log("Router::bind()");
    }
  }
}

let app = new Application.Application("Amazon Console");
app.run();
