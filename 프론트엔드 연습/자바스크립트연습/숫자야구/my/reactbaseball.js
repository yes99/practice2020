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
  gong = input.split("");
  var strike = 0;
  for (var i = 0; i < random.length; i++) {
    if (random[i] == gong[i]) {
      strike++;
    }
  }
  return strike;
}

function Ball(input) {
  gong = input.split("");
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
////////////////////////////////////////////////////////////////

class App extends React.Component {
  render() {
    return (
      <form id="form">
        <h1 id="status">start </h1>
        <input id="input" type="number" maxlength="4" />
        <button id="button" onClick= {ActionLinkd} >
          {" "}
          입력
        </button>
        <h1 id="trying"> start </h1>
      </form>
    );
  }
}


function ActionLink() {
  function handleClick(e) {
    e.preventDefault();
    console.log('The link was clicked.');
  }
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
  return (
    <a>
      Click me
    </a>
  );
}

ReactDOM.render(<App />, document.getElementById("root"));
