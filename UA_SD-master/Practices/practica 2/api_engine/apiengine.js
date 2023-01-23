const express = require('express');
const boom = require('express-boom');
const logger = require('morgan');
const cors = require('cors');

const User = require("./models/user");
const Atraccion = require("./models/atraccion");
const Log = require('./models/log');
const Ciudad = require('./models/ciudad');

const sequelize = require('./config/bd-connector');
const runDBPreparations = require('./config/db-functions');

const puerto = Number(process.env.APIPORT || process.argv[2]);

if (!puerto)
    throw ("No se ha especificado el puerto.")

const app = express();

app.use(boom());

// Body parser configuration
app.use(express.json({ limit: "100mb" }));
app.use(express.urlencoded({ extended: true }));

// Logger to console.
app.use(logger("dev"));

// Enable cors
app.use(cors());

(async () => {


    // Nos logeamos en el servidor de bases de datos.
    await sequelize.authenticate();
    console.log("Sequelize: Successuflly authenticated.");

    // Realizamos las preparaciones previas en la base de datos (crear tablas etc..)
    await runDBPreparations();


    app.get('/atracciones', async (req, res) => {
        try {
            res.json(await Atraccion.findAll());
        } catch (err) {
            console.error("Error!", err);
            res.boom.badRequest("Error atacando la base de datos");
        }
    });

    app.get('/usuarios', async (req, res) => {
        try {
            res.json(await User.findAll());
        } catch (err) {
            console.error("Error!", err);
            res.boom.badRequest("Error atacando la base de datos");
        }
    });

    app.get('/logs', async (req, res) => {
        try {
            res.json(await Log.findAll());
        } catch (err) {
            console.error("Error!", err);
            res.boom.badRequest("Error atacando la base de datos");
        }
    });


    // POR ACABAR
    app.get('/ciudades', async (req, res) => {
        try {
            res.json(await Ciudad.findAll({ limit: 4, order: [['id', 'ASC']] }));
        } catch (err) {
            console.error("Error!", err);
            res.boom.badRequest("Error atacando la base de datos");
        }
    });

    app.post('/ciudades:id', async (req, res) => {
        try {
            let ciudad = await Ciudad.findByPk(req.params.id);
            ciudad.nombre = req.body.nombre;
            await ciudad.save();
            res.json(ciudad);
        } catch (err) {
            console.error("Error!", err);
            res.boom.badRequest("Error atacando la base de datos");
        }
    });

    app.get('/limpiarlogs', async (req, res) => {
        try {
            await Log.destroy({
                where: {},
                truncate: true
            });
            res.json("Limpieza completada");
        } catch (err) {
            console.error("Error!", err);
            res.boom.badRequest("Error atacando la base de datos");
        }
    });


    app.listen(Number(puerto), () => {
        console.log("El servidor está inicializado en el puerto:", puerto);
    });

})();