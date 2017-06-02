var myVar = setInterval(myTimer, 1000);

function myTimer() {
    var div = document.getElementById("console");

    div.innerHTML = div.innerHTML + localStorage.data;
}