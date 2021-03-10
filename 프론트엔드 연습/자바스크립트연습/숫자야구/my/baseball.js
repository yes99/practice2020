var random = [];

//랜덤 숫자 네개 만들기
for (var i = 0; i < 4; i++) {
    var flag = 0;
    var pick = Math.floor(Math.random() * 10);
    for (j = 0; j < random.length; j++) {
        if (random[j] === pick) {
            flag = 1;
            break;
        }
    }
    if (flag != 1) {
        random.push(pick);
    } else {
        flag = 0;
        i--;
    }
}

console.log(random);

function Strike(input) {
    gong = input.split('');
    var strike = 0;
    for (var i = 0; i < random.length; i++) {
        if (random[i] == gong[i]) {
            strike++;
        }
    }
    return strike;
}

function Ball(input) {
    gong = input.split('');
    var ball = 0;
    for (var i = 0; i < random.length; i++) {
        for (var j = 0; j < gong.length; j++) {
            if (j == i) {
                continue;
            } else if (random[i] == gong[j]) {
                ball++;
            }
        }
    }
    return ball;
}

var input = document.getElementById("input"); // 넣을 공간
var status = document.getElementById("status"); //스트라이크 볼 나오는 창
var trying = document.getElementById("trying"); // 로그 표시
var button = document.getElementById("button"); //버튼
var form = document.getElementById("form"); //

form.addEventListener('submit', function callback(e) {
    e.preventDefault();
    //새로고침 방지
    //console.log(input, status, trying);
    if (input.value.length != 4) 
    {
        input.value='';
    }
    else{
        var myinput = input.value;
        console.log(myinput);
        if (myinput === random.join('')) 
        {
            console.log("홈런");
            trying.innerHTML = '';
            trying.innerHTML = '홈런';
        } else 
        {
            trying.innerHTML = trying.innerHTML+ Ball(myinput) + 'ball' + Strike(myinput) + 'strikes' + '<br>';
            //status.textContent = Ball(myinput) + 'ball' + Strike(myinput) + 'strikes'+ '<br>';
        }
    }
    
   

    //console.log(answer, random, answer === random.join(''));
    
    /*if(input.value.length != 4)
    {
        input.value = '';
    }
    else{

    }
    */
    //inputnum = parseInt(input);
    //console.log(inputnum);
    //alert("버튼을 누르셨습니다");
});

//console.log(random);