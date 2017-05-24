﻿function onLoad() {
    document.addEventListener("deviceready", onDeviceReady, false);
}

function onDeviceReady() {
    //Bluetooth init
    connectButton.addEventListener('touchend', bluetooth.manageConnection, false);
    sendButton.addEventListener("click", bluetooth.sendMessage);

    //QR code init
    scanQrcode.addEventListener("click", qrcode.scan);
}


