// npm run start:registry 9090
const encrypt = require('socket.io-encrypt')

const { server, io, app } = require("./servers");
const sequelize = require('./config/bd-connector');

const Aforo = require("./models/aforo");

const runDBPreparations = require('./config/db-functions');
const bindSocketFunctions = require("./controller");

const router = require("./apirest");

const puerto = Number(process.env.FWQRPORT || process.argv[2]);



async function start() {
    if (!process.env.SECRET)
        console.warn("Advertencia: No se ha especificado un Secret, usando el valor por defecto.");

    if (!puerto)
        throw ("No se ha especificado el puerto.")

    try {
        // Nos logeamos en el servidor de bases de datos.
        await sequelize.authenticate();
        console.log("Sequelize: Successuflly authenticated.");

        // Realizamos las preparaciones previas en la base de datos (crear tablas etc..)
        await runDBPreparations();

        // Pillamos el aforo, si no hay nada significa que el FWQ_Engine aún no ha arrancado.
        let aforo;
        while (!aforo) {
            await sleep(5000);
            try {
                aforo = await Aforo.findAll({
                    limit: 1,
                    order: [['createdAt', 'DESC']]
                });
            } catch (err) {
                console.log("Esperando 5s a que FWQ_ENGINE genere un AFORO.");
            }
        }
        aforo = aforo[0].aforo;

        app.use("/", router);

        io.use(encrypt(process.env.SECRET || 'ABRACADABRA'));

        // Por cada conexion...
        io.on("connection", async (socket) => {

            aforo = await Aforo.findAll({
                limit: 1,
                order: [['createdAt', 'DESC']]
            });
            aforo = aforo[0].aforo;

            console.log("Aforo máximo:", aforo);
            console.log("Conexion entrante desde direccion:", socket.handshake.address, "con id de sesion:", socket.id);

            // Asignamos funcionalidades al socket.
            bindSocketFunctions(io, socket, aforo);
        });

        // Arrancamos el servidor.
        server.listen(puerto);
        console.log("Servidor escuchando en el puerto:", puerto)

    } catch (err) { console.error(err) }
}

// Una funcion que hace esperar ciertos ms.
function sleep(ms) {
    return new Promise((resolve) => {
        setTimeout(resolve, ms);
    });
}

// Arrancamos
start().catch((err) => console.error(err));