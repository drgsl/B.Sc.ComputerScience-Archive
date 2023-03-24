function on(el) {
    let div = el.parentElement.children[1];
    div.style.display = "block";
    div.style.width = "100%";
}
function off(el) {
    el.style.display = "none";
    el.style.width = "0";
}

function buildFeedback(firstName,lastName,country,subject){
    let s = `         <div class="feedback">
    <p class="date"> <b> ${firstName}  ${lastName}</b> in ${country} </p>
    <p class="textul">${subject} </p>
</div>`
return s;
}
function showFeedbacks(feedbacks){
    window.feedbacks=feedbacks;
    document.getElementById("productSectionAdmin").innerHTML = "";
    for (let element of feedbacks) {
        var feedback = document.createElement("div");
        feedback.innerHTML = buildFeedback(element["firstName"], element["lastName"],element["country"], element["subject"])
        document.getElementById("productSectionAdmin").appendChild(feedback);
    }
}
async function populateDataFeedback() {

    const response = (await fetch("https://ivy-sun.herokuapp.com/api/v1/feedbacks/", {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    })).json().then((data) => showFeedbacks(data["feedbacks"]));
}
