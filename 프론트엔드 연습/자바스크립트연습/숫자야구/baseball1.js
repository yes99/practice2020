const initAnswer = () => {
    const flags = Array(10).fill(false);
  
    let answer = '';
    while (answer.length < 4) {
      const random = parseInt(Math.random() * 10);
  
      if (!flags[random]) {
        answer += random;
        flags[random] = true;
      }
    }
    return answer;
  }
  
  const gameObject = {
    answer: initAnswer(),
    attempts: 0,
    isClear: false,
    end: false
  };
  
  const makeHintStr = (number, hint) => {
    return `<strong>시도 ${gameObject.attempts}</strong>: ${number}, <strong>결과</strong>: ${hint}`;
  }
  
  const askQuestion = (event) => {
    event.preventDefault();
  
    if (!gameObject.isClear && !gameObject.end) {
      const question = event.target[0].value;
      const questionBox = document.querySelector('.questionBox');
  
      if (!isFourDigits(question)) {
        alert('네 자리 숫자를 입력해주세요.');
      } else if (isOverlap(question)) {
        alert('각 자리수는 숫자가 중복되면 안됩니다.');
      } else {
        gameObject.attempts++;
        const result = makeHintStr(question, getHint(question, gameObject.answer));
        questionBox.innerHTML += `<div>${result}</div>`
  
        if (isInvalidToAttempt(gameObject.attempts) && !isCorrect(question, gameObject.answer)) {
          alert('도전 실패!');
          gameFailed();
        }
      }
    }
  
    event.target[0].value = '';
  }
  
  const isFourDigits = (number) => {
    return number.length === 4;
  }
  
  const isOverlap = (number) => {
    const digits = number.split('');
    const flags = Array(10).fill(false);
  
    return digits.map(digit => {
      const index = parseInt(digit);
      if (!flags[index]) {
        flags[index] = true;
      } else {
        return true;
      }
    }).includes(true);
  }
  
  const isCorrect = (number, answer) => {
    return number === answer;
  }
  
  const findStrikes = (number, answer) => {
    let strikes = 0;
    const digits = number.split('');
  
    digits.map((digit, index) => {
      if (digit === answer[index]) {
        strikes++;
      }
    })
    return strikes;
  }
  
  const findBalls = (number, answer) => {
    let balls = 0;
    const digits = number.split('');
    const flags = Array(10).fill(false);
  
    // answer에 포함되어있는 숫자 체크
    answer.split('').map(digit => {
      flags[parseInt(digit)] = true;
    });
  
    // ball 카운트
    digits.map((digit, index) => {
      if (answer[index] !== digit && flags[parseInt(digit)]) {
        balls++;
      }
    });
    return balls;
  }
  
  const getHint = (number, answer) => {
    if (isCorrect(number, answer)) {
      gameClaer();
      return '정답입니다!';
    }
  
    const strikes = findStrikes(number, answer);
    const balls = findBalls(number, answer);
    return 'S: ' + strikes + ',B: ' + balls;
  }
  
  const isInvalidToAttempt = (attempts) => {
    return attempts >= 10;
  }
  
  const gameClaer = () => {
    const answerBox = document.querySelector('.answerBox');
    answerBox.classList = answerBox.classList[0] + ' solved';
    gameObject.isClear = true;
    answerBox.innerHTML = gameObject.answer;
  }
  
  const gameFailed = () => {
    const answerBox = document.querySelector('.answerBox');
    answerBox.classList += ' failed';
    gameObject.end = true;
    answerBox.innerHTML = gameObject.answer;
  }