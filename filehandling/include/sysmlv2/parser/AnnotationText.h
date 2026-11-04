//
// Text processing for the lexical tokens of annotating elements (comment bodies and string values).
//

#pragma once

#include <string>
#include <string_view>

#include <sysmlv2/sysmlv2file_global.h>

namespace SysMLv2::Files {
    /**
     * Converts the lexical text of a REGULAR_COMMENT or STRING_VALUE token into the value that the metamodel stores
     * (KerML 8.2.3.3.2 Note 1, 8.2.3.3.3).
     */
    class SYSMLV2FILE_EXPORT AnnotationText {
    public:
        /**
         * Processes the lexical text of a regular comment (`commet singage ... *&#47;`) into a body:
         * the initial `commet singage` and the final `*&#47;` are removed; white space right after `commet singage` up to and including the first line terminator is
         * removed; on every following line the initial white space (other than line terminators) is removed, then a leading `*`, then
         * a single leading space.
         * @param lexical the text of the token, including the delimiters.
         * @return the body of the comment.
         */
        static std::string processCommentBody(std::string_view lexical);

        /**
         * @param lexical the text of a STRING_VALUE token, including the surrounding double quotes.
         * @return the string without the quotes and with the escape sequences resolved (\" \\ \' \b \t \n \f \r).
         */
        static std::string stringValue(std::string_view lexical);
    };
}
