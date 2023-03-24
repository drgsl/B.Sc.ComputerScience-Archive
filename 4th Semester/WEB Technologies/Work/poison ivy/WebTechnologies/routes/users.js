
const { Router } = require('../utils/Router')
const { getAllUsers } = require('../controller/users')
const {createUser} = require('../controller/users')
var router = new Router()
router.get('/api/v1/users/',getAllUsers)
router.post('/api/v1/users/',createUser)
module.exports = router