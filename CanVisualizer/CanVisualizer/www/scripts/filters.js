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
        elemInput.name = 'propertyCheckboxen';
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

function loopCheckboxes() {
    var elems = document.body.getElementsByTagName("*");
    var checkboxesChecked = [];
    for (var i = 0; i < elems.length; i++) {
        if (elems[i].type == 'checkbox') {
            checkboxesChecked.push(elems[i]);
        }
    }

    return checkboxesChecked.length > 0 ? checkboxesChecked : null;
}

function getCheckedBoxes(chkboxName) {
    var checkboxes = document.getElementsByName(chkboxName);
    var checkboxesChecked = [];
    //loop over them all
    for (var i = 0; i < checkboxes.length; i++) {
        //And stick the checked ones onto an array..;
        if (checkboxes[i].checked) {
            checkboxesChecked.push(checkboxes[i]);
        }
    }
    //return the array if it is non-empty, or null;
    return checkboxesChecked.length > 0 ? checkboxesChecked : null;
}

function confirmProperties() {
    var checkedBoxes = getCheckedBoxes("propertyCheckboxen");
    getRAWProperties(checkedBoxes);

}