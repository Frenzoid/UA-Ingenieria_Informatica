/**
 * User model.
 */
const Sequelize = require('sequelize');
const sequelize = require('../config/bd-connector');

const Aforo = sequelize.define('aforo', {
    aforo: {
        type: Sequelize.INTEGER,
        allowNull: false,
        primaryKey: true
    },
});

module.exports = Aforo;