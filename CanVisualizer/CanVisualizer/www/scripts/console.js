var myvar;
function startTimer() {
    myVar = setInterval(myTimer, 1000)
}


function myTimer() {
    var div = document.getElementById("console");

    div.innerHTML = div.innerHTML + sessionStorage.data +"<br>";
}

function consoleHome() {
    clearInterval(myVar);
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("content").innerHTML =
            this.responseText;
        }
    };
    xhttp.open("GET", "index.html", false);
    xhttp.send();
    checkConnection();
}