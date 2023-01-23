/**
 * User model.
 */
const Sequelize = require('sequelize');
const sequelize = require('../config/bd-connector');

const Log = sequelize.define('log', {
    id: {
        type: Sequelize.INTEGER,
        autoIncrement: true,
        allowNull: false,
        primaryKey: true
    },
    address: {
        type: Sequelize.STRING,
        allowNull: false,
    },
    action: {
        type: Sequelize.STRING,
        allowNull: false,
    },
    data: {
        type: Sequelize.STRING,
        allowNull: false,
    },
});

module.exports = Log;