function IntervalChange() {
    var SetInterval = document.getElementById("interval").value;
    sessionStorage.setItem('readinterval', SetInterval);
}

function UnitChange() {
    var SetUnit = document.getElementById("unit").value;
    sessionStorage.setItem('unitconversion', SetUnit);
}

function settingsHome() {
    goToPage("index.html");
    checkConnection();
}