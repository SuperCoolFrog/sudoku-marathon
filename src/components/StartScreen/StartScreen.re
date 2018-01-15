
let component = ReasonReact.statelessComponent("StartScreen");

let make = (~startGame, _children) => {
  ...component,
  render: (_self) =>
    <div className="start-screen">
      <h3>{ReasonReact.stringToElement("Sudoku Marathon")}</h3>
      <div className="start-screen__text">
        <ul>
          <li>{ReasonReact.stringToElement("Everytime you fail a check you will lose 10 points")}</li>
          <li>{ReasonReact.stringToElement("Successful check will allow to continue")}</li>
        </ul>
      </div>
      <div className="start-screen__start">
        <button onClick=startGame>{ReasonReact.stringToElement("Start")}</button>
      </div>
    </div>
};