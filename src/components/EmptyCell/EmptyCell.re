let component = ReasonReact.statelessComponent("EmptyCell");

let make = (~index, ~value, ~updateSudoku, _children) => {
  let change = (event) => {
    let targetVal = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;
    let valAsInt = targetVal === "" ? 0 : int_of_string(targetVal);
    updateSudoku(index, valAsInt);
  };
  
  let focus = (event) => {
    let target = ReactDOMRe.domElementToObj(ReactEventRe.Focus.target(event));
    target##select();
  };

  {
    ...component,
    render: (_self) => {
      let inputVal = value === "0" ? "" : value;
      <div className="cell-board__empty-cell">
        <input value=inputVal onChange=change onFocus=focus maxLength=1 />
      </div>
    }
  }
};