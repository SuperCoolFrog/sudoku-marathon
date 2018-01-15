type workerEvent = Js.t({. data: string });
type worker = Js.t({
  .
  [@bs.set] onmessage: (workerEvent) => unit
});
[@bs.new] external createWorker : string => worker = "Worker";

let getEventData = (event: workerEvent) => event##data;

let startWork = (workerModuleName, onMessage) => {
  let nuWorker = createWorker("http://localhost:8080/build/" ++ workerModuleName ++ ".bs.js");
  nuWorker##onmessage #= onMessage;
};