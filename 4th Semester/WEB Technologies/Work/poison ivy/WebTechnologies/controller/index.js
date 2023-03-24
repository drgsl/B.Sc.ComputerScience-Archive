const fs = require('fs')
const { parseCookie } = require("../utils")

let indexHTML = '' ///codul html in string
let indexCSS = '' ///codul css in string
let indexJS = '' ///codul js in string


let id_counter = {};


function getIndexHTML(req, res) {

    res.statusCode = 200
        //fs.createReadStream('index.html').pipe(res)
    var data = fs.readFileSync('./views/index.html', 'utf8');
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
}

function getProducts(req, res) {

}

function exempleAPI(req, res) {
    res.statusCode = 200
    res.setHeader('Content-Type', 'application/json')
    res.write(JSON.stringify({ success: true, message: 'example ran successfully' }))
    res.end()
}

function getIndexHTML2(req, res) {
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

function getIndexCSS1(req, res) {
    var data2 = fs.readFileSync('./views/styles/index.css', 'utf8');
    res.setHeader('Content-Type', 'text/css')
    res.write(data2)
    res.end()

}

function getIndexCSS2(req, res) {
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

function getIndexJS(req, res) {
    var data2 = fs.readFileSync('./views/scripts/nav.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data2)
    res.end()
}

function getIndexJS2(req, res) {
    var data2 = fs.readFileSync('./views/scripts/contact.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data2)
    res.end()
}

function counter(req, res) {
    let body = "";

    req.on("data", (data) => {
        body += data;
    })
    req.on("end", () => {
        req.body = JSON.parse(body);
        const id = req.body["id"];
        if(id_counter[id] === undefined) {
            id_counter[id] = 1;
        }
        else {
            id_counter[id] += 1;
        }
        res.end()
    })
}

function getCounts(req, res) {
    res.setHeader('Content-Type', 'application/json')
    res.end(JSON.stringify(id_counter));
}

module.exports = { getIndexHTML, getIndexCSS1, getIndexCSS2, getIndexJS, exempleAPI, getIndexJS2, counter, getCounts }