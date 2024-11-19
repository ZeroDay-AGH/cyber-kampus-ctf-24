import express from 'express';
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import fs from 'fs';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

const app = express();

app.use(express.json());

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/src/index.html');
});

app.get('/robots.txt', (req, res) => {
    res.send('User-agent: *\nDisallow: /passes.txt');
});

app.get('/passes.txt', (req, res) => {
    res.send('In case you forgot you passes, here they are:\nhpotter@mmin.gov.uk\n3d2QGYu2V8DLo)HhyHmzEQzWaoH');
});

app.get('/images/:image', (req, res) => {
    const image = req.params.image;
    res.sendFile(__dirname + '/src/images/' + image);
});

app.post('/login', (req, res) => {
    const acceptLanguage = req.get('Accept-Language');

    const userAgent = req.get('User-Agent');

    const body = req.body;
    const login = body.login;
    const password = body.password;

    const latitude = body.latitude;
    const longitude = body.longitude;
    
    if (latitude > 51 && latitude < 52 && longitude < -0.12 && longitude > -0.13) {
        if (userAgent.includes('owl') || userAgent.includes('Owl')) {
            if (acceptLanguage.includes('en-gb') || acceptLanguage.includes('en-GB')) {
                if (login === 'hpotter@mmin.gov.uk' && password === '3d2QGYu2V8DLo)HhyHmzEQzWaoH') {
                    fs.readFile(__dirname + '/flag.txt', 'utf8', (err, data) => {
                        if (err) {
                            res.status(500).send('Error reading file');
                            return;
                        }
                        res.send(data);
                    });
                } else {
                    res.status(401).send('Invalid login credentials');
                }
            } else {
                res.status(401).send('We demand thy correspondence be written in proper british English');
            }
        } else {
            res.status(403).send('We only accept requests delivered by owls');
        }
    } else {
        res.status(400).send('We only accept correspondence in our headquarters in London'); 
    }
});

app.listen(3000, () => {
    console.log('Server is running on port 3000');
    console.log('http://localhost:3000');
});
