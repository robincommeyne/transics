
var UpdatedRAWPropertyList = [[]];

function getRAWProperties() {

    var RAWProperties = JSON.parse(sessionStorage.getItem('checkboxValues'));
    var UpdatedRAWProperties = JSON.parse(sessionStorage.getItem('checkboxRAWValues'));

    if (RAWProperties === null){
        alert("Please select filters");
        goToPage('filters.html');
        getProperties();
    }
    else {

        if (UpdatedRAWProperties === null) {
            UpdatedRAWPropertyList = RAWProperties;
        } else {
            UpdatedRAWPropertyList = UpdatedRAWProperties;
        }

        for (var i = 0; i < RAWProperties.length; i++) {

            if (RAWProperties[i][1] === true) {

                var elemDiv = document.createElement('div');
                elemDiv.className += 'groupdiv';
                var elemLblName = document.createElement('label');
                elemLblName.className += 'lbl';
                elemLblName.innerHTML = RAWProperties[i][0];
                var elemLblSwitch = document.createElement('label');
                elemLblSwitch.className += 'switch';
                var elemInput = document.createElement('input');
                elemInput.type = 'checkbox';
                elemInput.name = RAWProperties[i][0];
                elemInput.value = RAWProperties[i][0];
                elemInput.checked = UpdatedRAWPropertyList[i][1];
                elemInput.onchange = function () { checkboxRAWChanged(this); };
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

function checkboxRAWChanged(checkboxObject) {
    for (var i = 0; i < UpdatedRAWPropertyList.length; i++) {
        if (UpdatedRAWPropertyList[i][0] === checkboxObject.name) {
            if (checkboxObject.checked)
                UpdatedRAWPropertyList[i][1] = true;
            else
                UpdatedRAWPropertyList[i][1] = false;
        }
    }

    sessionStorage.setItem('checkboxRAWValues', JSON.stringify(UpdatedRAWPropertyList));

}
function rawFiltersBack() {
    goToPage("rawdata.html");
    checkConnection();
}