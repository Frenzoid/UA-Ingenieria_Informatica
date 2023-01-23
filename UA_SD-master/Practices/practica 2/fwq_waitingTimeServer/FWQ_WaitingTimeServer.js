let kafka = require('kafka-node');

const httpServer = require("http").createServer();
const encrypt = require('socket.io-encrypt')
const io = require("socket.io")(httpServer, {
    cors: {
        origin: "*",
    }
});

let atracciones = [];
const secret = process.env.SECRET || "ABRACADABRA";
if (!process.env.SECRET)
    console.warn("Advertencia: No se ha especificado un Secret, usando el valor por defecto.");

const puerto = Number(process.env.WTSPORT || process.argv[2]);
if (!puerto) throw ("Puerto del WTS no está definido.");

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


let client = new kafka.KafkaClient({ kafkaHost: process.env.KAFKAADDRESS || 'oldbox.cloud:9092', autoConnect: true });

client.createTopics(topicsToCreate, (err, data) => {
    if (err)
        console.error("Error!", err)
    else
        console.log("Topicos creados!", data);
});

let consumer = new kafka.Consumer(client, [{ topic: 'attrpersonas', partition: 0 },], { autoCommit: true, });

// Si el waitingTimeServer recibe la información
consumer.on('message', (message) => {
    let atraccion = JSON.parse(message.value);
    atraccion.updatedAt = Date.now();
    atraccion.tiempo = 5 * atraccion.personas;

    atracciones[atraccion.id] = atraccion;
    console.log(atraccion);
});

consumer.on('error', (err) => { console.log(err) })

io.use(encrypt(secret));

io.on('connection', (socket) => {
    console.log("Se ha establecido la conexión con id", socket.id);
    socket.on("solicitar_atracciones", () => {
        console.log("enviando atracciones");
        socket.emit("atracciones_enviadas", atracciones);
    })

})

io.on('disconnect', () => {
    console.log("Se ha desconectado el Engine");
});

httpServer.listen(puerto);
console.log("Escuchando en", puerto);