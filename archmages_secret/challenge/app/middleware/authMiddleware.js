const jwt = require('jsonwebtoken');
const { secretKey, archwizardPassword } = require('../config');

function verifyToken(req, res, next) {
    const token = req.cookies.token;
    if (!token) return res.status(401).json({ error: 'Access token missing' });

    try {
        const decoded = jwt.verify(token, secretKey);
        req.username = decoded.username;
        next();
    } catch (error) {
        res.status(401).json({ error: 'Invalid token' });
    }
}

module.exports = verifyToken;