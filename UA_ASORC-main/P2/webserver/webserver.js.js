const express = require('express')
const { Sequelize, DataTypes } = require('sequelize');

const app = express()
const port = 3000

const sequelize = new Sequelize('oracle://frenzoid:frenzoid@localhost:1521/XEPDB1')

const User = sequelize.define('User', {
  nombre: DataTypes.STRING,
  apellido: DataTypes.STRING,
  id : {
    type: DataTypes.INTEGER,
    primaryKey: true,
    autoIncrement: true,
 }
});

async function start() {
  try {
    await sequelize.authenticate();
    console.log('Connection has been established successfully.');
    await User.sync({force: true})
    await User.create({nombre: "Elvi Mihai", apellido: "Sabau Sabau"})
  } catch (error) {
    console.error('Unable to connect to the database:', error);
  }
}

app.get('/', async (req, res) => {
  const users = await User.findAll();
  res.send(users)
})

app.listen(port, async () => {
  await start();
  console.log(`App ready, listening on port ${port}`)
})
