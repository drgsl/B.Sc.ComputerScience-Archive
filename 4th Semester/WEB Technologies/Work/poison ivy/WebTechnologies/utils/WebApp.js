const http = require('http')
const { port } = require('./constants')
class WebApp {
  constructor (port, router) {
    this.port = port
    this.router = router
  }

  use () {

  }

  listen () {
    var app = this
    var server = http.createServer(function (req, res) {
      app.router.route(req, res)
    //  res.end()
    })
    server.listen(process.env.PORT||port)
    console.log(`app running on PORT: ${port}`)
  }
}

module.exports = { WebApp }
