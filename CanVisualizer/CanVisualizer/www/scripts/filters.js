
var PropertyList = [
    ["Engine Load", false],
    ["Coolant Temp", false],
    ["Fuel Pressure", false],
    ["Intake Map", false],
    ["RPM", false],
    ["Speed", false],
    ["Timing Advance", false],
    ["Intake Air Temp", false],
    ["MAF", false],
    ["Fuel Level", false],
    ["Bar Pressure", false],
    ["Fuel Rate", false]
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
    bluetooth.sendMessage();
    alert("filters sent");
}
function filtersHome()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("content").innerHTML =
            this.responseText;
        }
    };
    xhttp.open("GET", "index.html", false);
    xhttp.send();
    checkConnection();
}

