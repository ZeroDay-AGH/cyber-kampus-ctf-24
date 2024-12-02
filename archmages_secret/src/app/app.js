const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const cookieParser = require('cookie-parser');
const viewRoutes = require('./routes/views');
const authRoutes = require('./routes/auth');
const magicRoutes = require('./routes/magic');
const { archwizardPassword, archwizardUsername } = require('./config');
const { addUser } = require('./db/userModel');
const bcrypt = require('bcrypt');



app.set('view engine', 'ejs');

app.use(express.static('public'));

app.use(bodyParser.json());
app.use(cookieParser());

viewRoutes(app);
authRoutes(app);
magicRoutes(app);

const PORT = 3000;

async function startServer() {
    try {
        const archwizardHash = await bcrypt.hash(archwizardPassword, 10);

        addUser(archwizardUsername, archwizardHash, (err, result) => {
            if (err) {
                console.error('Registration failed:', err);
                return;
            }
        });
    } catch (error) {
        console.error('Error adding user:', error);
    }
    app.listen(PORT, () => {
        console.log(`Server running on http://localhost:${PORT}`);
    });
}

startServer();