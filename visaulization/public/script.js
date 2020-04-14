const ws = new WebSocket('ws://localhost:8080');
ws.onopen = () => {
  ws.send('hello');
};
const states = [];
ws.onmessage = ({ data }) => states.push(JSON.parse(data));

ws.onerror = console.error;

const delay = 50;
const zoo = new Set();
let avgGrassLevel = 0;

setTimeout(() => {
  const { object, data: [dim] } = states.shift();

  if (object !== 'grassland') {
    throw new Error('Wrong data');
  }

  const { updateCells, updateAnimals } = createWorld("div.world", dim, 500 / dim, delay);

  function processCellAction(data) {
    const cells = data.slice(0, dim * dim).map((grassLevel, id) => ({ id, grassLevel }));
    const totalGrassLevel = cells
      .map(({ grassLevel }) => grassLevel)
      .reduce((a, b) => a + b, 0);
    avgGrassLevel = totalGrassLevel / cells.length;

    updateCells(cells);
    updateAnimals([...zoo.values()]);
  }

  let timeoutId;
  timeoutId = (function run() {
    let state;
    zoo.clear();
    do {
      state = states.shift();
      const { object, data } = state;
      if (object === 'cells') {
        processCellAction(data);
      } else if (object === 'animal') {
        const [id, age, energy, cellId, species] = data;
        zoo.add({ id, age, energy, cellId, species });
      } else {
        return clearTimeout(timeoutId);
      }
    } while (state.object === 'animal');

    timeoutId = setTimeout(run, delay);
  })();

}, 1000);

function createWorld(selector, dim, cellSize, delay = 350) {
  const land = new Array(dim * dim)
    .fill(0).map((v, id) => ({ id, grassLevel: 0 }));

  const speciesColor = d3.scaleOrdinal(d3.schemeCategory10);
  const grassColor = d3.scaleLinear().domain([1, 100]).range(['white', 'green']);
  const X = (id) => id % dim;
  const Y = (id) => Math.floor(id / dim);

  const svg = d3.select(selector)
    .append('svg')
    .attr('width', cellSize * dim)
    .attr('height', cellSize * dim);

  function updateCells(cells) {
    const board = svg.selectAll("rect").data(cells, ({ id }) => id);

    board.enter()
      .append("rect")
      .style("class", "cells")
      .attr("width", cellSize + "px")
      .attr("height", cellSize + "px")
      .attr("fill", ({ grassLevel }) => grassColor(grassLevel))
      .attr("x", ({ id }) => X(id) * cellSize)
      .attr("y", ({ id }) => Y(id) * cellSize);

    board.attr("fill", ({ grassLevel }) => grassColor(grassLevel));
  }

  updateCells(land);

  const drift = 0.25;
  const driftedPosition = pos => cellSize * (pos + 0.5 + drift * (Math.random() - 0.5) / 0.5);

  function updateAnimals(animals) {
    const zoo = svg.selectAll("circle").data(animals, ({ id }) => id);
    zoo
      .enter()
      .append("circle")
      .style("class", "animal")
      .attr("r", ({ energy }) => 0.25 * cellSize * energy)
      .attr("cx", ({ cellId }) => driftedPosition(X(cellId)))
      .attr("cy", ({ cellId }) => driftedPosition(Y(cellId)))
      .attr("fill", ({ species }) => speciesColor(species));
    zoo
      .transition()
      .duration(delay)
      .attr("cx", ({ cellId }) => driftedPosition(X(cellId)))
      .attr("cy", ({ cellId }) => driftedPosition(Y(cellId)));
    zoo
      .exit()
      .transition()
      .duration(delay)
      .attr("fill", "gray")
      .attr("r", 0)
      .remove();
  }

  return {
    updateAnimals,
    updateCells
  };
}

// ---------------------------------------------------------------------
const options = {
  width: 600,
  height: 300,
  vAxis: {
    0: { minValue: 0/*, maxValue: 1*/ },
    1: { minValue: 0, maxValue: 1 }
  },
  series: {
    0: { targetAxisIndex: 0, color: 'green' },
    1: { targetAxisIndex: 1, color: 'blue' },
    2: { targetAxisIndex: 1, color: 'orange' },
  },
  animation: {
    duration: 500,
    easing: 'in'
  }
};

let C = 0;
google.charts.load('current', { 'packages': ['corechart'] });
google.charts.setOnLoadCallback(() => {
  var chart = new google.visualization.LineChart(document.getElementById('visualization-zoo'));
  var data = new google.visualization.DataTable();

  data.addColumn('number', 'x');
  data.addColumn('number', 'grass');
  data.addColumn('number', 'zebra');
  data.addColumn('number', 'antilope');

  setInterval(() => {
    const counters = { 1: 0, 2: 0 };
    for (const a of [...zoo.values()]) {
      counters[a.species]++;
    }
    data.addRow([C++, avgGrassLevel, ...Object.values(counters)]);
  }, 100);

  setInterval(() => {
    chart.draw(data, options);
  }, 1000);
});
