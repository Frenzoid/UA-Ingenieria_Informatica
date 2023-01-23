const kafka = require('kafka-node');
const httpServer = require("http").createServer();
const AesEncryption = require('aes-encryption')
const encrypt = require('socket.io-encrypt')
const io = require("socket.io")(httpServer, {
    cors: {
        origin: "*",
    }
});

const aes = new AesEncryption()
const secretAES = process.env.REACT_APP_SECRETAES || '11122233344455566677788822244455555555555555555231231321313aaaff'
aes.setSecretKey(secretAES)

const secret = process.env.REACT_APP_SECRET || "ABRACADABRA";
if (!process.env.REACT_APP_SECRET)
    console.warn("Advertencia: No se ha especificado un Secret, usando el valor por defecto.");

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


let payloads = [{ topic: 'visitante-rep', messages: "", partition: 0 }];

let client1 = new kafka.KafkaClient({ kafkaHost: process.env.REACT_APP_KAFKAADDRESS || 'oldbox.cloud:9092', autoConnect: true });
let client2 = new kafka.KafkaClient({ kafkaHost: process.env.REACT_APP_KAFKAADDRESS || 'oldbox.cloud:9092', autoConnect: true });

client1.createTopics(topicsToCreate, (err, data) => {
    if (err)
        console.error("Error!", err)
    else {
        console.log("Topicos creados!", data, "Creando clientes");

        io.use(encrypt(secret));

        let visitanteRepProd = new kafka.Producer(client1);
        let visitanteCliEnv = new kafka.Consumer(client1, [{ topic: 'visitante-env', partition: 0 }], { autoCommit: true, });
        let atraccionCli = new kafka.Consumer(client2, [{ topic: 'atraccion', partition: 0 }], { autoCommit: true, });

        let inter = setInterval(() => {
            if (visitanteRepProd.ready) {
                clearInterval(inter);
                console.log("Kafka visitante ready status:", visitanteRepProd.ready);

                io.on("connection", (socket) => {
                    console.log("Productor listo para", socket.handshake.address);

                    socket.on("dato_enviado_usr", (dato) => {
                        payloads[0].messages = JSON.stringify(dato);
                        visitanteRepProd.send(payloads, (err, data) => {
                            if (err)
                                console.error("Error!", err)
                            else
                                console.log(data);
                        });
                    });
                });
            }
        }, 2000);

        atraccionCli.on('message', (message) => {
            console.log("Dato recibido de Atracciones", message.value);
            io.emit("dato_recibido_attr", JSON.parse(aes.decrypt(message.value)));
        });

        visitanteCliEnv.on('message', (message) => {
            console.log("Dato recibido de Usuario", message.value);
            io.emit("dato_recibido_usr", JSON.parse(aes.decrypt(message.value)));
        });

        visitanteRepProd.on("error", (err) => console.error(err));
        visitanteCliEnv.on("error", (err) => console.error(err));
        atraccionCli.on("error", (err) => console.error(err));
    }
});


httpServer.listen(9111);
console.log("Servidor escuchando en", process.env.REACT_APP_KAFKACONTROLLER || "http://localhost:9111");
