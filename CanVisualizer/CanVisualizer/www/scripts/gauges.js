var timer;
var storagelist = ["EngineLoad","EngineCoolantTemp","EngineRPM", "VehicleSpeed","FuelLevel","EngineFuelRate", "ThrottlePosition"];
var labellist = ["lblEngineLoad", "lblTemperature", "lblRpm", "lblSpeed", "lblFuelLevel", "lblFuelRate", "lblThrottle"];
var spanlist = ["spanEngineLoad", "spanTemperature", "spanRpm", "spanSpeed", "spanFuelLevel", "spanFuelRate", "spanThrottle"];
var unitlist = [" %", " °C", " rpm", " km/h", " %", " L/min", " %"];
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
    var interval = sessionStorage.getItem('readinterval');
    timer = setInterval(gaugeTimerTick, interval * 1000);
}

function gaugeTimerTick() {
    

    for (var i = 0; i < storagelist.length; i++) {
        try {
            var lbl = document.getElementById(labellist[i]);
            var value = sessionStorage.getItem(storagelist[i])
            lbl.innerText = value.toString() + unitlist[i];
            var span = document.getElementById(spanlist[i]);
            span.style.width = value + "%";
            
        }
        catch (err) {
            console.log(err.message);
        }
    }
}