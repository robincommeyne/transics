var timer;
var storagelist = ["EngineLoad","EngineCoolantTemp","EngineRPM", "VehicleSpeed","FuelLevel","EngineFuelRate", "ThrottlePosition"];
var labellist = ["lblEngineLoad", "lblTemperature", "lblRpm", "lblSpeed", "lblFuelLevel", "lblFuelRate", "lblThrottle"];
function gaugesHome() {
    goToPage("index.html");
    clearInterval(timer);
    checkConnection();
}
function openAdvancedGauges() {

    goToPage("advancedgauges.html");
    checkConnection();
}


function GaugeTimer() {
    timer = setInterval(gaugeTimerTick, 1000)

}

function gaugeTimerTick() {
    

    for (var i = 0; i < storagelist.length; i++) {
        try {
            var lbl = document.getElementById(labellist[i]);
            lbl.innerText = sessionStorage.getItem(storagelist[i]).toString();
            
        }
        catch (err) {
            console.log(err.message);
        }
    }
}