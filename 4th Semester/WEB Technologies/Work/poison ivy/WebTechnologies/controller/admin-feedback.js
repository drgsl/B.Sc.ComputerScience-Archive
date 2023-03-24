const fs = require('fs')
const { parseCookie } = require("../utils")


function getAdminFeedbackHTML(req, res) {

    res.statusCode = 200
    var data = fs.readFileSync('./views/admin-feedback.html', 'utf8');
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

function getAdminFeedbackCSS1(req, res) {
    var data2 = fs.readFileSync('./views/styles/admin-feedback.css', 'utf8');
    res.setHeader('Content-Type', 'text/css')
    res.write(data2)
    res.end()
}

function getAdminFeedbackCSS2(req, res) {
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

function getAdminFeedbackJS(req, res) {
    var data2 = fs.readFileSync('./views/scripts/nav.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data2)
    res.end()
}

function getAdminFeedbackJS2(req, res) {
    var data3 = fs.readFileSync('./views/scripts/adminFeedback.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data3)
    res.end()
}

module.exports = { getAdminFeedbackHTML, getAdminFeedbackCSS1, getAdminFeedbackCSS2, getAdminFeedbackJS, exempleAPI, getAdminFeedbackJS2 }