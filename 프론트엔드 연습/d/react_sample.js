'use strict';

/*
state = 변하는것
props = 변하지않는것
*/

class Box extends React.Component {
	render() {
		return (
			<td 
				style={{
					width:"50px", height:"50px", fontSize:"35px", 
					fontWeight:"bold", textAlign:"center", border:"2px solid #444444"
				}}
				onClick={this.props.onClick}
			> 
			{this.props.value}
			</td>
		)
	} 
}


class Game extends React.Component {
	constructor(props){
		super(props);
		this.state = {
			squares: Array(9).fill(null),
			turn: true
		}
	}

	reset_game(){
		this.setState({
			squares: Array(9).fill(null),
			turn: true
		});
	}

	handleClick(i){
		// this.state.squares[2] = null
		let newSquares = this.state.squares.slice()
		// newSquares[i]이 빈칸이 아니면 handleClick 메소드가 종료됨
		if (newSquares[i] != null || judge(newSquares)){  
			return;
		}
		newSquares[i] = this.state.turn ? 'X' : 'O';
		this.setState(
			{
				squares:newSquares,
				turn: !this.state.turn
			}
		)
	}

	renderSquare(i){
		return (
			<Box 
				value={this.state.squares[i]}
				onClick={()=>this.handleClick(i)}
			/>
		)
	}

	render() {
		let winner = judge(this.state.squares);
		let status;
		if (winner != null) {
			status = '승자: ' + winner;
		} else {
			status = (this.state.turn ? 'X' : 'O') + "의 차례";
		}
		return (
			<div>
			<div>{status}</div>
			<table> 
				<tbody>
					<tr>
						{this.renderSquare(0)}
						{this.renderSquare(1)}
						{this.renderSquare(2)}
					</tr>
					<tr>
						{this.renderSquare(3)}
						{this.renderSquare(4)}
						{this.renderSquare(5)}
					</tr>
					<tr>
						{this.renderSquare(6)}
						{this.renderSquare(7)}
						{this.renderSquare(8)}
					</tr>
				</tbody>
			</table>
			<button onClick={()=>this.reset_game()}>reset</button>
			</div>
		);
	}
}

function judge(squares){
	const lines = [
		[0, 1, 2],
		[3, 4, 5],
		[6, 7, 8],
		[0, 3, 6],
		[1, 4, 7],
		[2, 5, 8],
		[2, 4, 6],
		[0, 4, 8]
	]

	for (let i=0; i < lines.length; i++){
		const [a, b, c] = lines[i];
		// a = 2, b = 5, c= 8
		if( squares[a] != null && squares[a] == squares[b] && squares[a] == squares[c])
			return squares[a]
	}
	return null;
}

// ReactDOM.render(컴포넌트, 컨테이너); 
// 컨테이너에 컴포넌트를 보이게 해주는 것
ReactDOM.render(
	<Game />,
	document.getElementById('root')
);

