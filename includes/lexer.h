#pragma once

#include "token.h"

#include <iostream>
#include <string>
#include <vector>

class Lexer
{
public:
    Lexer(std::string_view sourceCode)
        : m_sourceCode { sourceCode }
    {}

public:
    const std::vector<Dumblang::Token>& tokenize();
    const std::vector<Dumblang::Token>& getTokens() const { return tokens_; }

private:
    TokenType checkKeyword(std::string_view lexeme);
    void handleSingleChar();
    void handleAlpha();
    void handleNumber();
    void handleString();
    void skipWhiteSpace();
    bool isEOF() const;
    char current() const;
    char peekNext() const;
    char advance();
    bool advanceIf(char c);
    void addToken(TokenType type);
    std::string_view substr() const;

private:
    std::vector<Dumblang::Token> tokens_{};
    std::string_view m_sourceCode{};
    std::size_t m_curr{};
    std::size_t m_start{};
    std::size_t m_line{ 1 };
};
