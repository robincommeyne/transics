function onLoad() {
    document.addEventListener("deviceready", onDeviceReady, false);
    
}
function checkConnection() {
    bluetoothSerial.isConnected(connected, disconnected);
}

function connected() {
    btnConnect.innerHTML = "";
    var elem = document.createElement("img");
    elem.setAttribute("src", "images/connect.png");
    elem.setAttribute("height", "30");
    btnConnect.appendChild(elem);
    btnConnect.innerHTML = btnConnect.innerHTML + "<br /><br />Disconnect";
}
function disconnected() {
    
}

function onDeviceReady() {
    //Change Status bar Color 
    if(window.cordova && StatusBar)
    {
        StatusBar.backgroundColorByHexString('CC6600');
    }
}

function openFilters() {
    
    goToPage("filters.html");
    getProperties();
}
function openConsole() {

    goToPage("console.html");
    startTimer();
}
function openSettings() {

    goToPage("settings.html");
}
function openGauges() {
    goToPage("gauges.html");
    GaugeTimer();
   
}
function openGraph() {
    goToPage("graph.html");
    graphLoaded();
    loadFilters();

}
function openRawData() {
    goToPage("rawdata.html");

}

function goToPage(page)
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("content").innerHTML =
            this.responseText;
        }
    };
    xhttp.open("GET",page, false);
    xhttp.send();
}


