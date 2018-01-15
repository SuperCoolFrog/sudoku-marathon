let interval = 1000;
let pointsDelta = -1;

type state = {
  intervalId: ref(option(Js.Global.intervalId))
};


let component = ReasonReact.reducerComponent("Points");

let make = (~currentPoints, ~highestPoints, ~updatePoints, _children) => {
  
  let updatePoints = () => {
      Js.Global.setInterval((_) => updatePoints(pointsDelta), interval);
  };

  {
    ...component,
    initialState: () => { intervalId: ref(None)},
    reducer: ((), _state) => ReasonReact.NoUpdate,
    didMount: (self) => {
      self.state.intervalId := Some(updatePoints());
      ReasonReact.NoUpdate
    },
    willUnmount: self => {
      switch (self.state.intervalId^) {
      | Some(id) => Js.Global.clearInterval(id)
      | None => ()
      }
    },
    render: (_self) => {
      let displayHighestPoints = "Highest: " ++ string_of_int(highestPoints);
      let displayCurrentPoints = "Current: " ++ string_of_int(currentPoints);
      <div className="points">
        <div className="highest-points">
          {ReasonReact.stringToElement(displayHighestPoints)}
        </div>
        <div className="current-points">
          {ReasonReact.stringToElement(displayCurrentPoints)}
        </div>
      </div>
    }
  };
};