const db = require('./database');

function addUser(username, password, cb) {
    const sql = 'INSERT INTO user (username, password) VALUES (?, ?)';
    db.run(sql, [username, password], function (err) {
        if (err) return cb(err);
        cb(null, {id: this.lastID });
    })
}

function getUser(username, cb) {
    const sql = 'SELECT * FROM user WHERE username = ?';
    db.get(sql, [username], (err, row) => {
        if (err) return cb(err);
        cb(null, row);
    })
}

module.exports = { addUser, getUser };