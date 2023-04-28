const express = require('express');
const redis = require('redis');

const app = express();
const port = 3000;

app.get('/', (req, res) => {
    res.send('KENTRIS');
});

/* access session by id. */
app.get('/session/:id', (req, res) => {
});

/* update session by id. */
app.put('/session/:id', (req, res) => {
});

/* create a new session, returns id. */
app.post('/newsession', (req, res) => {
});

/* End session. */
app.delete('/endsession/:id', (req, res) => {
});

app.listen(port, () => {
    console.log(`Example app listening on port ${port}`);
});
