const { Router } = require('../utils/Router')
const loginController = require('../controller/login')

var router = new Router()


router.post('/api/v1/token/', loginController.login)
router.get('/login.html', loginController.getLoginHTML)
router.get('/registered', loginController.getLoginHTML)
router.get('/styles/nav.css', loginController.getLoginCSS2)
router.get('/styles/login.css', loginController.getLoginCSS1)
router.get('/logout', loginController.getLogout)
router.get('/scripts/nav.js', loginController.getLoginJS)
    // router.get('/products', loginController.getProducts)

module.exports.login = router