#pragma once

#include "tokentype.h"

#include <string>

namespace Dumblang
{
    struct Token
    {
        Token(std::string_view lexeme, TokenType type, std::size_t line)
            : m_lexeme { lexeme }
            , m_type { type }
            , m_line { line }
        {}

        std::string_view m_lexeme{};
        TokenType m_type{};
        std::size_t m_line{};
    };

    std::ostream& operator<<(std::ostream& out, const Token& t);
}
