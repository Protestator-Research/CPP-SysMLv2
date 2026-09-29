// expect: valid
// SysML 8.2.2.18.1: StateDefBody = ';' | ( 'parallel' )? '{' StateBodyItem* '}'
abstract state def StateAction {
    doc /* A state action. */
    entry action entryAction :>> 'entry';
    do action doAction : Action :>> 'do';
    exit action exitAction : Action :>> 'exit';
    attribute :>> isTriggerDuring;
    ref state self : StateAction :>> Action::self;
    state a;
    state b;
    transition t1 first a then b;
}
state def P parallel { state x; state y; }
