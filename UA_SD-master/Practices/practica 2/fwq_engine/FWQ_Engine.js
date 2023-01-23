const aforo = process.env.AFORO || process.argv[2];
const wtsAddress = process.env.WTSADDRESS || process.argv[3];
const secret = process.env.SECRET || "ABRACADABRA";
// Creo que también va aqui
const AesEncryption = require('aes-encryption')

const aes = new AesEncryption()
const secretAES = process.env.SECRETAES || '11122233344455566677788822244455555555555555555231231321313aaaff'
const APIKEY = process.env.APIKEY || "d9eee5d3d5d5a86c5868e8c61381983c"
aes.setSecretKey(secretAES)

if (!aforo)
    throw ("No se ha especificado el Aforo.");

if (!wtsAddress)
    throw ("Direccion de Waiting Time no especificado.");

if (!process.env.SECRET)
    console.warn("Advertencia: No se ha especificado un Secret, usando el valor por defecto.");

const sequelize = require('./config/bd-connector');
const runDBPreparations = require('./config/db-functions');

const kafka = require('kafka-node');
const io = require("socket.io-client");
const encrypt = require("socket.io-encrypt");
const axios = require("axios");

const User = require("./models/user");
const Atraccion = require("./models/atraccion");
const Ciudad = require("./models/ciudad");

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
    if (err) console.error("Error!", err)
    else console.log("Topicos creados!", data);
});

let payloadsVisitante = [{ topic: 'visitante-env', messages: "", partition: 0 }];
let payloadsAtraccion = [{ topic: 'atraccion', messages: "", partition: 0 }];

let visitanteEnvProd = new kafka.Producer(client);
let atraccionesEnvProd = new kafka.Producer(client);
let visitanteRepCons = new kafka.Consumer(client, [{ topic: 'visitante-rep', partition: 0 }], { autoCommit: true, });

