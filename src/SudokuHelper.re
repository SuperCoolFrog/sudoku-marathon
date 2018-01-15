let sizeOfSudoku = (sudoku) => int_of_float(sqrt(float_of_int(Array.length(sudoku))));

let returnRow = (cell, sudoku) => (cell / sizeOfSudoku(sudoku));
let returnColumn = (cell, sudoku) => (cell mod sizeOfSudoku(sudoku));
/* Still hardcoded for 9x9 */
let returnBlock = (cell, sudoku) => ((returnRow(cell, sudoku) / 3) * 3) + (returnColumn(cell, sudoku) / 3);

let rec isPossibleRowCell = (number, row, sudoku, rowCell) =>  {
  let sudokuSize = sizeOfSudoku(sudoku);
  let rowCellValue = sudoku[row * sudokuSize + rowCell]; 
  rowCellValue == number ?
    false :
    rowCell + 1 < sudokuSize ?
      isPossibleRowCell(number, row, sudoku, rowCell + 1) :
      true
};
let isPossibleRow = (number, row, sudoku) => isPossibleRowCell(number, row, sudoku, 0);


let rec isPossibleColumnCell = (number, column, sudoku, columnCell) => {
  let sudokuSize = sizeOfSudoku(sudoku);
  let columnCellValue = sudoku[column + sudokuSize * columnCell]; 
  columnCellValue == number ?
    false :
    columnCell + 1 < sudokuSize ?
      isPossibleColumnCell(number, column, sudoku, columnCell + 1) :
      true
};
let isPossibleColumn = (number, column, sudoku) => isPossibleColumnCell(number, column, sudoku, 0);

/* Still hardcoded for 9x9 */
let rec isPossibleBlockCell = (number, block, sudoku, blockCell) => {
  let sudokuSize = sizeOfSudoku(sudoku);
  let index = (block/3) * 27 + (blockCell mod 3) + 9 * (blockCell/3) + 3 * (block mod 3);
  let blockCellValue = sudoku[index]; 
  blockCellValue == number ?
    false :
    blockCell + 1 < sudokuSize ?
      isPossibleBlockCell(number, block, sudoku, blockCell + 1) :
      true
};
let isPossibleBlock = (number, block, sudoku) => isPossibleBlockCell(number, block, sudoku, 0);

let isPossibleNumber = (cell, number, sudoku) => {
  let row = returnRow(cell, sudoku);
  let column = returnColumn(cell, sudoku);
  let block = returnBlock(cell, sudoku);
  isPossibleRow(number, row, sudoku) && isPossibleColumn(number, column, sudoku) && isPossibleBlock(number, block, sudoku);
};

let isCorrectRow = (row, sudoku) => {
  let sudokuSize = sizeOfSudoku(sudoku);
  let rowCells = Array.sub(sudoku, row * sudokuSize, sudokuSize);
  Array.sort((a, b) => a > b ? 1 : a < b ? -1 : 0, rowCells);
  let valuesMatch = Array.mapi((index, value) => index + 1 == value, rowCells);

  Array.fold_right((a, b) => a && b, valuesMatch, true);
};

let isCorrectColumn = (column, sudoku) => {
  let sudokuSize = sizeOfSudoku(sudoku);
  let columnCells = Array.make(sudokuSize, 0);
	for (i in 0 to sudokuSize - 1) {
		columnCells[i] = sudoku[column + i * sudokuSize];
	};
  Array.sort((a, b) => a > b ? 1 : a < b ? -1 : 0, columnCells);
  let valuesMatch = Array.mapi((index, value) => index + 1 == value, columnCells);

  Array.fold_right((a, b) => a && b, valuesMatch, true);
};

/* Still hardcoded for 9x9 */
let isCorrectBlock = (block, sudoku) => {
  let sudokuSize = sizeOfSudoku(sudoku);
  let blockCells = Array.make(sudokuSize, 0);
  for(i in 0 to sudokuSize - 1) {
    blockCells[i] = sudoku[(block/3)*27+(i mod 3)+9*(i/3)+3*(block mod 3)];
  };
  Array.sort((a, b) => a > b ? 1 : a < b ? -1 : 0, blockCells);
  let valuesMatch = Array.mapi((index, value) => index + 1 == value, blockCells);
  Array.fold_right((a, b) => a && b, valuesMatch, true);
};

let isSolvedSudoku = (sudoku) => {
  let sudokuSize = sizeOfSudoku(sudoku);
  let rec isSolvedSudoku = (i) => {
    i == sudokuSize ?
      true : 
      isCorrectBlock(i, sudoku) && isCorrectRow(i, sudoku) && isCorrectColumn(i, sudoku) ?
        isSolvedSudoku(i + 1) :
        false;
  };
  isSolvedSudoku(0);
};

let getPossibleValues = (cell, sudoku) => {
  let sudokuSize = sizeOfSudoku(sudoku);
  let possibleValues = Array.make(sudokuSize, 0); 
  for(i in 1 to sudokuSize) {
    if(isPossibleNumber(cell, i, sudoku)) {
      possibleValues[i-1] = i;
    }
  };
  Array.of_list(List.filter((value) => value !== 0, Array.to_list(possibleValues)));
};

