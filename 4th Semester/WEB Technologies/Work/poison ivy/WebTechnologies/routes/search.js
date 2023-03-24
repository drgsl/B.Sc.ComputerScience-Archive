const { Router } = require('../utils/Router')
const searchController = require('../controller/search')

var router = new Router()

router.get('/search', searchController.getSearchHTML)
router.get('/search.html', searchController.getSearchHTML)
router.get('/styles/nav.css', searchController.getSearchCSS2)
router.get('/styles/search.css', searchController.getSearchCSS1)
router.get('/scripts/nav.js', searchController.getSearchJS1)
router.get('/scripts/search.js', searchController.getSearchJS2)
    // router.get('/products',searchController.getProducts)
    ///exemplu
    ///router.get(url_string, functieApelata)
    ///
module.exports.search = router