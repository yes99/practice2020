var body = document.body;

var num_Arr = [];

var count = 1;

function myfunc() {
    while (num_Arr.length < 4) {
        var picked = Math.floor(Math.random() * 10);

        if ((picked != 0) && (isAlreadyExist(picked))) {
            num_Arr.push(picked);
        }
    }
}


function isAlreadyExist(num) {
    for (var i = 0; i < num_Arr.length; i++) {
        if (num === num_Arr[i]) {
            return false;
        }
    }
    return true;
}

function strikeOrBall(myAns) {
    my_Arr = myAns.split('');
    var strike = 0;
    var ball = 0;
    for (var i = 0; i < num_Arr.length; i++) {
        if (num_Arr[i] == my_Arr[i]) {
            strike++;
        }
        for (var j = 0; j < my_Arr.length; j++) {
            if (j == i) {
                continue;
            }
            else if (num_Arr[i] == my_Arr[j]) {
                ball++;
            }
        }
    }
    result.textContent = 'strike: ' + strike + ', ball: ' + ball;
    myLog.innerHTML += (count++) + '. My Answer: ' + myAns + ', strike: ' + strike + ', ball: ' + ball + '<br/>';
}

myfunc();

console.log(num_Arr);
var result = document.createElement('h1');
body.append(result);

var form = document.createElement('form');
body.append(form);

var textbox = document.createElement('input');
textbox.type = 'number';
textbox.maxLength = 4;
form.append(textbox);

var button = document.createElement('button');
button.textContent = '입력';
form.append(button);

var Rbutton = document.createElement('button');
Rbutton.textContent = '다시하기';
body.append(Rbutton);

var myLog = document.createElement('div');
myLog.innerHTML = "<기록>" + '<br/>';
body.append(myLog);

form.addEventListener('submit', function callback(e) {
    e.preventDefault();
    //새로고침 방지
    if (textbox.value.length != 4) 
    {
        textbox.value='';
    }
    else {
        var myAnswer = textbox.value;
        console.log(myAnswer);
        var myS = textbox.value.split('');
        if (myAnswer === num_Arr.join('')) {
            result.textContent = '홈런';
        }
        else 
        {
            strikeOrBall(myAnswer);
        }
    }
});

Rbutton.addEventListener('click', function () {
    result.textContent = '';
    textbox.value = '';
    num_Arr = [];
    myLog.innerHTML = '';
    count = 1;
    myfunc();
    console.log(num_Arr);
})