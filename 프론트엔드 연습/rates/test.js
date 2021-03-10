var nations = ["KRW", "JPY", "USD", "EUR", "CNY"];
var rates = { "KRW": 1 };
var nat_dict = {
    "KRW": "한국(KRW)",
    "JPY": "일본(JPY)",
    "USD": "미국(USD)",
    "EUR": "유럽(EUR)",
    "CNY": "중국(CNY)"
};

function get_rate(nation) {
    var rate = document.getElementById(nation + "_rate");
    var xhr = new XMLHttpRequest();
    var rt;

    xhr.onload = function() {
        if (this.status === 200) {
            rt = JSON.parse(this.responseText);
            
            var cal_result = round_number(rt.rates.KRW);
            rate.innerText = cal_result;
            rates[nation] = cal_result;
        }
    }

    xhr.open("GET", "https://api.exchangeratesapi.io/latest?base=" + nation, true);

    xhr.send(null);
}


for (i = 1; i < 5; i++) {
    get_rate(nations[i]);
}

function singleCal() {
    var singleFrom = document.getElementById("singleFrom").value;
    var singleTo = document.getElementById("singleTo").value;
    var singleInput = document.getElementById("singleInput").value;
    var singleResult = document.getElementById("singleResult");

    console.log(singleFrom, singleTo, singleInput, singleResult);

    var cal_result = (singleInput * rates[singleFrom]) / rates[singleTo];
    //***여기 살짝 이해 안되는게 rates[singleTo]  근데 우리 위에 rates에는 한국밖에 없지 않나? 아니면 위에 get_rate에서 다 추가가 된 상태인거지?

    singleResult.value = round_number(cal_result);
}

function multiCal() {
    var multiFrom = document.getElementById("multiExBox0").value;
    var multiInput = document.getElementById("multiInput").value;
    var temp_result = multiInput * rates[multiFrom]; // 1차적으로 KRW로 바꾼 값

    for (i = 1; i < 5; i++) {
        var current_box = document.getElementById("multiExBox" + i);
        var current_value = document.getElementById("multiExValue" + i);
        // current_box.value = KRW, CNY, JPY
        var current_to = rates[current_box.value];
        var current_result = temp_result / current_to;

        current_value.innerText = round_number(current_result);
    }
}

function multiExChanged() {
    reset_multiEx(document.getElementById("multiExBox0").value);
}

// nation: 선택한 국가
function reset_multiEx(nation) {
    var i = 1;
    var tempBox, tempValue;
    //var nations = ["KRW", "JPY", "USD", "EUR", "CNY"];
    nations.forEach(function(nat) //***우리가 위에 nat_dic이라고 했는데이거 _ 뒤에는 딕셔너리라는 의미고 nat은 우리가 임의로 그냥 때다 쓸수 있는거야? */
        {
            if (nat != nation) {
                tempBox = document.getElementById("multiExBox" + i);
                tempValue = document.getElementById("multiExValue" + i);
                tempBox.value = nat;
                tempBox.innerText = nat_dict[nat];
                tempValue.value = nat;
                tempValue.innerText = "";
                i++;
            }
        });
}

function round_number(number) {
    return Math.round(number * 100) / 100;
}

reset_multiEx("KRW");