async function start() {
    try {
        // Nos logeamos en el servidor de bases de datos.
        let ciudadesBaseDatos;
        await sequelize.authenticate();
        console.log("Sequelize: Successuflly authenticated.");

        // Realizamos las preparaciones previas en la base de datos (crear tablas etc..)
        await runDBPreparations();

        setInterval(async () => {
            ciudadesBaseDatos = await Ciudad.findAll({ limit: 4, order: [['id', 'ASC']] });
            try {
                ciudadesBaseDatos[0].temperatura = (await axios.get("https://api.openweathermap.org/data/2.5/weather?q=" + ciudadesBaseDatos[0].nombre + "&appid=" + APIKEY + "&units=metric")).data.main.temp;
                ciudadesBaseDatos[1].temperatura = (await axios.get("https://api.openweathermap.org/data/2.5/weather?q=" + ciudadesBaseDatos[1].nombre + "&appid=" + APIKEY + "&units=metric")).data.main.temp;
                ciudadesBaseDatos[2].temperatura = (await axios.get("https://api.openweathermap.org/data/2.5/weather?q=" + ciudadesBaseDatos[2].nombre + "&appid=" + APIKEY + "&units=metric")).data.main.temp;
                ciudadesBaseDatos[3].temperatura = (await axios.get("https://api.openweathermap.org/data/2.5/weather?q=" + ciudadesBaseDatos[3].nombre + "&appid=" + APIKEY + "&units=metric")).data.main.temp;

                ciudadesBaseDatos[0].save();
                ciudadesBaseDatos[1].save();
                ciudadesBaseDatos[2].save();
                ciudadesBaseDatos[3].save();
            } catch (error) {
                console.error(error);
            }
        }, 5000)


        let inter1 = setInterval(() => {
            if (visitanteEnvProd.ready) {
                clearInterval(inter1);

                console.log("Kafka visitante ready status:", visitanteEnvProd.ready);

                visitanteRepCons.on('message', async (message) => {
                    // {"id":1,"name":"a","password":"","x_actual":3,"y_actual":11,"x_destino":3,"y_destino":3,"logged":true}

                    try {
                        let userObject = JSON.parse(message.value);
                        console.log("Dato recibido de Usuario", userObject);

                        let user = await User.findByPk(userObject.id);

                        if (user.logged) {
                            user.x_actual = userObject.x_actual;
                            user.y_actual = userObject.y_actual;
                            user.x_destino = userObject.x_destino;
                            user.y_destino = userObject.y_destino;
                            await user.save();

                            payloadsVisitante[0].messages = aes.encrypt(JSON.stringify(user));
                            visitanteEnvProd.send(payloadsVisitante, (err, data) => {
                                if (err)
                                    console.error("Error!", err)
                                else {
                                    console.log(data);
                                    console.log("Atracciones Solicitadas.");
                                    socketClient.emit("solicitar_atracciones");
                                }
                            });
                        }
                    } catch (err) {
                        console.error("Error, ignorando", err);
                        return;
                    }

                });


                visitanteEnvProd.on("error", (err) => console.error(err));
                visitanteRepCons.on("error", (err) => console.error(err));

            }
        });

        const socketClient = io(process.env.WTSADDRESS || process.argv[3], { timeout: 1000, reconnect: true });
        console.log(process.env.WTSADDRESS || process.argv[3]);
        encrypt(secret)(socketClient);

        socketClient.on("connect", () => {
            console.log("Engine conectado con WTS");


            let inter2 = setInterval(() => {
                if (atraccionesEnvProd.ready) {
                    clearInterval(inter2);

                    console.log("Kafka atraccion ready status:", atraccionesEnvProd.ready);

                    socketClient.on("atracciones_enviadas", async (atracciones) => {
                        console.log("atracciones recibidas", atracciones)
                        atracciones.map((atraccion) => {

                            try {

                                if (atraccion && atraccion.id) {
                                    atraccion.tiempo = comprobarTemperatura(atraccion, ciudadesBaseDatos);
                                    Atraccion.findByPk(atraccion.id).then(async (attr) => {

                                        if (attr) {
                                            attr.time = atraccion.tiempo;
                                            attr.coord_x = atraccion.coordX;
                                            attr.coord_y = atraccion.coordY;
                                            attr.picture = atraccion.imagen;
                                            attr.save();
                                        } else {
                                            attr = await Atraccion.create({
                                                time: atraccion.tiempo,
                                                id: atraccion.id,
                                                picture: atraccion.imagen,
                                                coord_x: atraccion.coordX,
                                                coord_y: atraccion.coordY,
                                            });
                                        }
                                    });
                                }

                            } catch (err) {
                                console.error("Error, ignorando..", err);
                            }


                        });

                        console.log(atracciones);
                        payloadsAtraccion[0].messages = aes.encrypt(JSON.stringify(atracciones));
                        atraccionesEnvProd.send(payloadsAtraccion, (err, data) => {
                            if (err)
                                console.error("Error!", err)
                            else
                                console.log(data);
                        });
                    })
                }

            }, 2000)

        });

        socketClient.on("error", (err) => console.log(wtsAddress, err));

    } catch (err) { console.error(err) }
}

function comprobarTemperatura(atraccion, arrayCiudades) {
    if ((atraccion.coordX >= 0 && atraccion.coordX <= 9) && (atraccion.coordY >= 0 && atraccion.coordY <= 9)) {
        if (arrayCiudades[0].temperatura < 20 || arrayCiudades[0].temperatura > 30) {
            return 1000;
        } else {
            return atraccion.tiempo;
        }
    } else if ((atraccion.coordX >= 10 && atraccion.coordX <= 19) && (atraccion.coordY >= 0 && atraccion.coordY <= 9)) {
        if (arrayCiudades[1].temperatura < 20 || arrayCiudades[1].temperatura > 30) {
            return 1000;
        } else {
            return atraccion.tiempo;
        }
    } else if ((atraccion.coordX >= 0 && atraccion.coordX <= 9) && (atraccion.coordY >= 10 && atraccion.coordY <= 19)) {
        if (arrayCiudades[2].temperatura < 20 || arrayCiudades[2].temperatura > 30) {
            return 1000;
        } else {
            return atraccion.tiempo;
        }
    } else if ((atraccion.coordX >= 10 && atraccion.coordX <= 19) && (atraccion.coordY >= 10 && atraccion.coordY <= 19)) {
        if (arrayCiudades[3].temperatura < 20 || arrayCiudades[3].temperatura > 30) {
            return 1000;
        } else {
            return atraccion.tiempo;
        }
    }
}

start();