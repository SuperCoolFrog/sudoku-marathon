[@bs.val] external postMessage : string => unit = "";

let csvSudoku = Helpers.csv_of_array(SudokuHelper.makeSudoku(), (i) => string_of_int(i));

postMessage(csvSudoku);