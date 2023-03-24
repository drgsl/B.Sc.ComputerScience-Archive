const { Router } = require('../utils/Router')
const myAccountController = require('../controller/myaccount')

var router = new Router()


router.get('/Myaccount', myAccountController.getMyAccountHTML)
router.get('/Myaccount.html', myAccountController.getMyAccountHTML)
router.get('/styles/nav.css', myAccountController.getMyAccountCSS2)
router.get('/styles/Myaccount.css', myAccountController.getMyAccountCSS1)
router.get('/scripts/nav.js', myAccountController.getMyAccountJS)
    // router.get('/products',myAccountController.getProducts)
    ///exemplu
    ///router.get(url_string, functieApelata)
    ///
module.exports.myAccount = router