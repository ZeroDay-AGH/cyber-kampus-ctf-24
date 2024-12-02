const axios = require('axios');
const qs = require('qs');
const db = require('../db/database');
const verifyToken = require('../middleware/authMiddleware');

module.exports = (app) => {
  app.post('/spells', verifyToken, (req, res) => {
    const { incantation, spell_type } = req.body;

    try {
        const username = req.username;

        const query = `INSERT INTO spells (magician, incantation, spell_type) VALUES (?, ?, ?)`;
        db.run(query, [username, incantation, spell_type], function(err) {
            if (err) {
                console.log(err);
                return res.status(500).json({ error: 'The Great Librarian can\'t save your spell'});
            }
            res.status(201).json({ message: 'Your spell has been accepted', spellId: this.lastID});
        });
    } catch (error) {
        res.status(401).json({ error: 'Are you a real wizard?' });
    }
  });

  app.get('/:magician/spells', verifyToken, (req, res) => {
    const { magician } = req.params;
    const username = req.username;

    if (username !== 'archwizard' && username !== magician) {
        return res.status(403).json({ error: 'You\'re not allowed to access this sacred knowledge' });
    }

    const query = `SELECT * FROM spells WHERE magician = ?`;
    db.all(query, [magician], (err, rows) => {
        if (err) {
            return res.status(500).json({ error: 'Failed to retrieve spells' });
        }

        res.render('spells', { magician, spells: rows });
    });
  });

  app.get('/', (req, res) => {
    // Let the magic happen
    const spell = req.query.spell;
    if (spell) {
        res.status(301).location(spell);
        return res.send('Abracadabra');
    }
    res.status(301).location('/login');
    return res.send('OK');
  });

  app.get('/:magician/spells/share', verifyToken, (req, res) => {
    const { magician } = req.params;
    const username = req.username;

    const isAlphanumeric = /^[A-Za-z0-9_]+$/.test(magician);

    if (!isAlphanumeric) {
        return res.status(400).json({ error: 'Invalid magician name. Only alphanumeric characters are allowed.' });
    }

    if (username !== 'archwizard' && username !== magician) {
        return res.status(403).json({ error: 'You\'re not allowed to access this sacred knowledge' });
    }
    axios.post('http://bot:3000/', qs.stringify({
        url: `http://archmage_app:3000/${magician}/spells`
    }))
    .then(response => {
        res.status(200).json({ message: 'Spell shared successfully', data: response.data });
    })
    .catch(error => {
        res.status(500).json({ error: 'Failed to share the spell' });
    });
  });
};