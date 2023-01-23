const Log = require("./models/log");

let logger = async (ip, accion, datos) => {
    try {
        await Log.create({
            address: ip,
            action: accion,
            data: datos
        });
    } catch (err) {
        console.error(err);
    }
}

module.exports = logger;