let getRandomPossibleValue = (possible, cell) => {
  /* let randomPicked = int_of_float(random() *. float_of_int(Array.length(possible[cell])));
  possible[cell][randomPicked]; */
  possible[cell][0];
};

let scanSudokuForUnique = (sudoku) => {
  let sudokuSize = sizeOfSudoku(sudoku);
  let possible = Array.make(sudokuSize*sudokuSize, 0);
  Array.mapi((i, _) => sudoku[i] == 0 ? getPossibleValues(i, sudoku) : Array.make(0,0), possible)
};

let removeAttempt = (attempts, number) => {
  Array.of_list(Array.fold_right((attempt, acc) => attempt !== number ? [attempt, ...acc] : acc, attempts, []));
};

let getMinTupleArray = (arr, getValue) => {
	let rec getMinRec = (arr, getValue, currentMin, index) => {
      if(index < Array.length(arr)) {
      	let currentTuple = arr[index];
      	getValue(currentTuple) < getValue(currentMin) ?
        	getMinRec(arr, getValue, currentTuple, index + 1) :
        	getMinRec(arr, getValue, currentMin, index + 1);
      } else {
      	currentMin
      }
  	};
  	getMinRec(arr, getValue, arr[0], 1);
};

let nextRandom = (possibles) => {
  let mapped = Array.mapi((index, possible) => (index, Array.length(possible)), possibles);
  let filtered = Array.of_list(Array.fold_right((item, acc) => snd(item)!== 0 ? [item, ...acc] : acc, mapped, []));
  let min = getMinTupleArray(filtered, (tup) => snd(tup));
  let (cell, _) = min;
  cell
};

let printSudoku = (sudoku: array(int)) => {
  let rec printAsText = (text, i) => {
    if(i < Array.length(sudoku)) {
      let valToPrint = string_of_int(sudoku[i]);
      printAsText(text ++ valToPrint, i + 1);
    } else {
      text;
    }
  };
  Js.log(printAsText("", 0))
};

let possibleMovesExists = (possibles) => {
  Array.fold_right((possible, moveExists) => moveExists || Array.length(possible) > 0, possibles, false);
};

let solve = (initialSudoku) => {
  let rec solve = (sudoku, nextMove, savedMoves, savedSudokuStates) => {
    /* Check if completed */
    if(!isSolvedSudoku(sudoku)) {
      /* Check to see if last move ended up in a dead end */
      if(possibleMovesExists(nextMove)) {
        let nextTry = nextRandom(nextMove);
        let attempt = getRandomPossibleValue(nextMove, nextTry);

        sudoku[nextTry] = attempt;

        let scannedMove = scanSudokuForUnique(sudoku);

        if(Array.length(nextMove[nextTry]) > 1) {
          /* If the last move had other options, add then to save state */
          nextMove[nextTry] = removeAttempt(nextMove[nextTry], attempt);

          let moveToSave = Array.copy(nextMove);
          let stateToSave = Array.copy(sudoku);
          solve(sudoku, scannedMove, [moveToSave, ...savedMoves], [stateToSave, ...savedSudokuStates]);
        } else {
          solve(sudoku, scannedMove, savedMoves, savedSudokuStates);
        }
      } else {
        let move = List.hd(savedMoves);
        let restMoves = List.tl(savedMoves);
        let savedSudokuState = List.hd(savedSudokuStates);
        let restStates = List.tl(savedSudokuStates);

        solve(savedSudokuState, move, restMoves, restStates);
      }
    } else {
      sudoku;
    }
  };

  let initialSavedMoves = [];
  let initialSavedStates = [];
  solve(initialSudoku, scanSudokuForUnique(initialSudoku), initialSavedMoves, initialSavedStates);
};

let randomNumberList = (listSize, randomUpperBound) => {
  Random.self_init();
  let rec makeList = (list) => {
    let randInt = Random.int(randomUpperBound);
    if(List.exists((i) => i === randInt, list)) {
      makeList(list);
    } else {
      let size = List.length(list);
      let updatedList = [randInt, ...list];
      if(size + 1 < listSize) {
        makeList(updatedList);
      } else {
        updatedList
      }
    }
  };

  makeList([]);
};

let emptyRandomCells = (sudoku, numberOfCells) => {
  Random.self_init();
  let totalCells = Array.length(sudoku);
  let listOfCells = randomNumberList(numberOfCells, totalCells);
  let isIndexToClear = (index) => List.exists((indexToClear) => index === indexToClear, listOfCells);
  Array.mapi((index, cell) => isIndexToClear(index) ? 0 : cell, sudoku);
};

let makeSudoku = () => {
  Random.self_init();
  let randomStartingNumber = Random.int(9) + 1;
  let arr = Array.make(81, 0);
  arr[0] = randomStartingNumber;
  solve(arr);
};
