let kafka = require('kafka-node');

let client = new kafka.KafkaClient({ kafkaHost: 'oldbox.cloud:9092' });

let producer = new kafka.Producer(client);

let payloads = [{ topic: 'test', messages: JSON.stringify({ hola: "mundo" }), partition: 0 }];

const topicsToCreate = [{
  topic: 'usuarios',
  partitions: 1,
  replicationFactor: 1
}, {
  topic: 'atracciones',
  partitions: 1,
  replicationFactor: 1
}];


client.createTopics(topicsToCreate, (err, data) => {
  if (err)
    console.error("Error!", err)
  else
    console.log("Topicos creados!", data);
})


let i = 0;

producer.on('ready', () => {

  setInterval(() => {
    i++;
    payloads[0].messages = JSON.stringify({ number: i });
    producer.send(payloads, (err, data) => {
      console.log(data);
    });
  }, 2000);

});

producer.on('error', (err) => { console.log(err) })