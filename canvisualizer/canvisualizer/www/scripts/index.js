function onLoad() {
    document.addEventListener("deviceready", onDeviceReady, false);
    
    
    //bluetoothSerial.isConnected(connected, disconnected);

    
}

//function connected() {
//    btnConnect.innerHTML = "";
//    var elem = document.createElement("img");
//    elem.setAttribute("src", "images/connect.png");
//    elem.setAttribute("height", "30");
//    btnConnect.appendChild(elem);
//    btnConnect.innerHTML = btnConnect.innerHTML + "<br /><br />Disconnect";
//}

//function disconnected() {
    
    
//}

function onDeviceReady() {
    //Bluetooth init
    //connectButton.addEventListener('touchend', bluetooth.manageConnection, false);
    //btnSubmitConfig.addEventListener("click", bluetooth.sendMessage);
 
    
    //QR code init
    btnConnect.addEventListener("click", bluetooth.manageConnection);
    //btnFilters.addEventListener("click", loadpage)


    //Change Status bar Color 
    if(window.cordova && StatusBar)
    {
        StatusBar.backgroundColorByHexString('CC6600');
    }
}

function loadDoc() {
    
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("demo").innerHTML =
            this.responseText;
        }
    };
    xhttp.open("GET", "filters.html", false);
    xhttp.send();
    getProperties();
}

