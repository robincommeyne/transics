
var bluetooth = {
    macAddress: "00:00:00:00:00:00",  // get your mac address from bluetoothSerial.list
    chars: "",

    /*
        Connects if not connected, and disconnects if connected:
    */
    manageConnection: function () {

        // connect() will get called only if isConnected() (below)
        // returns failure. In other words, if not connected, then connect:
        var connect = function () {
            // if not connected, do this:
            // clear the screen and display an attempt to connect
            bluetooth.clear();
            bluetooth.display("Attempting to connect. " +
                "Make sure the serial port is open on the target device.");
            // attempt to connect:
            bluetoothSerial.connect(
                bluetooth.macAddress,  // device to connect to
                bluetooth.openPort,    // start listening if you succeed
                bluetooth.showError    // show the error if you fail
            );
        };

        // disconnect() will get called only if isConnected() (below)
        // returns success  In other words, if  connected, then disconnect:
        var disconnect = function () {
            bluetooth.display("attempting to disconnect");
            // if connected, do this:
            bluetoothSerial.disconnect(
                bluetooth.closePort,     // stop listening to the port
                bluetooth.showError      // show the error if you fail
            );
        };

        // here's the real action of the manageConnection function:
        bluetoothSerial.isConnected(disconnect, connect);
    },
    /*
        subscribes to a Bluetooth serial listener for newline
        and changes the button:
    */
    openPort: function () {
        // if you get a good Bluetooth serial connection:
        bluetooth.display("Connected to: " + bluetooth.macAddress);

        // change the button's name:
        connectButton.innerHTML = "Disconnect";
        // set up a listener to listen for newlines
        // and display any new data that's come in since
        // the last newline:

        bluetoothSerial.subscribeRawData(function (data) {
            var bytes = new Uint8Array(data);
            bluetooth.display(new TextDecoder("utf-8").decode(bytes));
        }, bluetooth.display("subscribe error"));
    },

    /*
        unsubscribes from any Bluetooth serial listener and changes the button:
    */
    closePort: function () {
        // if you get a good Bluetooth serial connection:
        bluetooth.display("Disconnected from: " + bluetooth.macAddress);
        // change the button's name:
        connectButton.innerHTML = "Connect";
        // unsubscribe from listening:
        bluetoothSerial.unsubscribe(
                function (data) {
                    bluetooth.display(data);
                },
                bluetooth.showError
        );
    },
    /*
        appends @error to the message div:
    */
    showError: function (error) {
        bluetooth.display(error);
    },

    /*
        appends @message to the message div:
    */
    display: function (message) {
        var display = document.getElementById("message"), // the message div
            lineBreak = document.createElement("br"),     // a line break
            label = document.createTextNode(message);     // create the label

        display.appendChild(lineBreak);          // add a line break
        display.appendChild(label);              // add the message node
    },
    /*
        clears the message div:
    */
    clear: function () {
        var display = document.getElementById("message");
        display.innerHTML = "";
    },

    sendMessage: function () {
        bluetoothSerial.write("test");
    }
};      // end of app