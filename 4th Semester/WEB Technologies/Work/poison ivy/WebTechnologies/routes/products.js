
const { Router } = require('../utils/Router')
const { getAllProducts } = require('../controller/products')
const { createProduct } = require('../controller/products')
const { updateProduct }= require('../controller/products')
const { deleteProduct }= require('../controller/products')

var router = new Router()
router.get('/api/v1/products/',getAllProducts)
router.post('/api/v1/products/',createProduct)
router.post('/api/v1/deleteproduct/',deleteProduct)
router.post('/api/v1/updateproduct/',updateProduct)
module.exports = router