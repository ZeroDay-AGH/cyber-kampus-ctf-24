const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');
const { addUser, getUser } = require('../db/userModel');
const { secretKey } = require('../config');

module.exports = (app) => {
  app.post('/auth/register', async (req, res) => {
    try {
      const { username, password } = req.body;
      if (!username || !/^[A-Za-z0-9_]+$/.test(username)) {
        return res.status(400).json({ error: 'Invalid username. It must be non-empty and contain only letters, numbers, and underscores.' });
      }

      if (!password || password.length < 6) {
        return res.status(400).json({
          error: 'Password must be at least 6 characters long.'
        });
      }

      if (username === password) {
        return res.status(400).json({
          error: 'Username and password cannot be the same.',
        });
      }
      
      const hash = await bcrypt.hash(password, 10);

      addUser(username, hash, (err, result) => {
        if (err) {
          return res.status(500).json({ error: 'Registration failed' });
        }
        res.status(201).json({ message: 'Registration successful', userId: result.id });
      });
    } catch (error) {
      res.status(500).json({ error: 'Registration failed' });
    }
  });

  app.post('/auth/login', (req, res) => {
    const { username, password } = req.body;

    getUser(username, async (err, user) => {
      if (err || !user) {
        return res.status(404).json({ error: 'No user matching provided credentials' });
      }

      const pwdCorrect = await bcrypt.compare(password, user.password);
      if (!pwdCorrect) {
        return res.status(404).json({ error: 'No user matching provided credentials' });
      }

      const token = jwt.sign({ username: user.username }, secretKey, { expiresIn: '1h' });

      res.cookie('token', token, {
        httpOnly: true,
        maxAge: 3600000
      });

      res.cookie('magician', username, {
        maxAge: 3600000
      });

      res.status(200).json({ message: 'Login successful' });
    });
  });
};