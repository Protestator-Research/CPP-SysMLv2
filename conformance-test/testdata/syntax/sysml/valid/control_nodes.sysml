// expect: valid
action def Flow {
    first start then m;
    merge m;
    then d;
    decide d;
    then j;
    join j;
    then f;
    fork f;
    then done;
}

action def Anonymous {
    merge;
    decide;
    join;
    fork;
    decide { }
}

action def ThenMerge {
    action a;
    action b;
    first a;
    then merge;
    then b;
}
