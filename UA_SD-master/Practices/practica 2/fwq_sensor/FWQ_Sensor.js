const attrpersontimeintervald = process.env.ATTRPERSONTIMEINTER * 1000 || 2000;

if (!process.env.ATTRPERSONTIMEINTER)
  console.warn('Advertencia: No se ha especificado un intervalo de emision de personas en una atraccion, usando el valor por defecto, 2s');

let kafka = require('kafka-node');

const topicsToCreate = [{
  topic: 'visitante-rep',
  partitions: 1,
  replicationFactor: 1
}, {
  topic: 'visitante-env',
  partitions: 1,
  replicationFactor: 1
}, {
  topic: 'attrpersonas',
  partitions: 1,
  replicationFactor: 1
}, {
  topic: 'atraccion',
  partitions: 1,
  replicationFactor: 1
}];


let client = new kafka.KafkaClient({ kafkaHost: process.env.KAFKAADDRESS || 'oldbox.cloud:9092' });


client.createTopics(topicsToCreate, (err, data) => {
  if (err)
    console.error("Error!", err)
  else
    console.log("Topicos creados!", data);
});



let producer = new kafka.Producer(client);

let payloads = [{ topic: 'attrpersonas', messages: "", partition: 0 }];

let id = process.env.IDATTR || process.argv[2];
let coordX = process.env.X || process.argv[3];
let coordY = process.env.Y || process.argv[4];
let imagen = process.env.IMAGEN || process.argv[5];

if (!id) throw ("Falta la ID de la atraccion");

console.log(coordX, coordY);
if (!coordX || isNaN(coordX)) {
  throw ("La coordenada X no es un número");
}

if (coordX > 20) {
    throw ("La coordenada X está fuera del mapa");
}

if (!coordY || isNaN(coordY)) {
  throw ("La coordenada Y no es un número");
}

if (coordY > 20) {
  throw ("La coordenada Y está fuera del mapa");
}

let randomIntFromInterval = (min, max) => {
  // min and max included
  return Math.floor(Math.random() * (max - min + 1) + min)
}

let inter = setInterval(() => {
  if (producer.ready) {
    clearInterval(inter);

    setInterval(() => {
      // Cada persona tiene un tiempo de 5 segs
      payloads[0].messages = JSON.stringify({ personas: randomIntFromInterval(0, 14), id, coordX, coordY, imagen });

      producer.send(payloads, (err, data) => {
        console.log(data);
      });

    }, attrpersontimeintervald);

  }

});


producer.on('error', (err) => { console.log(err) })