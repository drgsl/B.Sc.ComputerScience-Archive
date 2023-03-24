function buildMakeupAdminHtml(nume, imagine, taguri, produse, id) {
    let taguletse = "";
    let produsele = "";
    let tag = taguri.split(",");
    let produs = produse.split(",");
    produs.pop();
    tag.pop();

    for (let i of tag) {
        taguletse += '<div class="tag">' + i + "</div>";
    }
    for (let i of produs) {
        produsele += '<div class="tag">' + i + "</div>";
    }
    let s = `<div class="makep">
                                  <div class="makeup-container-dim">
                                      <div class="makeup">
                                          <img class="makeup-img" src="${imagine}">
                                          <div class="makeup-name" > ${nume} </div>
                                          
                                          <div class="tag-list">
                                          ${taguletse}
                                          </div>
                                          <div class="btn">

                                          
                                          <button onclick="update('${id}')" class="btn-update"> Update </button>
                                          
                                          </div> 
                                          <div class="list">
                                          <h5> Lista produselor: </h5>   
                                          <div class="product-list">${produsele}</div></div>
                                       </div>
                                       
                                   </div>
                              </div>`;
    return s;
}

function update(id) {
    localStorage.setItem("id", id);
    window.location = "/updateMakeup";
}

function filterAdminByName() {
    populateData(() => {
        let currentValue = document.getElementById("searchbar").value;

        currentValue = currentValue.toLowerCase();
        let makeups = [];

        let values = currentValue.split(" ");
        makeups = window.makeups.slice();
        if (currentValue != "") {
            for (let x of values) {
                let makeupuri = [];
                for (let a of makeups) {
                    let name = a["name"].toLowerCase();
                    if (name.indexOf(x) != -1 && makeups.indexOf(name) === -1) {
                        makeupuri.push(a);
                        console.log(a);
                    }
                }
                makeups = makeupuri.slice();

            }

            showMakeups(makeups);
        }
    })
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
        let filterValues = checkboxes.filter(x => x.checked).map(x => x.value);

        let makeups = [];
        for (let a of window.makeups) {
            let objectString = JSON.stringify(a).toLowerCase();
            if (allWordsInString(filterValues, objectString)) {
                makeups.push(a);
                console.log(a);
            }
        }
        showMakeups(makeups);
    })
}

function showMakeups(makeups) {
    window.makeups = makeups;
    document.getElementById("makeupSectionAdmin").innerHTML = "";
    console.log(makeups);
    for (let element of makeups) {
        var makeup = document.createElement("div");
        var tag = element["tags"] + ","; // virgula e delimitator intre elementele array ului
        var produs = element["products"] + ",";
        makeup.innerHTML = buildMakeupAdminHtml(
            element["name"],
            element["image_path"],
            tag,
            produs,
            element["_id"]
        );
        document.getElementById("makeupSectionAdmin").appendChild(makeup);
    }
}

async function populateData(callback = undefined) {
    const response = (
            await fetch("https://ivy-sun.herokuapp.com/api/v1/makeup/", {
                method: "GET",
                headers: {
                    "Content-Type": "application/json",
                },
            })
        )
        .json()
        .then((data) => {
            showMakeups(data["makeups"])
            if (callback !== undefined) {
                callback();
            }
        });
}