
var bluetooth = {
    macAddress: "00:00:00:00:00:00",  // get your mac address from bluetoothSerial.list
    chars: "",
    status: "disconnected",


    /*
        Connects if not connected, and disconnects if connected:
    */
    manageConnection: function () {

        // connect() will get called only if isConnected() (below)
        // returns failure. In other words, if not connected, then connect:
        var connect = function () {
            qrcode.scan();
            // if not connected, do this:
            // clear the screen and display an attempt to connect
            bluetooth.clear();
            alert("Attempting to connect. " +
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
            alert("attempting to disconnect");
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
        alert("Connected to: " + bluetooth.macAddress);

        bluetooth.status = "connected";
        // change the button's name:
        btnConnect.innerHTML = "";
        var elem = document.createElement("img");
        elem.setAttribute("src", "images/connect.png");
        elem.setAttribute("height", "30");
        btnConnect.appendChild(elem);
        btnConnect.innerHTML = btnConnect.innerHTML + "<br /><br />Disconnect";
        // set up a listener to listen for newlines
        // and display any new data that's come in since
        // the last newline:

        bluetoothSerial.subscribeRawData(function (data) {
            var bytes = new Uint8Array(data);
            bluetooth.display(new TextDecoder("utf-8").decode(bytes));
        }, alert("subscribe error"));
    },

    /*
        unsubscribes from any Bluetooth serial listener and changes the button:
    */
    closePort: function () {
        // if you get a good Bluetooth serial connection:
        alert("Disconnected from: " + bluetooth.macAddress);
        bluetooth.status = "disconnected";
        // change the button
        btnConnect.innerHTML = "";
        var elem = document.createElement("img");
        elem.setAttribute("src", "images/disconnect.png");
        elem.setAttribute("height", "30");
        btnConnect.appendChild(elem);
        btnConnect.innerHTML = btnConnect.innerHTML + "<br /><br />Connect";
        // unsubscribe from listening:
        bluetoothSerial.unsubscribe(
                function (data) {
                    alert(data);
                },
                bluetooth.showError
        );
    },
    /*
        appends @error to the message div:
    */
    showError: function (error) {
        alert(error);
    },

    /*
        appends @message to the message div:
    */
    display: function (message) {
        //var display = document.getElementById("console"), // the message div
        //    lineBreak = document.createElement("br"),     // a line break
        //    label = document.createTextNode(message);     // create the label

        //display.appendChild(lineBreak);          // add a line break
        //display.appendChild(label);              // add the message node
        sessionStorage.setItem("data", message);
    },
    /*
        clears the message div:
    */
    clear: function () {
        //var display = document.getElementById("console");
        //display.innerHTML = "";
    },

    sendMessage: function () {
        bluetoothSerial.write("test");
    }
};      // end of app