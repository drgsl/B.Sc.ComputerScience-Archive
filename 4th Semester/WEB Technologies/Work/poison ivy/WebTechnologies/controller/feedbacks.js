const feedbackModel = require("../models/feedbacks");
const url = require('url');
async function getAllFeedbacks(req, res) {
    res.setHeader("Content-Type", "application/json");
    const queryFeedback = url.parse(req.url, true).query;
    try {
        const feedbacks = await feedbackModel.find({...queryFeedback });
        console.log(feedbacks);
        res.statusCode = 200;

        console.log(queryFeedback);
        return res.end(JSON.stringify({ success: true, feedbacks }));


    } catch (err) {
        console.log(err);
        res.statusCode = 500;
        return res.end(
            JSON.stringify({ success: false, message: "Internal server error" })
        );

    }
}
async function createFeedback(req, res) {
    /* req.body :*/
    let data = '';
    req.on('data', chunk => {
        data += chunk;
    })
    req.on('end', () => {
        req.body = JSON.parse(data);

        res.setHeader("Content-Type", "application/json");
        const feedback = new feedbackModel(req.body);
        console.log(req.body);
        try {

            feedback.save((err) => {
                if (err) {
                    console.log(err)
                    res.statusCode = 500
                    res.setHeader('Content-Type', 'application/json')
                    res.write(JSON.stringify({ success: false, message: 'Internal server error' }))
                    res.end()
                } else {
                    res.statusCode = 200
                    res.setHeader('Content-Type', 'application/json')
                    res.write(JSON.stringify({ success: true, message: feedback }))
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
module.exports = { getAllFeedbacks, createFeedback };