const { Router } = require('../utils/Router')
const addMakeupController = require('../controller/addmakeup')

var router = new Router()

router.get('/addedMakeup', addMakeupController.getAddMakeupHTML)
router.get('/addMakeup', addMakeupController.getAddMakeupHTML)
router.get('/add-makeup.html', addMakeupController.getAddMakeupHTML)
router.get('/styles/nav.css', addMakeupController.getAddMakeupCSS2)
router.get('/styles/add-makeup.css', addMakeupController.getAddMakeupCSS1)
router.get('/scripts/nav.js', addMakeupController.getAddMakeupJS)
    // router.get('/makeup',addMakeupController.getProducts)

module.exports.addMakeup = router