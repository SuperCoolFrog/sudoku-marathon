let csv_of_array= (arr, stringOfItem) => {
   let csv = Array.fold_right((item, str) => stringOfItem(item) ++ "," ++ str, arr, "");
   String.sub(csv, 0, String.length(csv) - 1)
};

let array_of_csv = (csvString, itemOfString) => {
  let rec buildList = (lst, str, index) => {
    let c = String.get(csvString, index);
    let isLastItem = (index + 1) >= String.length(csvString);
    
    if(isLastItem) {
      let item = itemOfString(str ++ String.make(1, c));
      [item, ...lst];
    } else if (c === ',' || isLastItem) {
      let item = itemOfString(str);
      let updatedList = [item, ...lst];
      buildList(updatedList, "", index + 1);
    } else {
      buildList(lst, str ++ String.make(1, c), index + 1);
    };
  };
  Array.of_list(List.rev(buildList([], "", 0)));
};