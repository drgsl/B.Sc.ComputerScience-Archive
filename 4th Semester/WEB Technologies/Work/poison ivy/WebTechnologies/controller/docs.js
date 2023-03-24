const fs = require('fs')

function getDocHTML(req, res) {

    res.statusCode = 200
    var data = fs.readFileSync('./views/doc.html', 'utf8');
    res.setHeader('Content-Type', 'text/html')
    res.write(data)
    res.end()

    console.log(fs)
}

function getProducts(req, res) {

}

function exempleAPI(req, res) {
    res.statusCode = 200
    res.setHeader('Content-Type', 'application/json')
    res.write(JSON.stringify({ success: true, message: 'example ran successfully' }))
    res.end()
}

function getDocCSS(req, res) {
    var data2 = fs.readFileSync('./views/styles/doc.css', 'utf8');
    res.setHeader('Content-Type', 'text/css')
    res.write(data2)
    res.end()

}


module.exports = { getDocHTML, getDocCSS, exempleAPI }