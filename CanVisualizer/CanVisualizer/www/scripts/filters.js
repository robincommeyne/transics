
var PropertyList = [
    ["Engine Load", false],
    ["Engine Coolant Temp", false],
    ["Fuel Pressure", false],
    ["Intake MAPressure", false],
    ["Engine RPM", false],
    ["Vehicle Speed", false],
    ["Timing Advance", false],
    ["Intake Air Temp", false],
    ["MAF air Flow Rate", false],
    ["Fuel Level", false],
    ["Barometric Pressure", false],
    ["Engine Fuel Rate", false],
    ["Throttle Position",false]
];

var UpdatedPropertyList = [[]];

function getProperties() {

    var data = JSON.parse(sessionStorage.getItem('checkboxValues'));

    if (data === null)
        UpdatedPropertyList = PropertyList;
    else
        UpdatedPropertyList = data;
    
    for (var i = 0; i < PropertyList.length; i++) {

        var elemDiv = document.createElement('div');
        elemDiv.className += 'groupdiv';
        var elemLblName = document.createElement('label');
        elemLblName.className += 'lbl';
        elemLblName.innerHTML = UpdatedPropertyList[i][0];
        var elemLblSwitch = document.createElement('label');
        elemLblSwitch.className += 'switch';
        var elemInput = document.createElement('input');
        elemInput.type = 'checkbox';
        elemInput.name = UpdatedPropertyList[i][0];
        elemInput.value = UpdatedPropertyList[i][0];
        elemInput.checked = UpdatedPropertyList[i][1];
        elemInput.onchange = function () { checkboxChanged(this);};
        var elemDivSwitch = document.createElement('div');
        elemDivSwitch.classList.add('slider');
        elemDivSwitch.classList.add('round');

        elemLblSwitch.appendChild(elemInput);
        elemLblSwitch.appendChild(elemDivSwitch);
        elemDiv.appendChild(elemLblName);
        elemDiv.appendChild(elemLblSwitch);

        var sp2 = document.getElementById("btnConfirm");
        var parentDiv = sp2.parentNode;
        parentDiv.insertBefore(elemDiv, sp2);

    }   
}

function checkboxChanged(checkboxObject) {
    for (var i = 0; i < UpdatedPropertyList.length; i++) {
        if (UpdatedPropertyList[i][0] === checkboxObject.name) {
            if (checkboxObject.checked)
                UpdatedPropertyList[i][1] = true;
            else
                UpdatedPropertyList[i][1] = false;
        }
    }

    sessionStorage.setItem('checkboxValues',JSON.stringify(UpdatedPropertyList));
}

function confirmProperties() {

    var readInterval = JSON.parse(sessionStorage.getItem('readinterval'));
    var data = JSON.parse(sessionStorage.getItem('checkboxValues'));
    var AllFilters = [[]];
    var Interval;

    if (data === null) {
        AllFilters = PropertyList;
    } else {
        AllFilters = data;
    }

    if (readInterval === null) {
        Interval = 1;
    } else {
        Interval = readInterval;
    }

    var completeJson = {};
    var Config = [];
    var Filters = [];

    completeJson.Config = Config;
    completeJson.Filters = Filters;
    
    var Description = "ReadInterval";
    var Value = Interval;
    var configset = {
        "Description": Description,
        "Value": Value
    }
    completeJson.Config.push(configset);

    for (var i = 0; i < AllFilters.length; i++) {
        var filter = {
            "Description": AllFilters[i][0].replace(/\s/g, ''),
            "Value": AllFilters[i][1]
        }
        completeJson.Filters.push(filter);
    }
    console.log(JSON.stringify(completeJson));
   
    bluetooth.sendMessage(JSON.stringify(completeJson));
    alert("filters sent");
}
function filtersHome()
{
    goToPage("index.html");
    checkConnection();
}

