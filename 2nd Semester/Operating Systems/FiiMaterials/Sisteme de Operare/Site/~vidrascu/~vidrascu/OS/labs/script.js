
function myToggle(elemId) {

  var x = document.getElementById(elemId);
  if (x.style.display === "none") {
    x.style.display = "block";
  } else {
    x.style.display = "none";
  }

}



function mySetToggle(elemId) {

  var seturi_exercitii = ["setCV", "setRB", "setBP", "setDA", "setAG", "setVU"];
  seturi_exercitii.forEach(myAuxFunction);

  function myAuxFunction(item, index) {
    if (item == elemId) {
      myToggle(elemId);
    } else {
      document.getElementById(item).style.display = "none";
    }
  }

}

function mySetToggle2(elemId,elemIdx) {

  var seturi_exercitii = ["setCV", "setRB", "setBP", "setDA", "setAG", "setVU"];
  seturi_exercitii.forEach(myAuxFunction2);

  function myAuxFunction2(item, index) {
    if (item == elemId) {
      myToggle(elemId+elemIdx);
    } else {
      document.getElementById(item+elemIdx).style.display = "none";
    }
  }

}
