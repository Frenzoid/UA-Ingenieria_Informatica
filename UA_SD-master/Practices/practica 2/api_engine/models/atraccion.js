/**
 * User model.
 */
const Sequelize = require('sequelize');
const sequelize = require('../config/bd-connector');

const Atraccion = sequelize.define('atraccion', {
    id: {
        type: Sequelize.INTEGER,
        allowNull: false,
        primaryKey: true
    },
    picture: {
        type: Sequelize.STRING,
        allowNull: true,
        unique: true
    },
    coord_x: {
        type: Sequelize.STRING,
        allowNull: false
    },
    coord_y: {
        type: Sequelize.INTEGER,
        allowNull: false
    },
    time: {
        type: Sequelize.INTEGER,
        allowNull: false
    },
});

module.exports = Atraccion;