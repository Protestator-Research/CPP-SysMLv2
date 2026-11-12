// expect: valid
package P {
    feature a = "plain";
    feature b = "with \"quotes\" and a \\ backslash";
    feature c = "tab\there\nnew line, \'single\' and \bback\fform\rreturn";
    feature d = "ends with a backslash \\";
    feature e = "";
    feature f = 9223372036854775807;
}
