async function getAllPlaceHoldersAndPost()
{
    var fname = document.getElementById("fname").value;
    var lname = document.getElementById("lname").value;
    var country = document.getElementById("country").value;
    var description = document.getElementById("subject").value;
    var data = {
        firstName: fname,
        lastName: lname,
        country: country,
        subject: description

      }
      const response = await fetch("https://ivy-sun.herokuapp.com/api/v1/feedbacks/", {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
      })
      window.location.href = "https://ivy-sun.herokuapp.com/#contact";
}

