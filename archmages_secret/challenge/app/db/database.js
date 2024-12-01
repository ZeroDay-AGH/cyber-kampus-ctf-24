const sqlite3 = require('sqlite3');

const db = new sqlite3.Database('./users.db', (err) => {
    if (err) {
        console.error('Error opening database ' + err.message);
    } else {
        console.log('Connected to the DB');

        db.run(`CREATE TABLE IF NOT EXISTS user (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE,
            password TEXT
        )`, (err) => {
            if (err) {
                console.error('Error creating user table ' + err.message);
            }
        });

        db.run(`CREATE TABLE IF NOT EXISTS spells (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            magician TEXT NOT NULL,
            incantation TEXT NOT NULL,
            spell_type TEXT NOT NULL
        )`, (err) => {
            if (err) {
                console.error('Error creating spells table ' + err.message);
            }
        });
    }
});

module.exports = db;