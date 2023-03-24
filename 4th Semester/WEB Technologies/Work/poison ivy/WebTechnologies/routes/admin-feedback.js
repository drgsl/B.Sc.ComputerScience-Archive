const { Router } = require('../utils/Router')
const adminFeedbackController = require('../controller/admin-feedback')

var router = new Router()


router.get('/adminFeedback', adminFeedbackController.getAdminFeedbackHTML)
router.get('/admin-feedback.html', adminFeedbackController.getAdminFeedbackHTML)
router.get('/styles/nav.css', adminFeedbackController.getAdminFeedbackCSS2)
router.get('/styles/admin-feedback.css', adminFeedbackController.getAdminFeedbackCSS1)
router.get('/scripts/nav.js', adminFeedbackController.getAdminFeedbackJS)
router.get('/scripts/adminFeedback.js', adminFeedbackController.getAdminFeedbackJS2)
    // router.get('/feedback',adminFeedbackController.getProducts)
    ///exemplu
    ///router.get(url_string, functieApelata)
    ///
module.exports.adminFeedback = router