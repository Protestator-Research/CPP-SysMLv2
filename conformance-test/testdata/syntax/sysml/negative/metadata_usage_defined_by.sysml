// expect: error
// `defined by` is not allowed in a metadata usage (only `:` or `typed by`).
metadata def M;
part def P {
    metadata n defined by M;
}
