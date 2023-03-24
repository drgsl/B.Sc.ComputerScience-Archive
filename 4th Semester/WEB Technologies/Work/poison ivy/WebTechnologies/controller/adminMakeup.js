const fs = require('fs')
const { parseCookie } = require("../utils")



function getAdminMakeupHTML(req, res) {

    res.statusCode = 200
    var data = fs.readFileSync('./views/admin-makeup.html', 'utf8');
     //res.setHeader('Content-Type', 'text/html')
     if(req["headers"]["cookie"]== undefined)req["headers"]["cookie"]="";
    if (parseCookie(req["headers"]["cookie"])["token"] === "") {
        var loggedinstatus = "Login"
        data = data.replace("{{loggedin}}", `<li><a class="nav-link" href="login.html">${loggedinstatus}</a></li>`)
    } else {
        res.setHeader("Set-Cookie", 'token=;path=/')
        var loggedinstatus = "Logout"
        data = data.replace("{{loggedin}}", `<li><a class="nav-link" href="Myaccount.html">Account</a></li>
      <li><a class="nav-link" href="logout">${loggedinstatus}</a></li>`)
    }


    res.write(data)
    res.end()

    console.log(fs)
}

function exempleAPI(req, res) {
    res.statusCode = 200
    res.setHeader('Content-Type', 'application/json')
    res.write(JSON.stringify({ success: true, message: 'example ran successfully' }))
    res.end()
}

function getAdminMakeupCSS1(req, res) {
    var data2 = fs.readFileSync('./views/styles/admin-makeup.css', 'utf8');
    res.setHeader('Content-Type', 'text/css')
    res.write(data2)
    res.end()
}

function getAdminMakeupCSS2(req, res) {
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

function getAdminMakeupJS1(req, res) {
    var data2 = fs.readFileSync('./views/scripts/nav.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data2)
    res.end()
}

function getAdminMakeupJS2(req, res) {
    var data2 = fs.readFileSync('./views/scripts/adminMakeup.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data2)
    res.end()
}
module.exports = { getAdminMakeupHTML, getAdminMakeupCSS1, getAdminMakeupCSS2, getAdminMakeupJS1, getAdminMakeupJS2, exempleAPI }