const { ObjectID } = require('bson');
const mongoose = require('mongoose')
const Schema = new mongoose.Schema({
  username: String,
  id_user: String,
  password: String,
  is_admin: String,
  email: String,
});
const user = mongoose.model("users", Schema);
module.exports = user;
