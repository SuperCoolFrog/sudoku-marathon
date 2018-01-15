let component = ReasonReact.statelessComponent("Continue");

let make = (
  ~continue,
  ~highestPoints,
  ~currentPoints,
  _children
) => {
  ...component,
  render: (_self) => {
    let displayHighestPoints = "Highest: " ++ string_of_int(highestPoints);
    let displayCurrentPoints = "Current: " ++ string_of_int(currentPoints);

    <div className="continue">
      <div className="continue__highest-points">
        {ReasonReact.stringToElement(displayHighestPoints)}
      </div>
      <div className="continue__current-points">
        {ReasonReact.stringToElement(displayCurrentPoints)}
      </div>
      <div className="continue__continue">
        <button onClick=continue>{ReasonReact.stringToElement("Continue")}</button>
      </div>
    </div>
  }
};