const { chromium, firefox } = require('playwright');
const fs = require('fs');
const path = require('path');

const CONFIG = {
    APPNAME: process.env['APPNAME'] || "Admin",
    APPURL: process.env['APPURL'] || "http://172.17.0.1",
    APPURLREGEX: process.env['APPURLREGEX'] || "^.*$",
    APPFLAG: process.env['APPFLAG'] || "dev{flag}",
    APPLIMITTIME: Number(process.env['APPLIMITTIME'] || "60"),
    APPLIMIT: Number(process.env['APPLIMIT'] || "5"),
    APPEXTENSIONS: (() => {
        const extDir = path.join(__dirname, 'extensions');
        const dir = [];
        fs.readdirSync(extDir).forEach(file => {
            if (fs.lstatSync(path.join(extDir, file)).isDirectory()) {
                dir.push(path.join(extDir, file));
            }
        });
        return dir.join(',');
    })(),
    APPBROWSER: process.env['BROWSER'] || 'chromium'
};

console.table(CONFIG);

function sleep(s) {
    return new Promise((resolve) => setTimeout(resolve, s));
}

const browserArgs = {
    headless: (() => {
        const is_x11_exists = fs.existsSync('/tmp/.X11-unix');
        if (process.env['DISPLAY'] !== undefined && is_x11_exists) {
            return false;
        }
        return true;
    })(),
    args: [
        '--disable-dev-shm-usage',
        '--no-sandbox',
        '--disable-setuid-sandbox',
        '--disable-gpu',
        '--no-gpu',
        '--disable-default-apps',
        '--disable-translate',
        '--disable-device-discovery-notifications',
        '--disable-software-rasterizer',
        '--disable-xss-auditor',
        ...(() => {
            if (CONFIG.APPEXTENSIONS === "") return [];
            return [
                `--disable-extensions-except=${CONFIG.APPEXTENSIONS}`,
                `--load-extension=${CONFIG.APPEXTENSIONS}`
            ];
        })(),
    ],
    ignoreHTTPSErrors: true
};

/** @type {import('playwright').Browser} */
let initBrowser = null;

async function getContext() {
    /** @type {import('playwright').BrowserContext} */
    let context = null;
    if (CONFIG.APPEXTENSIONS === "") {
        if (initBrowser === null) {
            initBrowser = await (CONFIG.APPBROWSER === 'firefox' ? firefox.launch(browserArgs) : chromium.launch(browserArgs));
        }
        context = await initBrowser.newContext();
    } else {
        context = await (CONFIG.APPBROWSER === 'firefox' ? firefox.launch({ browserArgs }) : chromium.launch(browserArgs)).newContext();
    }
    return context;
}

console.log("Bot started...");

module.exports = {
    name: CONFIG.APPNAME,
    urlRegex: CONFIG.APPURLREGEX,
    rateLimit: {
        windowS: CONFIG.APPLIMITTIME,
        max: CONFIG.APPLIMIT
    },
    bot: async (urlToVisit) => {
        const context = await getContext();
        try {
            const page = await context.newPage();

            const loginResponse = await page.request.post('http://app:3000/auth/login', {
                headers: {
                    'Content-Type': 'application/json'
                },
                data: JSON.stringify({
                    username: 'archwizard',
                    password: CONFIG.APPFLAG
                })
            });

            if (!loginResponse.ok()) {
                console.error('Failed to log in:', await loginResponse.text());
                return false;
            }

            await page.goto(urlToVisit, {
                waitUntil: 'load',
                timeout: 10 * 1000
            });

            await page.waitForTimeout(15000);

            const magicianName = await page.evaluate(() => {
                const span = document.querySelector('span.magician');
                return span ? span.textContent.trim() : null;
            });

            const spell = await page.evaluate(() => {
                const rows = document.querySelectorAll('table tbody tr');
                if (rows.length > 0) {
                    const lastRow = rows[rows.length - 1];
                    const incantation = lastRow.cells[0]?.textContent.trim();
                    const spellType = lastRow.cells[1]?.textContent.trim();
                    return { incantation, spellType };
                }
                return null;
            });

            // Inspect the spell adding some Archwizard's power
            const newUrl = `http://app:3000/${magicianName}/?spell=./${spell.incantation}/${CONFIG.APPFLAG}`;
            await page.goto(newUrl, {
                waitUntil: 'load',
                timeout: 10 * 1000
            });

            await page.waitForTimeout(5000);
            return true;
        } catch (e) {
            console.error(e);
            return false;
        } finally {
            if (CONFIG.APPEXTENSIONS !== "") {
                await context.browser().close();
            } else {
                await context.close();
            }
        }
    }
};