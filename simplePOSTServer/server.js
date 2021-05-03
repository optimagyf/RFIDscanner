const express = require("express");
const bodyParser = require("body-parser");
const app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.post('/postplain', (req, res) => {
    console.log('Got body:', req.body);
    res.sendStatus(200);
});

app.listen(3000,() => {
    console.log("Started on PORT 3000");
})
