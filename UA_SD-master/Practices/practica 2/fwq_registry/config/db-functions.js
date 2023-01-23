const User = require('../models/user');
const Log = require('../models/log');

async function runDBPreparations() {

    // Sync all models.
    await User.sync({ force: false });
    await Log.sync({ force: false });
}

module.exports = runDBPreparations;