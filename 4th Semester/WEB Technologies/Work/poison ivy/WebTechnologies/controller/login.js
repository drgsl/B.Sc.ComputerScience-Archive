const fs = require('fs')
const { getUserByEmail } = require('../controller/users')
const { parseCookie } = require("../utils")

let randomString = () => {
    var output = "";
    var options = "1234567890FABCDEF";
    for (i = 0; i < 40; i++) {
        output += options[Math.floor(Math.random() * 100000) % options.length];
    }
    return output;
}

let loginHTML = ""
let loginCSS = ""
let loginJS = ""

function getLogout(req, res) {
    res.statusCode = 200
        //fs.createReadStream('index.html').pipe(res)
    var data = fs.readFileSync('./views/login.html', 'utf8');

    var loggedinstatus = "Login"


    data = data.replace("{{loggedin}}", `<li><a class="nav-link" href="login.html">${loggedinstatus}</a></li>`)


    res.setHeader('Set-Cookie', 'token=;path=/')


    res.write(data)
    res.end()
}

function getLoginHTML(req, res) {

    res.statusCode = 200
        //fs.createReadStream('index.html').pipe(res)
    var data = fs.readFileSync('./views/login.html', 'utf8');
    console.log(parseCookie(req["headers"]["cookie"]));
    if(req["headers"]["cookie"]== undefined)req["headers"]["cookie"]="";
    if (parseCookie(req["headers"]["cookie"])["token"] === "") {
        res.setHeader('Content-Type', 'text/html')
        var loggedinstatus = "Login"

        data = data.replace("{{loggedin}}", `<li><a class="nav-link" href="login.html">${loggedinstatus}</a></li>`)
    } else {
        var data = fs.readFileSync('./views/search.html', 'utf8');

        var loggedinstatus = "Logout"


        data = data.replace("{{loggedin}}", `<li><a class="nav-link" href="Myaccount.html">Account</a></li>
      <li><a class="nav-link" href="logout">${loggedinstatus}</a></li>`)


        //res.setHeader('Content-Type', 'text/html')



    }


    res.write(data)
    res.end()
}


function exempleAPI(req, res) {
    res.statusCode = 200
    res.setHeader('Content-Type', 'application/json')
    res.write(JSON.stringify({ success: true, message: 'example ran successfully' }))
    res.end()
}



function getLoginCSS1(req, res) {
    var data2 = fs.readFileSync('./views/styles/login.css', 'utf8');
    res.setHeader('Content-Type', 'text/css')
    res.write(data2)
    res.end()
}

function getLoginCSS2(req, res) {
    var data2 = fs.readFileSync('./views/styles/nav.css', 'utf8');
    res.setHeader('Content-Type', 'text/css')
    res.write(data2)
    res.end()
}


function getLoginJS(req, res) {
    var data2 = fs.readFileSync('./views/scripts/nav.js', 'utf8');
    res.setHeader('Content-Type', 'text/javascript')
    res.write(data2)
    res.end()
}

async function login(req, res) {
    let data = '';
    req.on('data', chunk => {
        data += chunk;
    })
    req.on('end', async() => {
        req.body = JSON.parse(data);
        const email = req.body["email"];
        const password = req.body["password"];
        res.setHeader('Content-Type', 'application/json')


        const token = randomString();

        const user = await getUserByEmail(email);

        if (user !== undefined) {
            console.log(password)
            console.log(user)
            if (password === user.password) {
                console.log("Ne am logat");
                if (user["is_admin"] === "1") {
                    res.setHeader('Set-Cookie', "admin=\"1\";path=/");
                } else {
                    res.setHeader('Set-Cookie', "admin=\"0\";path=/");
                }



                res.end(JSON.stringify({ token: token }));


            } else {
                res.statusCode = 401;
                res.end(JSON.stringify({ token: "" }));

            }
        } else {
            res.statusCode = 401;
            res.end(JSON.stringify({ token: "" }));

        }
    })
}

module.exports = { login, getLoginHTML, getLoginCSS1, getLoginCSS2, getLoginJS, getLogout }