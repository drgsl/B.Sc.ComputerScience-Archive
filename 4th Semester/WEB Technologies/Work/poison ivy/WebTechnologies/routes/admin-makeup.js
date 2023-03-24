const { Router } = require('../utils/Router')
const adminMakeupController = require('../controller/adminMakeup')

var router = new Router()


router.get('/adminMakeup', adminMakeupController.getAdminMakeupHTML)
router.get('/admin-makeup.html', adminMakeupController.getAdminMakeupHTML)
router.get('/styles/nav.css', adminMakeupController.getAdminMakeupCSS2)
router.get('/styles/admin-makeup.css', adminMakeupController.getAdminMakeupCSS1)
router.get('/scripts/nav.js', adminMakeupController.getAdminMakeupJS1)
router.get('/scripts/adminMakeup.js', adminMakeupController.getAdminMakeupJS2)
   
module.exports.adminMakeup = router