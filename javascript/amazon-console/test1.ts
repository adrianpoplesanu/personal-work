//import express from "express";
//import path from "path";
import * as express from 'express';

const app = express();
const port = 8080; // default port to listen

// define a route handler for the default home page
app.get( "/", ( req, res ) => {
    // render the index template
    //res.render( "index" );
    res.send('Hello world!');
} );

// start the express server
app.listen( port, () => {
    // tslint:disable-next-line:no-console
    console.log( `server started at http://localhost:${ port }` );
} );
