var PropertyList = ["Engine Load","Coolant Temp","Fuel Pressure","Intake Map","RPM","Speed","Timing Advance","Intake Air Temp","MAF","Fuel Level","Bar Pressure","Fuel Rate"];

function getProperties() {

    for (var i = 0; i < PropertyList.length; i++) {

        var elemDiv = document.createElement('div');
        elemDiv.className += 'groupdiv';
        var elemLblName = document.createElement('label');
        elemLblName.className += 'lbl';
        elemLblName.innerHTML = PropertyList[i];
        var elemLblSwitch = document.createElement('label');
        elemLblSwitch.className += 'switch';
        var elemInput = document.createElement('input');
        elemInput.type = 'checkbox';
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

function confirmProperties() {

}