let cell_to_element = (rowNumber, initialSudoku, updateSudoku, cellIndex, cellValue) => {
  let value = string_of_int(cellValue);
  let index = rowNumber + cellIndex;
  let initialValue = initialSudoku[index];
  initialValue === 0 ? <EmptyCell index value updateSudoku /> : <Cell value />;
}; 

let component = ReasonReact.statelessComponent("CellBoardRow");

let make = (~initialSudoku, ~sudoku, ~rowNumber, ~sudokuSize, ~updateSudoku, _children) => {
  ...component,
  render: (_self) => {
    let index  = rowNumber * sudokuSize;
    let cellsInRow = Array.sub(sudoku, index, sudokuSize);
    let cellAsElements = Array.mapi(cell_to_element(index, initialSudoku, updateSudoku), cellsInRow);
    <div className="cell-board__row">(ReasonReact.arrayToElement(cellAsElements))</div>
  }
};