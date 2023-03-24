const { Router } = require('../utils/Router')
const updateProductController = require('../controller/updateProduct')

var router = new Router()


router.get('/update-product', updateProductController.getUpdateProductHTML)
router.get('/update-product.html', updateProductController.getUpdateProductHTML)
router.get('/styles/nav.css', updateProductController.getUpdateProductCSS2)
router.get('/styles/update-product.css', updateProductController.getUpdateProductCSS1)
router.get('/scripts/nav.js', updateProductController.getUpdateProductJS)
router.get('/updateProduct.js', updateProductController.getUpdateJS) 
router.get('/updateProduct',updateProductController.getUpdateJS)  

module.exports.updateProduct = router