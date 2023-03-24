const { Router } = require('../utils/Router')
const searchMakeupController = require('../controller/searchMakeup')

var router = new Router()

router.get('/makeup', searchMakeupController.getSearchMakeupHTML)
router.get('/makeup.html', searchMakeupController.getSearchMakeupHTML)
router.get('/styles/nav.css', searchMakeupController.getSearchMakeupCSS2)
router.get('/styles/makeup.css', searchMakeupController.getSearchMakeupCSS1)
router.get('/scripts/nav.js', searchMakeupController.getSearchMakeupJS1)
router.get('/scripts/searchMakeup.js', searchMakeupController.getSearchMakeupJS2)
    // router.get('/makeup',searchMakeupController.getProducts)

module.exports.searchMakeup = router