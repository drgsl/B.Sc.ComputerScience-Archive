const { Router } = require('../utils/Router')
const addProductController = require('../controller/addproductPage')

var router = new Router()

router.get('/added', addProductController.getAddProductPageHTML)
router.get('/add-product', addProductController.getAddProductPageHTML)
router.get('/add-product.html', addProductController.getAddProductPageHTML)
router.get('/styles/nav.css', addProductController.getAddProductPageCSS2)
router.get('/styles/add-product.css', addProductController.getAddProductPageCSS1)
router.get('/scripts/nav.js', addProductController.getAddProductPageJS)
    // router.get('/products',addProductController.getProducts)
    ///exemplu
    ///router.get(url_string, functieApelata)
    ///
module.exports.addProduct = router