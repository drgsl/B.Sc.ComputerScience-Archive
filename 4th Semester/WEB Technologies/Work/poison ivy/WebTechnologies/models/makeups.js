const { ObjectId } = require('bson');
const mongoose = require('mongoose')
const Schema = new mongoose.Schema({
  name: String,
  image_path: String,
  url: String,
  descriere: String,
  tags: [String],
  products:[ObjectId],
});
const makeups = mongoose.model("makeups", Schema);
module.exports = makeups;