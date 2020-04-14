const WebSocket = require('ws');
const sim = require('./simulator');

const wss = new WebSocket.Server({ port: 8080 });

wss.on('connection', function connection(ws) {
  console.log(wss.clients.size);

  ws.once('message', function incoming() {
    sim((data) => ws.send(JSON.stringify(data)));
  });

});

wss.on('disconnect', () => console.log('disconnect'));
