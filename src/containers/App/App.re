type gameStateOption =
  | Start
  | Loading
  | Playing 
  | Continue
  | GameOver;

type state = {
  solvedSudoku: array(int),
  unsolvedSudoku: array(int),
  currentSudoku: array(int),
  currentPoints: int,
  highestPoints: int,
  gameState: gameStateOption,
  numberOfEmptyCells: int,
};

type cell = { index: int, value: int };

type action =
  | CheckIfSolved
  | FetchSudoku
  | UpdateCell(cell)
  | UpdatePoints(int)
  | UpdateHighestPoints(int)
  | UpdateSolvedSudoku(array(int))
  | UpdateUnsolvedSudoku(array(int))
  | UpdateCurrentSudoku(array(int))
  | UpdateGameState(gameStateOption);

let update = (sudoku, { index, value }) => {
  let copy = Array.copy(sudoku);
  Array.set(copy, index, value);
  copy
};

/* 17 is the minimum need for a unique solution */
/* https://www.reddit.com/r/askscience/comments/4r0ick/in_a_sudoku_puzzle_what_is_the_minimum_number_of/ */
/* Sticking with 20 to be safe */
let maxMissingBlocks = 81 - 20;

let basePoints = 30;
let pointsPerAnswer = 10;

let pointsForSudoku = (unsolvedSudoku) => {
  let additionalPoints =
    Array.fold_right((item, total) => item === 0 ? total + pointsPerAnswer : total,
      unsolvedSudoku, 0);
  basePoints + additionalPoints;
};

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    solvedSudoku: Array.make(81, 0),
    unsolvedSudoku: Array.make(81, 0),
    currentSudoku: Array.make(81, 0),
    currentPoints: 60,
    highestPoints: 60,
    gameState: Start,
    numberOfEmptyCells: 1
  },
  reducer: (action, state) =>
    switch action {
    | UpdateCell(cell) => ReasonReact.Update({...state, currentSudoku: update(state.currentSudoku, cell)})
    | UpdatePoints(delta) =>
      let {
        currentPoints,
        gameState,
        highestPoints,
      } = state;
      let updatedPoints = currentPoints + delta;

      ReasonReact.Update({
        ...state,
        currentPoints: updatedPoints,
        highestPoints: updatedPoints > highestPoints ? updatedPoints : highestPoints,
        gameState: updatedPoints < 1 ? GameOver : gameState
      })
    | UpdateHighestPoints(points) => ReasonReact.Update({...state, highestPoints: points})
    | CheckIfSolved =>
      let runCheck = (self) => {
        let {
          currentSudoku,
          unsolvedSudoku,
        } = state;
        if(SudokuHelper.isSolvedSudoku(currentSudoku)) {
          let pointsEarned = pointsForSudoku(unsolvedSudoku);
          self.ReasonReact.send(UpdatePoints(pointsEarned));
          self.ReasonReact.send(UpdateGameState(Continue));
        } else {
          self.ReasonReact.send(UpdatePoints(-pointsPerAnswer));
        }
      };
      ReasonReact.SideEffects((self) => runCheck(self));
    | UpdateSolvedSudoku(solvedSudoku) => ReasonReact.Update({...state, solvedSudoku })
    | UpdateUnsolvedSudoku(unsolvedSudoku) => ReasonReact.Update({...state, unsolvedSudoku })
    | UpdateCurrentSudoku(currentSudoku) => ReasonReact.Update({...state, currentSudoku })
    | UpdateGameState(gameState) => ReasonReact.Update({...state, gameState })
    | FetchSudoku =>
      let { numberOfEmptyCells } = state;
      let onMessage = (self, event) => {
        let data = JsWorker.getEventData(event);
        let solvedSudoku = Helpers.array_of_csv(data, (str) => int_of_string(str));
        let unsolvedSudoku = SudokuHelper.emptyRandomCells(solvedSudoku, numberOfEmptyCells);

        self.ReasonReact.send(UpdateSolvedSudoku(solvedSudoku));
        self.ReasonReact.send(UpdateUnsolvedSudoku(unsolvedSudoku));
        self.ReasonReact.send(UpdateCurrentSudoku(Array.copy(unsolvedSudoku)));
        self.ReasonReact.send(UpdateGameState(Playing));
      };

      ReasonReact.UpdateWithSideEffects({
        ...state,
        numberOfEmptyCells: numberOfEmptyCells + 1 <= maxMissingBlocks ? numberOfEmptyCells + 1 : maxMissingBlocks
      },
      (self) => JsWorker.startWork("CreateSudokuWorker", onMessage(self)));
    },
  render: ({ send, state }) => {
    let {
      unsolvedSudoku,
      currentSudoku,
      highestPoints,
      currentPoints,
      gameState,
    } = state;

    let updateSudoku = (index, value) => {
      send(UpdateCell({index, value}));
    };
    let checkIfComplete = (_) => {
      send(CheckIfSolved);
    };
    let updatePoints = (delta) => {
      send(UpdatePoints(delta));
    };

    let fetchNextGame = (_) => {
      send(UpdateGameState(Loading));
      send(FetchSudoku);
    };

    let displayByGameState = () => {
      switch gameState{
      | Start => <StartScreen startGame=fetchNextGame />
      | Loading => <Loading reloadNextBoard=fetchNextGame />
      | Playing =>
        <GameWrapper
          initialSudoku=unsolvedSudoku
          sudoku=currentSudoku
          updateSudoku=updateSudoku
          checkIfComplete
          highestPoints
          currentPoints
          updatePoints
        />
      | Continue =>
        <Continue
          continue=fetchNextGame 
          highestPoints
          currentPoints
          />
      | GameOver => <GameOver />
      }
    };

    <div className="app-container">
      <div className="app-container__main">
        {displayByGameState()}
      </div>
    </div>
  }
};