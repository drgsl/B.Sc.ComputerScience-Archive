const { Router } = require('../utils/Router')
const indexController = require('../controller')

var router = new Router()



router.get('/', indexController.getIndexHTML)
router.get('/index', indexController.getIndexHTML)
router.get('/index.html', indexController.getIndexHTML)
router.get('/styles/nav.css', indexController.getIndexCSS2)
router.get('/styles/index.css', indexController.getIndexCSS1)
router.get('/scripts/nav.js', indexController.getIndexJS)
router.get('/scripts/contact.js', indexController.getIndexJS2)
router.post("/api/v1/counter", indexController.counter)
router.get("/api/v1/getcounts", indexController.getCounts)

// router.get('/products',indexController.getProducts)
///exemplu
///router.get(url_string, functieApelata)
///
module.exports.index = router