// expect: valid
// SysML 8.2.2.17.7: IfNode = ActionNodePrefix 'if' ExpressionParameterMember ActionBodyParameterMember ( 'else' ... )?
action def I {
    if n > 0 { }
    if n > 0 { perform a; }
    if n > 0 { } else { }
    if a { } else if b { }
    if a { } else if b { } else { perform c; }
}
