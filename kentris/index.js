const express = require('express');
const redis = require('redis');

const app = express();
const port = 3000;

const mem = redis.createClient();
mem.on('error', (err) => {
    console.log(`REDIS ERROR: ${err}`);
});

/* access session by id. */
app.get('/session/:id', async(req, res) => {
    await mem.connect();
    await mem.set('e', 'true');
    const v = await mem.get('e')
});

/* update session by id. */
app.put('/session/:id', async(req, res) => {
    await mem.connect();
});

/* create a new session, returns id. */
app.get('/newsession', async(req, res) => {
    await mem.connect();
    const id = Math.floor((Math.random()*10000)).toString();
    res.send(id);
});

/* End session. */
app.delete('/endsession/:id', async(req, res) => {
    await mem.connect();
});

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`);
});
