function on(el) {
    let div = el.parentElement.children[1];
    div.style.display = "block";
    div.style.width = "100%";
    fetch("https://ivy-sun.herokuapp.com/api/v1/counter", {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({"id": el.parentElement.children[1].children[0].innerHTML})
    })
}

function off(el) {
    el.style.display = "none";
    el.style.width = "0";
}


function downloadObjectAsJson(data, exportName){
    var dataStr = "data:text/plain;charset=utf-8," + encodeURIComponent(data);
    var downloadAnchorNode = document.createElement('a');
    downloadAnchorNode.setAttribute("href",     dataStr);
    downloadAnchorNode.setAttribute("download", exportName);
    document.body.appendChild(downloadAnchorNode); // required for firefox
    downloadAnchorNode.click();
    downloadAnchorNode.remove();
  }



function makeTop(makeups, callback) {
    let group_by_age_tags = {}
    for(let el of makeups) {
        el["tags"].filter(x => x.match(/[0-9]+-[0-9]+/g))
        .map(age_tag => {
            if(group_by_age_tags[age_tag] != undefined) {
                group_by_age_tags[age_tag].push(el);
            }
            else {
                group_by_age_tags[age_tag] = [el];
            }
        });
    }

    return callback(group_by_age_tags);
    
}

function htmlCallback(group_by_age_tags) {
    let html = "<html><body>"
    for(let key of Object.keys(group_by_age_tags)) {
        html += `<h1>${key}</h1>` 
        let top_for_key = group_by_age_tags[key].sort((a, b) => b["score"] - a["score"]);
        html += `<h2>${JSON.stringify(top_for_key)}</h2>`
    }
    html += "</body></html>"

    return html;
}

function topHTML() {
    populateData(async () => {
        (await fetch("https://ivy-sun.herokuapp.com/api/v1/getcounts", {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    })).json().then(async(data) => {
        window.makeups.map((x) => x["score"] = 0);
        for(var key of Object.keys(data)) {
            let id = key.trim();
            console.log(id);
            window.makeups.filter(x => x["_id"] == id)[0]["score"] = data[key];
        }

        downloadObjectAsJson(makeTop(window.makeups, htmlCallback), "top.html");
    

    });
    })
}


// <?xml version="1.0" encoding="UTF-8" ?>
// <rss version="2.0">
// <channel>
//  <title>Top makeups today</title>
//  <description>This is the makeups top as of today</description>

//  <item>
//   <title>Example entry</title>
//   <description>Here is  an interesting description.</description>
//  </item>

// </channel>
// </rss>

function rssCallback(group_by_age_tags) {
    let html = `<?xml version="1.0" encoding="UTF-8" ?>
    <rss version="2.0">
    <channel>
    <title>Top makeups today</title>
    <description>This is the makeups top as of today</description>`
    for(let key of Object.keys(group_by_age_tags)) {
        html += `<item><title>${key}</title>` 
        let top_for_key = group_by_age_tags[key].sort((a, b) => b["score"] - a["score"]);
        
        let desc = ""

        for(let el of top_for_key) {
            desc += el["name"] + " ";
        }
        html += `<description>${desc}</description>`
        html += '</item>'
    }
    html += "</channel></rss>"

    console.log(html)

    return html;
}

function topRSS() {
    console.log("ne intamplam si noi ?")
    populateData(async () => {
        (await fetch("https://ivy-sun.herokuapp.com/api/v1/getcounts", {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    })).json().then(async(data) => {
        window.makeups.map((x) => x["score"] = 0);
        for(var key of Object.keys(data)) {
            let id = key.trim();
            console.log(id);
            window.makeups.filter(x => x["_id"] == id)[0]["score"] = data[key];
        }

        downloadObjectAsJson(makeTop(window.makeups, rssCallback), "top.xml");
    });
    })
}

function pdfCallback(group_by_age_tags) {
    const doc = new jspdf.jsPDF();

    let index = 1;

    for(let key of Object.keys(group_by_age_tags)) {
        doc.text(key, 10, 10 * index);
        index += 1;
        let top_for_key = group_by_age_tags[key].sort((a, b) => b["score"] - a["score"]);
        for(let el of top_for_key) {
            doc.text(el["name"], 10, 10 * index);
            index += 1;
            if(index > 27) {
                doc.addPage();
                index = 1;
            }
        }

        index += 1;
    }
    doc.save("top.pdf");
}

