function onLoad() {
    document.addEventListener("deviceready", onDeviceReady, false);
}

function onDeviceReady() {
    //Bluetooth init
    connectButton.addEventListener('touchend', bluetooth.manageConnection, false);
    btnSubmitConfig.addEventListener("click", bluetooth.sendMessage);

    
    //QR code init
    btnConnect.addEventListener("click", qrcode.scan);


    //Change Status bar Color 
    if(window.cordova && StatusBar)
    {
        StatusBar.backgroundColorByHexString('CC6600')
    }
}




