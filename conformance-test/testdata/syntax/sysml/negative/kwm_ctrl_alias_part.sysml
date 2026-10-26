// expect: error no-keyword-misuse
// 'part' after an alias without ';' starts a new statement
package P { alias A for B part def C; }
