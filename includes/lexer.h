#pragma once

#include "token.h"

#include <iostream>
#include <string>
#include <vector>

class Lexer final
{
public:
    Lexer(std::string_view sourceCode)
        : m_sourceCode { sourceCode }
    {}

public:
    const std::vector<Dumblang::Token>& tokenize();

private:
    static TokenType checkKeyword(std::string_view lexeme) noexcept;
    void handleSingleChar();
    void handleAlpha();
    void handleNumber();
    void handleString();
    void handleComment();
    void skipWhiteSpace() noexcept;
    bool isEOF() const noexcept;
    char current() const noexcept;
    char peek() const noexcept;
    char advance() noexcept;
    bool advanceIf(char c) noexcept;
    void addToken(TokenType type);
    std::string_view substr() const;

private:
    std::vector<Dumblang::Token> m_tokens{};
    std::string_view m_sourceCode{};
    std::size_t m_curr{};
    std::size_t m_start{};
    std::size_t m_line{ 1 };
};
