
// Această funcție este inclusă la finalul body-ului paginilor HTML cu exercițiile de laborator, pentru a include "inline" codul sursă (bash sau C) de la o adresă URL de pe server.

function includeMyCode() {
    var z, i, elmnt, file, xhttp;

    /* Loop through a collection of all HTML elements: */
    z = document.getElementsByTagName("*");
    for (i = 0; i < z.length; i++) {
        elmnt = z[i];

        /*search for elements with a certain atrribute:*/
        file = elmnt.getAttribute("w3-include-MyCode");

        if (file) {
            // daca file <> null, înseamnă că acel element specifică URL-ul unui fișier program.c ce trebuie descărcat de pe server și inclus în acel element HTML.

            /* Make an HTTP request using the attribute value as the file name: */
            xhttp = new XMLHttpRequest();  // inițializare un obiect ce va face o cerere http asincronă, prin metoda GET

            xhttp.onreadystatechange = function() {
				// handler-ul (funcția callback) ce va fi apelată când se modifică starea acelei cereri din "în curs de descărcare" în "OK, receive completed".
				// Explicație: deoarece apelul this.open()+send() de mai jos este de tip asincron, această funcție callback va fi apelată la terminarea transferului...
				if (this.readyState == 4) {
					// 4 : You know the entire content has been received when the value of readyState becomes XMLHttpRequest.DONE (4), and status becomes 200 ("OK").
					if (this.status == 200) {
						var codulC = this.responseText;  // acesta este conținutul fișierului program.c, primit de pe server.
						var result = codulC.replace(/</g, "&lt;"); // aici înlocuiesc fiecare apariție a caracterului "<" cu tag-ul &lt; pentru a putea vizualiza corect codul C în "interiorul" acelui element HTML (referit prin this), e.g. <pre>codul C</pre>
						elmnt.innerHTML = result; // aici practic se obține înlocuirea <div w3-include-MyCode="url">See the code from <a href="url">here</a>.</div> cu <div>codul C de la acel url</div> !!!
					}
					if (this.status == 404) { elmnt.innerHTML = "Error 404: the file, containing that C program or bash script, was not found!"; }

					/* Remove the attribute, and call this function once more: */
					elmnt.removeAttribute("w3-include-MyCode");
					includeMyCode(); // este necesar acest apel, pentru că altfel se procesează doar primul element HTML ce conține acel atribut "w3-include-MyCode", în ciuda acelui for prin toate elementele paginii HTML.
				}
            }

            xhttp.open("GET", file, true);  // inițializează nou creata cerere http; file = url-ul de pe server al fișierului program.c ; true: cerere asincronă
            xhttp.send(null); // se trimite cererea respectivă către server, asincron -- fără a se aștepta răspunsul, datorită setării din apelul open()

            /* Exit the function: */
            return;
        }
    }
}


// Aceasta este funcția inițială, găsită într-un exemplu pe net, pentru a include "inline" codul html de la o adresă URL de pe un server.
// Eu am customizat acest exemplu, in functia de mai sus, pentru a include "inline" cod sursă C sau scripturi bash, cu afișarea corectă a simblolurilor "<".

function includeHTML() {
  var z, i, elmnt, file, xhttp;
  /* Loop through a collection of all HTML elements: */
  z = document.getElementsByTagName("*");
  for (i = 0; i < z.length; i++) {
    elmnt = z[i];
    /*search for elements with a certain atrribute:*/
    file = elmnt.getAttribute("w3-include-html");
    if (file) {
      /* Make an HTTP request using the attribute value as the file name: */
      xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
          if (this.status == 200) {elmnt.innerHTML = this.responseText;}
          if (this.status == 404) {elmnt.innerHTML = "Page not found.";}
          /* Remove the attribute, and call this function once more: */
          elmnt.removeAttribute("w3-include-html");
          includeHTML();
        }
      }
      xhttp.open("GET", file, true);
      xhttp.send();
      /* Exit the function: */
      return;
    }
  }
}
