function IntervalChange() {
    var SetInterval = document.getElementById("interval").value;
    sessionStorage.setItem('readinterval', SetInterval);
}

function loadSettings() {
    var interval = sessionStorage.getItem('readinterval');
    if (interval === null) {
        document.getElementById('interval').selectedIndex = 0;
    } else {
        document.getElementById('interval').selectedIndex = interval-1;
    }
}

function UnitChange() {
    var SetUnit = document.getElementById("unit").value;
    sessionStorage.setItem('unitconversion', SetUnit);
}

function settingsHome() {
    goToPage("index.html");
    checkConnection();
}