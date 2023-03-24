const userModel = require("../models/users");
const url = require('url');
const { parseCookie } = require("../utils")


async function getAllUsers(req, res) {
    res.setHeader("Content-Type", "application/json");
    const queryUser = url.parse(req.url, true).query;
    try {
        const users = await userModel.find({...queryUser });
        console.log(users);
        res.statusCode = 200;

        console.log(queryUser);
        return res.end(JSON.stringify({ success: true, users }));


    } catch (err) {
        console.log(err);
        res.statusCode = 500;
        return res.end(
            JSON.stringify({ success: false, message: "Internal server error" })
        );

    }
}

async function getUserByEmail(userEmail) {
    try {
        const users = await userModel.find({ email: userEmail });
        console.log(users);

        if (users.length == 0) {
            console.log("no user found with that email")
            return undefined;
        } else {
            return users[0];
        }


    } catch (err) {
        console.log(err);
        return undefined;
    }
}

async function createUser(req, res) {
    /* req.body :*/
    let data = '';
    req.on('data', chunk => {
        data += chunk;
    })
    req.on('end', () => {
        req.body = JSON.parse(data);
        /* */
        res.setHeader("Content-Type", "application/json");
        //const queryUser = url.parse(req.url,true).query;
        const user = new userModel(req.body);
        console.log(req.body);
        try {

            user.save((err) => {
                if (err) {
                    console.log(err)
                    res.statusCode = 500
                    res.setHeader('Content-Type', 'application/json')
                    res.write(JSON.stringify({ success: false, message: 'Internal server error' }))
                    res.end()
                } else {
                    res.statusCode = 200
                    res.setHeader('Content-Type', 'application/json')
                    res.write(JSON.stringify({ success: true, message: user }))
                    res.end()
                }
            })
        } catch (e) {
            res.statusCode = 500
            res.setHeader('Content-Type', 'application/json')
            res.write(JSON.stringify({ success: false, message: 'Internal server error!' }))
            res.end()
        }
    })
}
module.exports = { getAllUsers, createUser, getUserByEmail };