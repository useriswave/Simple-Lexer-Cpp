#pragma once

#include "tokentype.h"

#include <string>
#include <optional>

namespace Dumblang
{
    struct Token
    {
        Token(std::string_view lexeme, TokenType type)
            : lexeme_ { lexeme }
            , type_ { type }
        {}

        std::string_view lexeme_{};
        TokenType type_{};
    };

    std::string_view toStr(TokenType type);
    std::ostream& operator<<(std::ostream& out, const Token& t);
}
