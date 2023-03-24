function buildProductAdminHtml(nume, imagine, taguri,id) {
    let taguletse = "";

    let tag = taguri.split(",");
    tag.pop();

    for (let i of tag) {
        taguletse += '<div class="tag">' + i + "</div>";
    }
    let s = `<div class="prod">
                                <div class="product-container-dim">
                                    <div class="product">
                                        <img class="product-img" src="${imagine}">
                                        <div class="product-name" > ${nume} </div>
                                        
                                        <div class="tag-list">
                                        ${taguletse}
                                        </div>
                                        <div class="btn">
                                         
                                        <button onclick="update('${id}')" class="btn-update"> Update </button>
                                          
                                        </div>       
                                     </div>
                                 </div>
                            </div>`;
    return s;
}


function update(id) {
    localStorage.setItem("id", id);
    window.location = "/update-product.html";
}
function allWordsInString(words, string) {
    for (let word of words) {
        if (string.indexOf(word) == -1) {
            return false;
        }
    }
    return true;
}

function filterBySearch() {
    populateData(() => {
        let checkboxes = document.getElementsByClassName("checkboxfilter");
        checkboxes = Array.prototype.slice.call(checkboxes);
        let filterValues = checkboxes.filter((x) => x.checked).map((x) => x.value);

        let products = [];
        for (let a of window.products) {
            let objectString = JSON.stringify(a).toLowerCase();
            if (allWordsInString(filterValues, objectString)) {
                products.push(a);
                console.log(a);
            }
        }
        showProducts(products);
    });
}

function filterAdminByName() {
    let currentValue = document.getElementById("searchbar").value;
    console.log(currentValue);
    currentValue = currentValue.toLowerCase();
    let products = [];

    let values = currentValue.split(" ");
    products = window.products.slice();
    if (currentValue != "") {
        for (let x of values) {
            let produse = [];
            for (let a of products) {
                let name = a["name"].toLowerCase();
                if (name.indexOf(x) != -1 && products.indexOf(name) === -1) {
                    produse.push(a);
                    console.log(a);
                }
            }
            products = produse.slice();
        }

        showProducts(products);
    } else {
        populateData();
    }
}

function showProducts(products) {
    window.products = products;
    document.getElementById("productSectionAdmin").innerHTML = "";
    for (let element of products) {
        var product = document.createElement("div");
        var tag = element["tags"] + ","; // virgula e delimitator intre elementele array ului
        product.innerHTML = buildProductAdminHtml(
            element["name"],
            element["image_path"],
            tag,
            element["_id"]
        );
        document.getElementById("productSectionAdmin").appendChild(product);
    }
}

async function populateData(callback = undefined) {
    const response = (
            await fetch("https://ivy-sun.herokuapp.com/api/v1/products/", {
                method: "GET",
                headers: {
                    "Content-Type": "application/json",
                },
            })
        )
        .json().then((data) => {
            showProducts(data["products"]);
            if (callback !== undefined) {
                callback();
            }
        });
}

