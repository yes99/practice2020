const tr1 = document.getElementById('tr1');
const tr2 = document.getElementById('tr2');
const tr3 = document.getElementById('tr3');
const trs = [tr1, tr2, tr3];
const tds = [];
let turn = 'X';

const marking = function(event) { //indexOf  문자내에서 특정한 문자열의 index 값을 리턴한다
    //event.target 으로 이벤트 객체를 받아옵니다
    //디버깅? 로그에다가 이거저거 써주고만 있으니까

    const trNumber = trs.indexOf(event.target.parentNode);
    console.log('trNumber', trNumber);
    const tdNumber = tds[trNumber].indexOf(event.target);
    console.log('tdNumber', tdNumber);

    //if (tds[trNumber][tdNumber].textContent !== '') 
    if (tds[trNumber][tdNumber].innerText !== '') { // 칸이 이미 채워져 있는가?
        console.log('Not empty');
    } else {
        //비어 있지 않을 경우 채워넣는 과정
        console.log('Empty');
        //tds[trNumber][tdNumber].textContent = turn;
        tds[trNumber][tdNumber].innerText = turn; // 여기가 적어주는 과정
        if (turn === 'X') {
            turn = 'O';
        } else {
            turn = 'X';
        }
    }
};

for (let i = 0; i < 3; i++) {
    tds.push([]);
};

for (let j = 0; j < 3; j++) {
    tds[0].push(tr1.querySelectorAll('td').item(j));
    tds[1].push(tr2.querySelectorAll('td').item(j));
    tds[2].push(tr3.querySelectorAll('td').item(j));
};

for (let k = 0; k < 9; k++) {
    const td = document.getElementsByTagName('td').item(k);
    td.addEventListener('click', marking);
};