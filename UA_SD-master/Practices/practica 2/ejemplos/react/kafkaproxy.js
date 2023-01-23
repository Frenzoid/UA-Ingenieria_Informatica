let kafka = require('kafka-node');
const httpServer = require("http").createServer();
const io = require("socket.io")(httpServer, {
    cors: {
        origin: "*",
    }
});

let client = new kafka.KafkaClient({ kafkaHost: 'oldbox.cloud:9092', autoConnect: true });
let producer = new kafka.Producer(client);
let consumer = new kafka.Consumer(client, [{ topic: 'test', partition: 0 }], { autoCommit: true, });

let payloads = [{ topic: 'test', messages: JSON.stringify(), partition: 0 }];

producer.on('ready', () => {
    console.log("kafka producer ready!");

    io.on("connection", (socket) => {

        socket.on("dato_enviado", (dato) => {
            payloads[0].messages = JSON.stringify(dato);
            producer.send(payloads, (err, data) => {
                console.log("enviado", data);
            });
        });
    });

});

consumer.on('message', (message) => {

    console.log("recibido", JSON.parse(message.value));
    io.emit("dato_recibido", JSON.parse(message.value));

});

producer.on('error', (err) => { console.log(err) })

httpServer.listen(9111);
