var graphMemory = [];
var graphTsMemory = [];
var GraphValue;
var GraphTs;
var myBar;
var storagelist = ["EngineLoad", "EngineCoolantTemp", "EngineRPM", "VehicleSpeed", "FuelLevel", "EngineFuelRate", "ThrottlePosition"];

var timerGraph;
function startGraphTimer() {
    var interval = sessionStorage.getItem('readinterval');
    var timer;
    if (interval === null) {
        timer = 1000;
    } else {
        timer = interval * 1000;
    }
    timerGraph = setInterval(GraphTimer, timer);
}


function GraphTimer() {
    GraphTs = sessionStorage.getItem("EngineRPMTs");
    GraphValue = sessionStorage.getItem("EngineRPM");

    if (graphMemory.length < 20) {
        graphTsMemory.push(GraphTs);
        graphMemory.push(GraphValue);
    } else {
        graphTsMemory.shift();
        graphMemory.shift();
    }
    myBar.update();
}

var config = {
    type: 'line',
    data: {
        labels: graphTsMemory,
        datasets: [{
            label: "Value",
            backgroundColor: window.chartColors.orange,
            borderColor: window.chartColors.orange,
            data: graphMemory,
            fill: false,
        }]
    },
    options: {
        maintainAspectRatio: false,
        responsive: true,
        title: {
            display: false,
            text: 'Line Chart'
        },
        tooltips: {
            mode: 'index',
            intersect: false,
        },
        hover: {
            mode: 'nearest',
            intersect: false
        },
        scales: {
            xAxes: [{
                display: true,
                scaleLabel: {
                    display: false,
                    labelString: 'Month'
                }
            }],
            yAxes: [{
                display: true,
                scaleLabel: {
                    display: false,
                    labelString: 'Value'
                }
            }]
        }
    }
};
function graphLoaded() {
    var ctx = document.getElementById("canvas").getContext("2d");
    myBar = new Chart(ctx, config);
};


var UpdatedGraphPropertyList = [[]];
function loadFilters() {
    var GraphProperties = JSON.parse(sessionStorage.getItem('checkboxValues'));
    var UpdatedGraphProperties = JSON.parse(sessionStorage.getItem('checkboxGraphValues'));

    if (GraphProperties === null) {
        alert("Please select filters");
        goToPage('filters.html');
        getProperties();
    }
    else {

        if (UpdatedGraphProperties === null) {
            UpdatedGraphPropertyList = GraphProperties;
        } else {
            UpdatedGraphPropertyList = UpdatedGraphProperties;
        }

        for (var i = 0; i < GraphProperties.length; i++) {

            if (GraphProperties[i][1] === true) {

                var elemDiv = document.createElement('div');
                elemDiv.className += 'groupdiv';
                var elemLblName = document.createElement('label');
                elemLblName.className += 'lbl';
                elemLblName.innerHTML = GraphProperties[i][0];
                var elemLblSwitch = document.createElement('label');
                elemLblSwitch.className += 'switch';
                var elemInput = document.createElement('input');
                elemInput.type = 'checkbox';
                elemInput.name = GraphProperties[i][0];
                elemInput.value = GraphProperties[i][0];
                elemInput.checked = UpdatedGraphPropertyList[i][1];
                elemInput.onchange = function () { checkboxGraphChanged(this); };
                var elemDivSwitch = document.createElement('div');
                elemDivSwitch.classList.add('slider');
                elemDivSwitch.classList.add('round');

                elemLblSwitch.appendChild(elemInput);
                elemLblSwitch.appendChild(elemDivSwitch);
                elemDiv.appendChild(elemLblName);
                elemDiv.appendChild(elemLblSwitch);

                document.getElementById('content').appendChild(elemDiv);
            }
        }
    }
}

function checkboxGraphChanged(checkboxObject) {
    for (var i = 0; i < UpdatedGraphPropertyList.length; i++) {
        if (UpdatedGraphPropertyList[i][0] === checkboxObject.name) {
            if (checkboxObject.checked)
                UpdatedGraphPropertyList[i][1] = true;
            else
                UpdatedGraphPropertyList[i][1] = false;
        }
    }

    sessionStorage.setItem('checkboxGraphValues', JSON.stringify(UpdatedGraphPropertyList));
}

function graphHome() {
    goToPage("index.html");
    clearInterval(timerGraph);
    checkConnection();
}
