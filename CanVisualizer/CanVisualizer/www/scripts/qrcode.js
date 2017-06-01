/*
    Handles QR code reading and set macAddress from the raspberry pi
*/
var qrcode = {
    scan: function () {
        cordova.plugins.barcodeScanner.scan(
            function (result) {
                if (!result.cancelled) {
                    if (result.format == "QR_CODE") {
                        alert("We got a QR code\n" +
                              "Result: " + result.text + "\n" +
                              "Format: " + result.format + "\n" +
                              "Cancelled: " + result.cancelled);
                        bluetooth.macAddress = result.text.toString();
                        bluetooth.manageConnection();

                    }
                }
            },
            function (error) {
                alert("Scanning failed: " + error);
            }
        );
    }
};