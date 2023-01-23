/**
 * User model.
 */
const Sequelize = require('sequelize');
const sequelize = require('../config/bd-connector');

const bcrypt = require('bcrypt');

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

// Before each insert or update..
User.beforeCreate(async (user) => {
    const salt = bcrypt.genSaltSync(10);
    user.password = bcrypt.hashSync(user.password, salt);
});

User.beforeUpdate(async (user) => {
    if (!((await User.findByPk(user.id)).password == user.password)) {
        const salt = bcrypt.genSaltSync(10);
        user.password = bcrypt.hashSync(user.password, salt);
    }
});


// Custom class method.
User.checkPassword = (password, hashedPassword) => {
    return bcrypt.compareSync(password, hashedPassword);
}

module.exports = User;