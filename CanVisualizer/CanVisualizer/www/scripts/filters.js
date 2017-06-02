
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

function getProperties() {

    for (var i = 0; i < PropertyList.length; i++) {

        var elemDiv = document.createElement('div');
        elemDiv.className += 'groupdiv';
        var elemLblName = document.createElement('label');
        elemLblName.className += 'lbl';
        elemLblName.innerHTML = PropertyList[i][0];
        var elemLblSwitch = document.createElement('label');
        elemLblSwitch.className += 'switch';
        var elemInput = document.createElement('input');
        elemInput.type = 'checkbox';
        elemInput.name = PropertyList[i][0];
       
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

$("#checkbox-container :checkbox").on("change", function () {
    alert("The checkbox with the ID '" + this.name + "' changed");
});


function confirmProperties() {
    bluetooth.sendMessage();
}