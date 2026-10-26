// expect: valid
metadata def M;
part def P { metadata M; }
part p { metadata M; }
package Pkg { metadata M; }
