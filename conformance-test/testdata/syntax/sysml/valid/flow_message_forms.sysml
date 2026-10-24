// expect: valid
// SysML 8.2.2.16: FlowDeclaration = UsageDeclaration ValuePart? ( 'of' FlowPayloadFeatureMember )? ( 'from' FlowEndMember 'to' FlowEndMember )? | FlowEndMember 'to' FlowEndMember; FlowEndSubsetting = referencedFeature = [QualifiedName] | referencedFeature = FeatureChainPrefix (the '.' after QualifiedName is not printed but implied by spec examples such as 'src.src_out to tgt.tgt_in' and by FeatureChainPrefix ending in '.', so the grammar requires it); MessageDeclaration analogous with MessageEventMember
part def Fahrzeug {
    part tank;
    part motor;
    flow of Kraftstoff from tank.ausgang to motor.eingang;
    flow Benzinfluss of Kraftstoff from tank.ausgang to motor.eingang;
    flow tank.ausgang to motor.eingang;
    flow Direkt from tank.ausgang to motor.eingang;
    flow of Kraftstoff from a::b.c to x.y.z;
    flow x.y.z to a.b.c;
    succession flow of Kraftstoff from tank.ausgang to motor.eingang;
    succession flow tank.ausgang to motor.eingang;
    flow;
    flow f : FT;
    flow of p : Kraftstoff [1] from tank.ausgang to motor.eingang;
    message of Signal from tank to motor;
    message Nachricht of Signal from tank to motor;
    message tank to motor;
    message from tank to motor;
    flow f : F of i : I from src.src_out to tgt.tgt_in;
    flow from weighVehicle.massMeasured to evaluatePassFail.massMeasured;
    message of ControlSignal from controller.sendControl to engine.receiveControl;
}
