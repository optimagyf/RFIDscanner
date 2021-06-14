const express = require("express");
const app = express();

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.post("/postplain", (req, res) => {
  console.log("Got body:", req.body);
  res.sendStatus(200);
});

app.listen(3000, () => {
  console.log("Started on PORT 3000");
});
