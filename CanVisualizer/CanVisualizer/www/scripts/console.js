var myvar;
function startTimer() {
    var interval = sessionStorage.getItem('readinterval');
    myVar = setInterval(myTimer, interval * 1000);
  
}


function myTimer() {
    var div = document.getElementById("console");

    div.innerHTML = div.innerHTML + sessionStorage.data + "<br>";
    div.scrollTop = div.scrollHeight;
}

function consoleHome() {
    
    clearInterval(myVar);
    goToPage("index.html");
    checkConnection();
}