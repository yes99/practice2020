import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';


function Square(props) {
  return (
    <button className="square" onClick={props.onClick}>
      {props.value}
    </button>
  );
}
  
class Board extends React.Component {
  constructor(props)
  {
    super(props);
    this.state={
      squares:Array(9).fill(null),
      xIsNext: true, 
    };
  }
handleClick(i)
{
  //squares 을 통째로 바꿈. 기본저긍로, 컴포넌트의 state를 바꾸는 것은 this.setState, 로 써서 하는것으로 되어있음.  
  //squares는 array .... this.setState는 하나에만 접근을 해서 바꾸는것이 불가능. 
  //slice() 라는 매소드 .... 배열에서 붙는것, 정확히는 slice(a,헐?b) a부터 b번째 까지 잘라서 새로운 배열. ()시에는 통째로 복사하려고 쓴느것. 
  const squares = this.state.squares.slice();
  if(calculateWinner(squares) || squares[i])
  {
    return;
  }
  squares[i] = this.state.xIsNext ? 'X' : 'O';
  this.setState({
    squares: squares,
    xIsNext: !this.state.xIsNext,
  });
}

renderSquare(i) {
    return (
          <Square 
            value ={this.state.squares[i]}
            onClick={() => this.handleClick(i)} 
          />
    );
  }

  render() {
    const winner = calculateWinner(this.state.squares);
    let status;
    if(winner)
    {
      status = 'Winner : ' + winner;
    }
    else
    {
      status = 'Next player: ' + (this.state.xIsNext ? 'X' : 'O');
    }

    return (
      <div>
        <div className="status">{status}</div>
        <div className="board-row">
          {this.renderSquare(0)}
          {this.renderSquare(1)}
          {this.renderSquare(2)}
        </div>
        <div className="board-row">
          {this.renderSquare(3)}
          {this.renderSquare(4)}
          {this.renderSquare(5)}
        </div>
        <div className="board-row">
          {this.renderSquare(6)}
          {this.renderSquare(7)}
          {this.renderSquare(8)}
        </div>
      </div>
    );
  }
}

class Game extends React.Component {
  render() {
    return (
      <div className="game">
        <div className="game-board">
          <Board />
        </div>
        <div className="game-info">
          <div>{/* status */}</div>
          <ol>{/* TODO */}</ol>
        </div>
      </div>
    );
  }
}

// ========================================

ReactDOM.render(
  <Game />,
  document.getElementById('root1')
);


function calculateWinner(squares) {
  const lines = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6],
  ];
  for (let i = 0; i < lines.length; i++) {
    const [a, b, c] = lines[i];
    if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
      return squares[a];
    }
  }
  return null;
}