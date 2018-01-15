let component = ReasonReact.statelessComponent("GameWrapper");

let make = (
  ~sudoku,
  ~updateSudoku,
  ~updatePoints,
  ~initialSudoku,
  ~currentPoints,
  ~highestPoints,
  ~checkIfComplete,
  _children
) => {
  ...component,
  render: (_self) => 
    <div className="game-wrapper">
      <div className="game-wrapper__content">
        <CellBoard
          initialSudoku
          sudoku
          updateSudoku
        />
        <Points
          currentPoints=currentPoints
          highestPoints=highestPoints
          updatePoints
        />
      </div>
      <div className="game-wrapper__footer">
        <button onClick=checkIfComplete>{ReasonReact.stringToElement("Check")}</button> 
      </div>
    </div>
};