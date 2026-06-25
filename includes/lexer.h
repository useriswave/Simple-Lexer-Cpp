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
    TokenType checkKeyword(std::string_view buffer);
    bool isValidIdentifier(const std::string& buffer);
    void handleSingleChar();
    void handleAlpha();
    void handleNumber();
    void handleString();
    bool isEOF() const;

private:
    std::vector<Dumblang::Token> tokens_{};
    std::string code_{};
    std::size_t current_{};
};
