const mongoose = require('mongoose')
const Schema = new mongoose.Schema({
 firstName: String,
  lastName: String,
  country: String,
  subject:String,
});
const feedbacks = mongoose.model("feedbacks", Schema);
module.exports = feedbacks;
