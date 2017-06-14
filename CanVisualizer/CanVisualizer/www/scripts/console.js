var myvar;
function startTimer() {
    var interval = sessionStorage.getItem('readinterval');
    var timer;
    if (interval === null) {
        timer = 1000;
    } else {
        timer = interval * 1000;
    }
    myVar = setInterval(myTimer, timer);
  
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