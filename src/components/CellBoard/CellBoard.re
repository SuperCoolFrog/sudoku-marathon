let cell_to_element = (cellValue: int) => {
  let value = string_of_int(cellValue);
  <Cell value />
}; 

let size_of_sudoku = (sudoku) => int_of_float(sqrt(float_of_int(Array.length(sudoku))));

let component = ReasonReact.statelessComponent("CellBoard");

let cellRows = (initialSudoku, sudoku, updateSudoku) => {
  let sudokuSize = size_of_sudoku(sudoku);
  let rec makeRows = (rows, rowNumber) => {
    let row = <CellBoardRow initialSudoku sudoku rowNumber sudokuSize updateSudoku />;
    let updatedRows = [row, ...rows];
    let nextRow = rowNumber + 1;
    if (nextRow < sudokuSize) {
      makeRows(updatedRows, nextRow);
    } else {
      updatedRows
    }
  };
  Array.of_list(makeRows([], 0));
};

let make = (~initialSudoku, ~sudoku, ~updateSudoku, _children) => {
  ...component,
  render: (_self) => {
    let rows = cellRows(initialSudoku, sudoku, updateSudoku);
    <div className="cell-board">(ReasonReact.arrayToElement(rows))</div>
  }
};