#pragma once

#include "tokentype.h"

#include <string>

namespace Dumblang
{
    struct Token
    {
        Token(std::string_view lexeme, TokenType type)
            : m_lexeme { lexeme }
            , m_type { type }
        {}

        std::string_view m_lexeme{};
        TokenType m_type{};
    };

    std::ostream& operator<<(std::ostream& out, const Token& t);
}
