const express = require('express');
const router = express.Router();
const User = require("./models/user");
const Aforo = require("./models/aforo");
const logger = require("./logger");

let aforoActual = 0;

async function autenticarUsuario(req, res, next) {
    try {

        let aforo = await Aforo.findAll({
            limit: 1,
            order: [['createdAt', 'DESC']]
        });

        aforo = aforo[0].aforo;

        let received = req.body;

        logger(req.ip, "autenticar", JSON.stringify(received));

        if (aforoActual >= aforo) {
            res.boom.badRequest("Se ha alcanzado el aforo máximo!")
            return;
        } else aforoActual++;

        if (!received.name || !received.password) {
            res.boom.badRequest("Faltan datos!")
            aforoActual--;
            return;
        }

        let usr = await User.findOne({ where: { name: received.name } })


        if (!usr) {
            res.boom.badRequest("El usuario no existe")
            aforoActual--;
            return;
        }

        if (!User.checkPassword(received.password, usr.password)) {
            res.boom.badRequest("Credenciales Incorrectas.")
            aforoActual--;
            return;
        }

        usr.logged = true;
        await usr.save();

        res.json(usr);

        console.log("Usuario", usr.name, "autenticado | Aforo:", aforoActual, "/", aforo);

        if (aforoActual == aforo)
            console.log("Aforo máximo alcanzado.");

        return;

    }
    catch (err) {
        console.error(err)
        return res.boom.badImplementation();
    }
}

async function registrarUsuario(req, res, next) {
    try {

        let received = req.body;

        logger(req.ip, "registro", JSON.stringify(received));

        if (!received.name || !received.password) {
            res.boom.badRequest("Faltan datos!")
            return;
        }

        let usrPrev = await User.findAndCountAll({ where: { name: received.name } });


        if (usrPrev.count) {
            res.boom.badRequest("Ya existe un usuario con ese nombre.")
            return;
        }

        const user = await User.create(
            {
                name: received.name,
                password: received.password,
                x_actual: 9,
                y_actual: 9,
                x_destino: 9,
                y_destino: 9,
                logged: false,
            });



        // Mandamos al cliente el usuario registrado.
        res.json(user);
        console.log("Usuario", user.id, ":", user.name, "registrado.");

        return;

    }
    catch (err) {
        console.error(err)
        return res.boom.badImplementation();
    }
}

async function editarUsuario(req, res, next) {
    try {

        let received = req.body;

        logger(req.ip, "editar", JSON.stringify({ userid: req.params.id, requestbody: received }));

        if (!received.name || !received.password) {
            res.boom.badRequest("Faltan datos!")
            return;
        }

        let usrPrev = await User.findOne({ where: { name: received.name } });

        if (usrPrev && usrPrev.id != req.params.id) {
            res.boom.badRequest("Ya existe un usuario con ese nombre.")
            return;
        }

        let user = await User.findByPk(req.params.id);
        user.name = received.name;
        user.password = received.password;
        await user.save();

        // Mandamos al cliente el usuario actualizado.
        res.json(user);

        console.log("Usuario", user.id, ":", received.name, "actualizado.", JSON.parse(JSON.stringify(user)));

        return;

    }
    catch (err) {
        console.error(err)
        return res.boom.badImplementation();
    }
}

async function desuatenticarUsuario(req, res, next) {
    try {

        let aforo = await Aforo.findAll({
            limit: 1,
            order: [['createdAt', 'DESC']]
        });

        aforo = aforo[0].aforo;

        aforoActual--;

        let usr = await User.findByPk(req.params.id);
        logger(req.ip, "desautenticar", JSON.stringify({ user: usr }));

        usr.logged = false;
        usr.x_actual = 9;
        usr.y_actual = 9;
        usr.y_destino = 9;
        usr.x_destino = 9;
        usr.save();

        // Emitimos a usuario actual la desconexion.
        res.json(usr.id);

        console.log("Desautenticado:", usr.name, " | Aforo:", aforoActual, "/", aforo);

        return;

    }
    catch (err) {
        console.error(err)
        return res.boom.badImplementation();
    }
}

// POST localhost:9090/auth
router.post('/auth', autenticarUsuario);

// POST localhost:9090/register
router.post('/register', registrarUsuario);

// PUT localhost:9090/edit/23
router.put('/edit/:id/', editarUsuario);

// GET localhost:9090/23
router.get('/logoff/:id', desuatenticarUsuario);


module.exports = router