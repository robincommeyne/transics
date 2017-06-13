var MONTHS = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
var config = {
    type: 'line',
    data: {
        labels: ["January", "February", "March", "April", "May", "June", "July"],
        datasets: [{
            label: "My First dataset",
            backgroundColor: window.chartColors.red,
            borderColor: window.chartColors.red,
            data: [
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor()
            ],
            fill: false,
        }, {
            label: "My Second dataset",
            fill: false,
            backgroundColor: window.chartColors.blue,
            borderColor: window.chartColors.blue,
            data: [
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor(),
                randomScalingFactor()
            ],
        }]
    },
    options: {
        maintainAspectRatio: false,
        responsive: true,
        title: {
            display: false,
            text: 'Chart.js Line Chart'
        },
        tooltips: {
            mode: 'index',
            intersect: false,
        },
        hover: {
            mode: 'nearest',
            intersect: true
        },
        scales: {
            xAxes: [{
                display: true,
                scaleLabel: {
                    display: true,
                    labelString: 'Month'
                }
            }],
            yAxes: [{
                display: true,
                scaleLabel: {
                    display: true,
                    labelString: 'Value'
                }
            }]
        }
    }
};
function graphLoaded() {
    var ctx = document.getElementById("canvas").getContext("2d");
    window.myLine = new Chart(ctx, config);
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
    checkConnection();
}
