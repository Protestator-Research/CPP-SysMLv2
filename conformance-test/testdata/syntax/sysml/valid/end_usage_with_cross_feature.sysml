// expect: valid
// SysML 8.2.2.6.2: EndUsagePrefix = 'end' ( OwnedCrossFeatureMember )?, followed by the kind keyword of the end usage
connection def HubDeviceConnection {
    end connectingHub [0..1] ordered part hub : Hub;
    end connectedDevices [1..*] part device : Device;
    end [1] item owner : Owner;
    end occurrence source : Occurrence :>> Message::source, FlowTransfer::source;
    end port p : P :>> Base::p;
    end part x : X crosses y.z;
    end part w : W => v.u;
    end item t;
    attribute bandwidth : Real;
}
