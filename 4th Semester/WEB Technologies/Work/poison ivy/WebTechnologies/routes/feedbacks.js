const { Router } = require('../utils/Router')
const { getAllFeedbacks } = require('../controller/feedbacks')
const {createFeedback}  = require('../controller/feedbacks')
var router = new Router()

router.get('/api/v1/feedbacks/',getAllFeedbacks)
router.post('/api/v1/feedbacks/',createFeedback)
module.exports = router