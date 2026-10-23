//
// Text helpers shared by the reader and the writer of the XMI files.
// (Private header of the sysmlv2parser library.)
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <cstddef>
#include <cstdint>
#include <string>
//---------------------------------------------------------

namespace SysMLv2::Files::Xmi {

    /// The number of bytes of the well-formed UTF-8 sequence at the start of @p text (0 if there is none: a stray continuation byte, a
    /// truncated, overlong or surrogate sequence, a code point above U+10FFFF); @p code is the character.
    inline std::size_t utf8Sequence(const char* text, std::size_t available, std::uint32_t& code) {
        const auto byte = [&](std::size_t i) { return static_cast<unsigned char>(text[i]); };
        const unsigned char lead = byte(0);
        std::size_t length = 0;
        if (lead < 0x80) {
            code = lead;
            return 1;
        } else if (lead >= 0xC2 && lead <= 0xDF) {
            length = 2;
            code = lead & 0x1F;
        } else if (lead >= 0xE0 && lead <= 0xEF) {
            length = 3;
            code = lead & 0x0F;
        } else if (lead >= 0xF0 && lead <= 0xF4) {
            length = 4;
            code = lead & 0x07;
        } else {
            return 0;
        }
        if (available < length) return 0;
        for (std::size_t i = 1; i < length; ++i) {
            if ((byte(i) & 0xC0) != 0x80) return 0;
            code = (code << 6) | (byte(i) & 0x3F);
        }
        if ((length == 3 && code < 0x800) || (length == 4 && code < 0x10000) || code > 0x10FFFF || (code >= 0xD800 && code <= 0xDFFF)) return 0;
        return length;
    }

    /// True if @p text is well-formed UTF-8 (the empty text is).
    inline bool isValidUtf8(const std::string& text) {
        for (std::size_t i = 0; i < text.size();) {
            std::uint32_t code = 0;
            const std::size_t length = utf8Sequence(text.data() + i, text.size() - i, code);
            if (length == 0) return false;
            i += length;
        }
        return true;
    }
}
