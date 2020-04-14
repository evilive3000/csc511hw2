const { spawn } = require('child_process');

const cmd = '../cmake-build/grassland';

const runSimulations = (callback) => {

  let buffer = '';
  const cli = spawn(cmd);

  cli.stdout.on('data', (data) => {
    const lines = (buffer + data).split("\n");
    buffer = lines.pop();
    lines.forEach(line => {
      const [action, object, data] = line.split('|');
      callback({ action, object, data: data.split(';').map(Number) });
    });
  });

  cli.stderr.on('data', console.error);

  cli.on('close', (code) => console.log(`Close code: ${code}`));
};

module.exports = runSimulations;
