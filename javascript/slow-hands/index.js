//console.log('running SlowHands bash application...');
//process.stdout.write("sh: ");

const readline = require('readline');
const clear = require('clear');
const chalk = require('chalk');
const figlet = require('figlet');
const fs = require('fs');
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
                        if (fs.lstatSync(workingDirectory + '\\' + items[i]).isDirectory()) {
                            console.log(chalk.white(items[i]));
                        }
                    } 
                    for (var i=0; i<items.length; i++) {
                        if (!fs.lstatSync(workingDirectory + '\\' + items[i]).isDirectory()) {
                            //console.log(items[i].padEnd(30, '.'));
                            console.log(chalk.white(items[i]).padEnd(40, '.') + ' ... ' + (fs.statSync(workingDirectory + '\\' + items[i]).size / 1000000.0 + 'Mb').padStart(15, '.'));
                        }
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