function parseCookie(str) {
    let cookie_key_val = str.split('; ').filter(x => x.includes("=")).map(x => x.split("="));
    let res = {};
    for (let el of cookie_key_val) {
        res[el[0]] = el[1];
    }
    return res;
}


module.exports = {parseCookie}