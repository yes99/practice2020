const tr1 = document.getElementById('tr1');
const tr2 = document.getElementById('tr2');
const tr3 = document.getElementById('tr3');
const trs = [tr1, tr2, tr3];
const tds = [];
let turn = 'X';

const marking = function(event) {
    const trNumber = trs.indexOf(event.target.parentNode);
    console.log('trNumber', trNumber);
    const tdNumber = tds[trNumber].indexOf(event.target);
    console.log('tdNumber', tdNumber);

    if (tds[trNumber][tdNumber].textContent !== '') { // 칸이 이미 채워져 있는가?
        console.log('Not empty');
    } else {
        console.log('Empty');
        tds[trNumber][tdNumber].textContent = turn;
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