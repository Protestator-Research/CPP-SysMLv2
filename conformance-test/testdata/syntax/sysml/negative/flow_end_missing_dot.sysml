// expect: error
// SysML 8.2.2.16: FlowEndSubsetting 'tank' without '.' before the flow feature is rejected; the '.' is implied by spec examples such as 'src.src_out to tgt.tgt_in' and by FeatureChainPrefix ending in '.'
part def Fahrzeug { part tank; part motor; flow tank ausgang to motor eingang; }
