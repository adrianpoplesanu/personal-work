const express = require( "express" );
var path = require('path');
var mysql = require('mysql');

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "aaa"
});

con.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
});

const app = express();
const port = 8080; // default port to listen

app.engine('.html', require('ejs').__express);

app.set('views', path.join(__dirname, 'views'));

app.use(express.static(path.join(__dirname, 'public')));

app.set('view engine', 'html');

// define a route handler for the default home page
app.get( "/", ( req, res ) => {
    //res.send( "Hello world!" );
    res.render('home', {});
} );

// start the Express server
app.listen( port, () => {
    console.log( `server started at http://localhost:${ port }` );
} );
