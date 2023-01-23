/**
 * User model.
 */
const Sequelize = require('sequelize');
const sequelize = require('../config/bd-connector');

const User = sequelize.define('user', {
    id: {
        type: Sequelize.INTEGER,
        autoIncrement: true,
        allowNull: false,
        primaryKey: true
    },
    name: {
        type: Sequelize.STRING,
        allowNull: false,
        unique: true
    },
    password: {
        type: Sequelize.STRING,
        allowNull: false
    },
    x_actual: {
        type: Sequelize.INTEGER,
        allowNull: false
    },
    y_actual: {
        type: Sequelize.INTEGER,
        allowNull: false
    },
    x_destino: {
        type: Sequelize.INTEGER,
        allowNull: true
    },
    y_destino: {
        type: Sequelize.INTEGER,
        allowNull: true
    },
    logged: {
        type: Sequelize.BOOLEAN,
        defaultValue: false
    }
});

module.exports = User;