function topPDF() {
    console.log("ne intamplam si noi ?")
    populateData(async () => {
        (await fetch("https://ivy-sun.herokuapp.com/api/v1/getcounts", {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    })).json().then(async(data) => {
        window.makeups.map((x) => x["score"] = 0);
        for(var key of Object.keys(data)) {
            let id = key.trim();
            console.log(id);
            window.makeups.filter(x => x["_id"] == id)[0]["score"] = data[key];
        }

        makeTop(window.makeups, pdfCallback);
    });
    })
}

function buildMakeupHtml(nume, imagine, taguri, descriere, link, produse, id) {
    let taguletse = ""
    let produsele = ""
    let tag = taguri.split(",");
    let produs = produse.split(",");
    produs.pop();
    tag.pop();

    window.productString


    for (let i of tag) {
        taguletse += "<div class=\"tag\">" + i + "</div>"
    }
    for (let i of produs) {
        produsele += "<div class=\"tag\">" + window.products.products.filter(x => x["_id"] == i)[0]["name"] + "</div>"
    }
    let s = `<div class="col">
                            <div class="makeup-container">
                                <div class="wrap">
                                    <img class="makeup-img" onclick="on(this)" src="${imagine}">
                                    <div class="hide" id="overlay" onclick="off(this)">
                                        <p hidden> ${id} </p>
                                        <h3> ${nume} </h3>
                                        <h5> Descriere </h5>
                                        <p> ${descriere} </p>
                                        <h5> Pentru mai multe detalii accesati: </h5>
                                        <a href="${link}"> ${link} </a> 
                                    </div>
                                </div>
                                <div class="details"> ${nume} </div>
                                <div class="tags">
                                      ${taguletse}
                                </div>
                                <h5> <a href="api/v1/products?produse=${produs.join(",")}"> Lista produselor: </a> </h5>   
                                <div class="product-list">${produsele}</div></div>
                            </div>
                        </div>`
    return s;

}

function allWordsInString(words, string) {
    for (let word of words) {
        if (string.indexOf(word) == -1) {
            return false;
        }
    }
    return true;
}

function filterByName() {

    populateData(() => {
        let currentValue = document.getElementById("searchbar").value.toLowerCase();
        console.log(currentValue);

        let makeups = [];
        let currentSplit = currentValue.split(" ");

        for (let a of window.makeups) {
            let name = a["name"].toLowerCase();
            if (allWordsInString(currentSplit, name)) {
                makeups.push(a);
                console.log(a);
            }


        }
        showMakeups(makeups);
    })

}


function updateSlider(value) {
    document.getElementById("agep").innerText = "Age: " + value;
    window.sliderValue = value;
}

function disableSlider() {
    document.getElementById("megaSlider").disabled = !document.getElementById("megaSlider").disabled;
    document.getElementById("agep").innerText = "Age filter disabled";
    window.sliderValue = undefined;
}

function ageFilter(element, ageValue) {
    if (ageValue === undefined) return true;
    let iz_ok = false;
    element["tags"].filter(x => x.match(/[0-9]+-[0-9]+/g))
        .map(x => {
            let start_age = parseInt(x.split("-")[0]);
            let end_age = parseInt(x.split("-")[1]);
            if (start_age <= ageValue && ageValue <= end_age) {
                iz_ok = true;
            }
        });
    return iz_ok;
}

function filterByAnything() {

    populateData(() => {
        let checkboxes = document.getElementsByClassName("checkboxfilter");
        checkboxes = Array.prototype.slice.call(checkboxes);
        let filterValues = checkboxes.filter(x => x.checked).map(x => x.value);

        let makeups = [];
        for (let a of window.makeups) {
            let objectString = JSON.stringify(a).toLowerCase();
            if (allWordsInString(filterValues, objectString) && ageFilter(a, window.sliderValue)) {
                makeups.push(a);
                console.log(a);
            }
        }
        showMakeups(makeups);
    })
}


function showMakeups(makeups) {
    window.makeups = makeups;
    document.getElementById("makeupSection").innerHTML = "";
    for (let element of makeups) {
        var makeup = document.createElement("div");
        var tag = element["tags"] + ',';
        var produs = element["products"] + ",";
        makeup.innerHTML = buildMakeupHtml(element["name"], element["image_path"], tag, element["descriere"], element["url"], produs, element["_id"])
        document.getElementById("makeupSection").appendChild(makeup);
    }
}

async function populateData(callback = undefined) {


    (await fetch("https://ivy-sun.herokuapp.com/api/v1/products/", {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    })).json().then(async(data) => {
        window.products = data;
        (await fetch("https://ivy-sun.herokuapp.com/api/v1/makeup/", {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json'
            }
        })).json().then((data) => {
            showMakeups(data["makeups"])
            if (callback !== undefined) {
                callback();
            }
        });
    });

}