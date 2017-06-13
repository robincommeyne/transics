var myvar;
function startTimer() {
    myVar = setInterval(myTimer, 1000)
  
}


function myTimer() {
    var div = document.getElementById("console");

    div.innerHTML = div.innerHTML + sessionStorage.data + "<br>";
    sessionStorage.removeItem("data");
}

function consoleHome() {
    
    clearInterval(myVar);
    goToPage("index.html");
    checkConnection();
}