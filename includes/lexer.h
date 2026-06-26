#pragma once

#include "token.h"

#include <iostream>
#include <string>
#include <vector>

class Lexer
{
public:
    Lexer(std::string_view code)
        : code_ { code }
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
    char peek() const;
    char peekNext() const;
    char advance();
    void addToken(std::string_view lexeme, TokenType type);

private:
    std::vector<Dumblang::Token> tokens_{};
    std::string_view code_{};
    std::size_t current_{};
    std::size_t start_{};
    std::size_t line_{ 1 };
};
