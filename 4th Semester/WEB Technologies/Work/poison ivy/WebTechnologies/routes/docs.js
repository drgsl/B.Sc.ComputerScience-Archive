const { Router } = require('../utils/Router')
const docsController = require('../controller/docs')

var router = new Router()




router.get('/doc', docsController.getDocHTML)
router.get('/doc.html', docsController.getDocHTML)
router.get('/styles/doc.css', docsController.getDocCSS)
    // router.get('/products',docsController.getProducts)
    ///exemplu
    ///router.get(url_string, functieApelata)
    ///
module.exports.docs = router