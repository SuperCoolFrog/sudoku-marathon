let component = ReasonReact.statelessComponent("GameOver");

let make = (_children) => {
  ...component,
  render: (_self) => <div className="game-over">{ReasonReact.stringToElement("Game Over")}</div>
};