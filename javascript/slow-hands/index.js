console.log('running SlowHands bash application...');
process.stdout.write("sh: ");

const readline = require('readline');
const clear = require('clear');
const chalk = require('chalk');
const figlet = require('figlet');
var path = require('path');
var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  terminal: false
});

var workingDirectory = path.resolve(".");

clear();
console.log(
  chalk.yellow(
    figlet.textSync('SlowHands', { font: 'Doom', horizontalLayout: 'full' })
  )
);
process.stdout.write("sh> ");
//process.stdout.write(chalk.green('sh>');

rl.on('line', function(line){
    if (line) {
        switch(line) {
            case 'pwd':
                console.log(chalk.green(workingDirectory));
                //process.stdout.write(workingDirectory);
                //process.stdout.write(path.resolve(".") + '\n');
                //workingDirectory = path.basename(process.cwd());
                //process.stdout.write(workingDirectory);
            break;
            case 'exit':
                console.log(chalk.yellow('Good bye! SlowHands (c) 2o19.'));
                //process.stdout.write('Good bye! SlowHands (c) 2o19.');
                process.exit();
            break;
            default:
                console.log(chalk.red('Command not found'));
                //process.stdout.write('Unknown command\n');
            break;
        }
        //console.log("received command: " + line);
    }
    process.stdout.write("sh> ");
});