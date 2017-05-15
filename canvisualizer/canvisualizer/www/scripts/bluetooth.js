//Handle all functions for bluetooth

document.addEventListener('deviceready', function () {

    new Promise(function (resolve) {
        bluetooth.initialize(resolve: true, statusReceiver: false});
}).then(initializeSuccess, handleError);
});

