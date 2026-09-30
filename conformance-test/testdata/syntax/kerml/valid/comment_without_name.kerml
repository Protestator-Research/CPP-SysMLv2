// expect: valid
// KerML 8.2.3.3.2: Comment = ( 'comment' Identification ( 'about' Annotation ( ',' Annotation )* )? )? ...; the Identification may be empty
class A; class B; class C;
comment about A, B /* about two classes */
comment about C /* about one class */
comment cmt about A /* named */
comment /* anonymous */
