let component = ReasonReact.statelessComponent("Loading");

let make = (~reloadNextBoard, _children) => {
  ...component,
  render: (_self) => {
    <div className="loading">
      <div className="sk-cube-grid">
        <div className="sk-cube sk-cube1"></div>
        <div className="sk-cube sk-cube2"></div>
        <div className="sk-cube sk-cube3"></div>
        <div className="sk-cube sk-cube4"></div>
        <div className="sk-cube sk-cube5"></div>
        <div className="sk-cube sk-cube6"></div>
        <div className="sk-cube sk-cube7"></div>
        <div className="sk-cube sk-cube8"></div>
        <div className="sk-cube sk-cube9"></div>
      </div>
      <div className="loading__reload">
        <p>{ReasonReact.stringToElement("If this is taking more than a few seconds please click to reload")}</p>
        <button onClick=reloadNextBoard>{ReasonReact.stringToElement("Reload")}</button>
      </div>
    </div>
  }
};