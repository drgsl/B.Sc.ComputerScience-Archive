const { Router } = require('../utils/Router')
const adminhomeController = require('../controller/admin-home')

var router = new Router()


router.get('/1401040519092021', adminhomeController.getAdminHomeHTML)
router.get('/1401040519092021.html', adminhomeController.getAdminHomeHTML)
router.get('/styles/nav.css', adminhomeController.getAdminHomeCSS2)
router.get('/styles/admin-home.css',adminhomeController.getAdminHomeCSS1)
router.get('/scripts/nav.js', adminhomeController.getAdminHomeJS)

module.exports.adminHome = router
