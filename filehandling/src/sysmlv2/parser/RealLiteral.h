//
// Locale-independent parsing of real numbers (private header of the sysmlv2parser library).
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <locale>
#include <sstream>
#include <string>
//---------------------------------------------------------

namespace SysMLv2::Files {

    /**
     * Parses @p text as a real number in the "C" locale, whatever the locale of the process is.
     *
     * Why this exists: std::stod and std::strtod use the global C locale, and Qt applications (QCoreApplication calls
     * setlocale(LC_ALL, "") on Unix) run in the user's locale; with a comma as decimal separator "5.02921" is read as 5.
     *
     * The whole text must be one number made of the characters 0-9 + - . e E (whitespace, hex, inf and nan are rejected on every
     * standard library). Returns false for anything else and for values that overflow a double (1e999); @p value is changed only
     * on success. Underflow is stdlib-dependent: libstdc++ reads 1e-999 as 0 and 1e-320 as that subnormal, other libraries may reject them.
     */
    inline bool parseDouble(const std::string& text, double& value) {
        // libc++ hands the text to strtod_l, which would also accept 0x10, inf and nan; only plain decimal text goes to the stream.
        if (text.empty() || text.find_first_not_of("0123456789+-.eE") != std::string::npos) return false;
        std::istringstream stream(text);
        stream.imbue(std::locale::classic());
        stream.unsetf(std::ios_base::skipws);
        double parsed = 0.0;
        stream >> parsed;
        if (stream.fail() || !stream.eof()) return false;
        value = parsed;
        return true;
    }
}
