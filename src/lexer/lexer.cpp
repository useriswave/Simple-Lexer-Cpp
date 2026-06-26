#include "../../includes/lexer.h"
#include "../../includes/token.h"

#include <cctype>
#include <string_view>

const std::vector<Dumblang::Token>& Lexer::tokenize()
{
    while (!isEOF()) {
        if (std::isspace(peek())) {
            skipWhiteSpace();
        } else if (std::isalpha(peek()) || peek() == '_') {
            handleAlpha();
        } else if (std::isdigit(peek())) {
            handleNumber();
        } else {
            try {
                handleSingleChar();
            } catch (const std::runtime_error&) {
                throw;
            }
        }

        start_ = current_;
    }

    return tokens_;
}

void Lexer::handleSingleChar()
{
    switch (advance())
    {
    case '+': addToken(TokenType::Plus); break;
    case '-': addToken(TokenType::Minus); break;
    case '*': addToken(TokenType::Star); break;
    case '/': addToken(TokenType::Slash); break;
    case '(': addToken(TokenType::LeftParentheses); break;
    case ')': addToken(TokenType::RightParentheses); break;
    case '[': addToken(TokenType::LeftBracket); break;
    case ']': addToken(TokenType::RightBracket); break;
    case '{': addToken(TokenType::LeftBrace); break;
    case '}': addToken(TokenType::RightBrace); break;
    case ',': addToken(TokenType::Comma); break;
    case '.': addToken(TokenType::Dot); break;
    case ';': addToken(TokenType::Semicolon); break;
    case ':': addToken(TokenType::Colon); break;
    case '"': handleString(); break;

    // double chars
    case '=': addToken(advanceIf('=') ? TokenType::EqualsEquals : TokenType::Equals); break;
    case '>': addToken(advanceIf('=') ? TokenType::GreaterThanOrEqual : TokenType::GreaterThan); break;
    case '<': addToken(advanceIf('=') ? TokenType::LessThanOrEqual : TokenType::LessThan); break;
    case '&': addToken(advanceIf('&') ? TokenType::AndAnd : TokenType::And); break;
    case '|': addToken(advanceIf('|') ? TokenType::OrOr : TokenType::Or); break;

    default:  addToken(TokenType::Unknown);
    }
}

TokenType Lexer::checkKeyword(std::string_view lexeme)
{
    if      (lexeme == "if") return TokenType::If;
    else if (lexeme == "else") return TokenType::Else;
    else if (lexeme == "while") return TokenType::While;
    else if (lexeme == "for") return TokenType::For;
    else if (lexeme == "int") return TokenType::Integer;
    else if (lexeme == "double") return TokenType::Double;
    else if (lexeme == "float") return TokenType::Float;
    else if (lexeme == "string") return TokenType::String;
    else if (lexeme == "boolean")return TokenType::Boolean;
    else if (lexeme == "void") return TokenType::Void;
    else if (lexeme == "null") return TokenType::Null;
    else return TokenType::Ident;
}

void Lexer::handleAlpha()
{
    while (std::isalnum(peek()) || peek() == '_') {
        advance();
    }

    addToken(checkKeyword(substr()));
}

void Lexer::handleNumber()
{
    bool hasDecimal{};

    while (std::isdigit(peek()) || peek() == '.') {
        if (peek() == '.') {
            if (hasDecimal)
                break;

            hasDecimal = true;
        }

        advance();
    }

    addToken(hasDecimal ? TokenType::DoubleLiteral : TokenType::IntegerLiteral);
}

void Lexer::handleString()
{
    advance();
    ++start_;

    while (peek() != '"') {
        if (isEOF()) {
            throw std::runtime_error{"ERROR: Reached EOF while tokenizing string.\n" };
        }

        advance();
    }

    addToken(TokenType::StringLiteral);
}

void Lexer::skipWhiteSpace()
{
    while (!isEOF()) {
        if (peek() == ' ' || peek() == '\t') {
            advance();
        } else if (peek() == '\n') {
            advance();
            ++line_;
        } else {
            break;
        }
    }
}

bool Lexer::isEOF() const
{
    return current_ >= code_.length();
}

char Lexer::peek() const
{
    if (isEOF()) {
        return '\0';
    }

    return code_[current_];
}

char Lexer::peekNext() const
{
    if (isEOF()) {
        return '\0';
    }

    return code_[current_+1];
}

char Lexer::advance()
{
    char c { peek() };
    ++current_;

    return c;
}

bool Lexer::advanceIf(char c)
{
    if (peek() == c) {
        advance();
        return true;
    }

    return false;
}

void Lexer::addToken(TokenType type)
{
    tokens_.emplace_back(substr(), type);
}

std::string_view Lexer::substr() const
{
    if (isEOF()) {
        return "";
    }

    return code_.substr(start_, current_ - start_);
}
