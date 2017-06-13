var RAWPropertyList = [];

function getRAWProperties() {

    for (var i = 0; i < RAWPropertyList.length; i++) {

        var elemDiv = document.createElement('div');
        elemDiv.className += 'groupdiv';
        var elemLblName = document.createElement('label');
        elemLblName.className += 'lbl';
        elemLblName.innerHTML = RAWPropertyList[i];
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

        var sp2 = document.getElementById("btnRAWConfirm");
        var parentDiv = sp2.parentNode;
        parentDiv.insertBefore(elemDiv, sp2);

    }
}

function confirmRAWProperties() {

}
function rawDataHome() {
    goToPage("index.html");
    checkConnection();
}
function rawFilters() {
    goToPage("rawfilters.html");
    checkConnection();
}