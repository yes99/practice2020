'use strict';


function Square (props){
	return (
		<td 
			style={{width:"50px", height:"50px", fontSize:"30px",fontWeight:"bold", textAlign:"center", border:"2px solid #444444"}} 
			className="square"
			onClick={props.onClick}
		>
			{props.value}
		</td>
	);
}

class Board extends React.Component {
	constructor(props){
		super(props);
		this.state = {
			squares: Array(9).fill(null),
			xIsNext: true,
		};
	}

	reset_board() {
		this.setState({
			squares: Array(9).fill(null),
			xIsNext: true,
		});
	}

	handleClick(i) {
		const squares = this.state.squares.slice();
		if (calculateWinner(squares)||squares[i]){
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
				value={this.state.squares[i]}
				onClick={() => this.handleClick(i)}
			/>
		);
	}
	render() {
		const winner = calculateWinner(this.state.squares);
		let status;
		if (winner) {
			status = 'Winner: ' + winner;
		} else {
			status = 'Player Turn: ' + (this.state.xIsNext ? 'X' : 'O');
		} 

	    return (
      	<div>
	        <div className="status">{status}</div>
        	<table>
        	<tbody>
	        	<tr className="board-row">
          			{this.renderSquare(0)}
          			{this.renderSquare(1)}
          			{this.renderSquare(2)}
        		</tr>
        		<tr className="board-row">
	          		{this.renderSquare(3)}
          			{this.renderSquare(4)}
          			{this.renderSquare(5)}
        		</tr>
        		<tr className="board-row">
	          		{this.renderSquare(6)}
          			{this.renderSquare(7)}
	          		{this.renderSquare(8)}
        		</tr>
        	</tbody>
        	</table>
			<button onClick={()=>this.reset_board()}>
			"reset"
			</button>
      	</div>
    );
  }
}

class Game extends React.Component {
	render(){
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
		)
	}

}

function calculateWinner(squares){
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
  for (let i = 0; i < lines.length; i++){
  	const [a, b, c] = lines[i];
  	if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]){
  		return squares[a];
  	}
  }
  return null;
}

ReactDOM.render(
	<Game />,
	document.getElementById('root')
);