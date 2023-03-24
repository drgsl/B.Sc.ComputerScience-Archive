const mongoose = require('mongoose')

const url ='mongodb+srv://TWuser:totTWuser@clusterdb.k4vzb.mongodb.net/ivyDB?retryWrites=true&w=majority';

const connectionParams={
    useNewUrlParser: true,
    useCreateIndex: true,
    useUnifiedTopology: true
}

mongoose.connect(url,connectionParams)
  .then (()=>console.log("Connection establish"))
  .catch(()=>console.log("Connection error"))
