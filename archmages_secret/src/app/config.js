const crypto = require('crypto');
const secretKey = crypto.randomBytes(64).toString('hex');

const archwizardUsername = 'archwizard';
const archwizardPassword = process.env['APPFLAG'] || "dev{flag}";

module.exports = {
    secretKey,
    archwizardUsername,
    archwizardPassword
};