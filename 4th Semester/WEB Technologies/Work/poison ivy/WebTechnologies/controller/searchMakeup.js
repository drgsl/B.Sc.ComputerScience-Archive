const fs = require('fs')

let searchHTML = ""
let searchCSS = ""
let serachJS = ""

const { parseCookie } = require("../utils")


function getSearchMakeupHTML(req, res) {

    res.statusCode = 200

    //fs.createReadStream('index.html').pipe(res)
    var data = fs.readFileSync('./views/makeup.html', 'utf8');
    if(req["headers"]["cookie"]== undefined)req["headers"]["cookie"]="";
    if (parseCookie(req["headers"]["cookie"])["token"] === "") {
        res.setHeader('Content-Type', 'text/html')
            //res.setHeader('Set-Cookie', token=${token};path=/)
        var loggedinstatus = "Login"

        data = data.replace("{{loggedin}}", `<li><a class="nav-link" href="login.html">${loggedinstatus}</a></li>`)
    } else {

        var loggedinstatus = "Logout"

        data = data.replace("{{loggedin}}", `<li><a class="nav-link" href="Myaccount.html">Account</a></li>
      <li><a class="nav-link" href="logout">${loggedinstatus}</a></li>`)


        //res.setHeader('Content-Type', 'text/html')



    }


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

function getSearchMakeupHTML2(req, res) {
    try {

        res.statusCode = 200
        res.setHeader('Content-Type', 'text/html')
        res.write(indexHTML)
        res.end()
    } catch (e) {
        console.log(e)
        res.statusCode = 500
        res.setHeader('Content-Type', 'text/html')
        res.write('Internal server error')
        res.end()
    }
}

function getSearchMakeupCSS1(req, res) {
    var data2 = fs.readFileSync('./views/styles/makeup.css', 'utf8');
    res.setHeader('Content-Type', 'text/css')
    res.write(data2)
    res.end()
}

function getSearchMakeupCSS2(req, res) {
    var data2 = fs.readFileSync('./views/styles/nav.css', 'utf8');
    res.setHeader('Content-Type', 'text/css')
    res.write(data2)
    res.end()
}

function getNavbarCSS(req, res) {
    try {
        res.statusCode = 200
        res.setHeader('Content-Type', 'text/css')
        res.write(navBarCSS)
        res.end()
    } catch (e) {
        console.log(e)
        res.statusCode = 500
        res.setHeader('Content-Type', 'text/css')
        res.write('Internal server error')
        res.end()
    }
}

function getSearchMakeupJS1(req, res) {
    var data2 = fs.readFileSync('./views/scripts/nav.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data2)
    res.end()
}

function getSearchMakeupJS2(req, res) {
    var data2 = fs.readFileSync('./views/scripts/searchMakeup.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data2)
    res.end()
}

module.exports = { getSearchMakeupHTML, getSearchMakeupCSS1, getSearchMakeupCSS2, getSearchMakeupJS1, getSearchMakeupJS2, exempleAPI }