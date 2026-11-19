// expect: valid
package P {
    attribute a = "plain";
    attribute b = "with \"quotes\" and a \\ backslash";
    attribute c = "tab\there\nnew line, \'single\' and \bback\fform\rreturn";
    attribute d = "ends with a backslash \\";
    attribute e = "";
    attribute f = 9223372036854775807;
}
