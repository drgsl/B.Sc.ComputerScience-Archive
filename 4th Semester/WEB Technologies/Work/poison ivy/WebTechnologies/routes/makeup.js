
const { Router } = require('../utils/Router')
const { getAllMakeups } = require('../controller/makeup')
const { createMakeup }=require('../controller/makeup')
const { deleteMakeup }=require('../controller/makeup')
const { updateMakeup }=require('../controller/makeup')
var router = new Router()
router.get('/api/v1/makeup/',getAllMakeups)
router.post('/api/v1/makeup/',createMakeup)
router.post('/api/v1/updatemakeup/', updateMakeup)
router.post('/api/v1/deletemakeup/', deleteMakeup)

module.exports = router