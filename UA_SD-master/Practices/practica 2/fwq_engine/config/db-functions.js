const Aforo = require('../models/aforo');
const Atraccion = require('../models/atraccion');
const Ciudad = require('../models/ciudad');

async function runDBPreparations() {

    // Sync all models.
    await Aforo.sync({ force: true });
    await Aforo.create({ aforo: Number(process.env.AFORO || process.argv[2]) });
    console.log("Aforo máximo setteado:", Number(process.env.AFORO || process.argv[2]));

    await Atraccion.sync({ force: true });
    console.log("Tabla de atracciones creadas / limpiadas");


    await Ciudad.sync({ force: true });
    console.log("Tabla de las ciudades creadas / limpiadas");
    await Ciudad.create({nombre: "Alicante"})
    await Ciudad.create({nombre: "Mountain View"})
    await Ciudad.create({nombre: "London"})
    await Ciudad.create({nombre: "Moscow"})
}

module.exports = runDBPreparations;