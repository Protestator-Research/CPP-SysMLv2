// expect: valid
enum def ObdTrigger { Startup; Cyclic; OnCommand; }
metadata def ObdSignal {
    attribute serviceId : Natural;
    attribute pid : Natural[0..1];
    attribute trigger : ObdTrigger[0..1];
    attribute startOrder : Natural[0..1];
}
part def SUPPORTED_PIDS_01_20 {
    metadata ObdSignal {
        serviceId = 1;
        pid = 0;
        trigger = ObdTrigger::Startup;
        startOrder = 1;
    }
}
