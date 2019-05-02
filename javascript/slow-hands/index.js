//console.log('running SlowHands bash application...');
//process.stdout.write("sh: ");

const readline = require('readline');
const clear = require('clear');
const chalk = require('chalk');
const figlet = require('figlet');
var fs = require('fs');
var path = require('path');
var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  terminal: false
});

var workingDirectory = path.resolve(".");
var isLSCommand = false;

clear();
console.log(
  chalk.yellow(
    figlet.textSync('SlowHands', { font: 'Doom', horizontalLayout: 'full' })
  )
);
process.stdout.write("sh> ");

rl.on('line', function(line){
    if (line) {
        switch(line) {
            case 'pwd':
                console.log(chalk.green(workingDirectory));
            break;
            case 'ls':
                isLSCommand = true;
                fs.readdir(workingDirectory, function(err, items) {
                    console.log(chalk.green('Contents of ' + workingDirectory));
                 
                    for (var i=0; i<items.length; i++) {
                        console.log(chalk.white(items[i]));
                    }
                    process.stdout.write("sh> ");
                });
            break;
            case 'exit':
                console.log(chalk.yellow('Good bye! SlowHands (c) 2o19.'));
                process.exit();
            break;
            default:
                console.log(chalk.red('Command not found'));
            break;
        }
    }
    if (!isLSCommand) {
        process.stdout.write("sh> ");
    } else {
        isLSCommand = false;
    }
});