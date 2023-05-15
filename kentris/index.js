/*
    * Kentris main file
    *
    * AUTHOR: Jack Davidson
    *
    */

const express = require('express');
const redis = require('redis');

const app = express();
const port = 3000;

const mem = redis.createClient();
mem.on('error', (err) => {
    console.log(`REDIS ERROR: ${err}`);
});

/* create a new session, returns id. */
app.get('/asUser/:u', async(req, res) => {
    /* empty list. */
    await mem.set(`kentris:${req.params.u}:clears`, '0');
    await mem.set(`kentris:${req.params.u}:lost`, '0');

    res.send();
});

app.get('/asUser/:u/lose', async(req, res) => {
    await mem.set(`kentris:${req.params.u}:lost`, '1');
    res.send();
});

/* update clears. */
app.get('/asUser/:u/clear', async(req, res) => {
    await mem.incr(`kentris:${req.params.u}:clears`);
    res.send(await mem.get(`kentris:${req.params.u}:clears`));
});

/* pop clears of a user */
app.get('/user/:u/clears', async(req, res) => {
    c = await mem.get(`kentris:${req.params.u}:clears`);
    mem.set(`kentris:${req.params.u}:clears`, '0');
    res.send(c);
});

app.get('/user/:u/lost', async(req, res) => {
    res.send(await mem.get(`kentris:${req.params.u}:lost`));
});

(async () => {
    await mem.connect();
})();

mem.on('ready', () => {
    app.listen(port, () => {
        console.log(`Example app listening on port ${port}`);
    });
});
