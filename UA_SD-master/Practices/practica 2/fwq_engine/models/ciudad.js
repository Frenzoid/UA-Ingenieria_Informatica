/**
 * User model.
 */
const Sequelize = require('sequelize');
const sequelize = require('../config/bd-connector');

const Ciudad = sequelize.define('ciudad', {
    id: {
        type: Sequelize.INTEGER,
        autoIncrement: true,
        allowNull: false,
        primaryKey: true
    },
    nombre: {
        type: Sequelize.STRING,
        allowNull: false,
    },
    temperatura: {
        type: Sequelize.FLOAT,
        allowNull: true,
    },
});

module.exports = Ciudad;