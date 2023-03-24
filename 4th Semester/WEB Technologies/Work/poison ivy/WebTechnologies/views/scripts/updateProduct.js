async function preloadStuff() {
    const id = localStorage.getItem("id");

    const response = (await fetch("https://ivy-sun.herokuapp.com/api/v1/products/", {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    })).json().then((data) => {
        data = data["products"].filter(x => x["_id"] == id);
        if (data.lenght === 0) {
            console.error("nu am gasit id-ul");
        } else {
            console.log(data);
            let el = data[0];
            document.getElementById("id").value = el["_id"]
            document.getElementById("product-name").value = el["name"];
            document.getElementById("product-img").value=el["image_path"];
            document.getElementById("product-tag").value=el["tags"];
            document.getElementById("product-desc").value=el["descriere"];
            document.getElementById("product-link").value=el["url"];

            }
    });

}

async function updateStuff(){
    var data = {
        id: document.getElementById("id").value,
        name: document.getElementById("product-name").value,
        img: document.getElementById("product-img").value,
        tags: document.getElementById("product-tag").value,
        desc: document.getElementById("product-desc").value,
        url: document.getElementById("product-link").value,
    };

  
      const response = await fetch(
        "https://ivy-sun.herokuapp.com/api/v1/updateproduct/",
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify(data),
        }
      );

    window.location.href = "https://ivy-sun.herokuapp.com/admin-products.html";
     
}

async function deleteProduct(){
    var data = {
        id: document.getElementById("id").value,
    };

  
      const response = await fetch(
        "https://ivy-sun.herokuapp.com/api/v1/deleteproduct/",
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify(data),
        }
      );

    window.location.href = "https://ivy-sun.herokuapp.com/admin-products.html";
     
}