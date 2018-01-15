let component = ReasonReact.statelessComponent("Cell");

let make = (~value, _children) => {
  ...component,
  render: (_self) => <div className="cell-board__cell">{ReasonReact.stringToElement(value)}</div>
};