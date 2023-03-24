const { Router } = require('../utils/Router')
const updateMakeupController = require('../controller/updateMakeup')

var router = new Router()


router.get('/updateMakeup', updateMakeupController.getUpdateMakeupHTML)
router.get('/update-makeup.html', updateMakeupController.getUpdateMakeupHTML)
router.get('/styles/nav.css', updateMakeupController.getUpdateMakeupCSS2)
router.get('/styles/update-makeup.css', updateMakeupController.getUpdateMakeupCSS1)
router.get('/scripts/nav.js', updateMakeupController.getUpdateMakeupJS)
router.get('/update.js', updateMakeupController.getUpdateJS)
router.get('/update', updateMakeupController.getUpdateJS)

module.exports.updateMakeup = router