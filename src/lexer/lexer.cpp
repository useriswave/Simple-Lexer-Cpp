#include "../../includes/lexer.h"
#include "../../includes/token.h"

#include <algorithm>
#include <cctype>

const std::vector<Dumblang::Token>& Lexer::tokenize()
{
    for (; current_ < code_.length(); start_ = current_)  {
        if (std::isspace(code_[current_])) {
            skipWhiteSpace();
        } else if (std::isalpha(code_[current_]) || code_[current_] == '_') {
            handleAlpha();
        } else if (std::isdigit(code_[current_])) {
            handleNumber();
        } else {
            try {
                handleSingleChar();
            } catch (const std::runtime_error&) {
                throw;
            }
        }
    }

    return tokens_;
}

void Lexer::handleSingleChar()
{
    switch (code_[current_])
    {
    case '+': tokens_.emplace_back("+", TokenType::Plus); break;
    case '-': tokens_.emplace_back("-", TokenType::Minus); break;
    case '*': tokens_.emplace_back("*", TokenType::Star); break;
    case '/': tokens_.emplace_back("/", TokenType::Slash); break;
    case '=': tokens_.emplace_back("=", TokenType::Equals); break;
    case '(': tokens_.emplace_back("(", TokenType::LeftParentheses); break;
    case ')': tokens_.emplace_back(")", TokenType::RightParentheses); break;
    case '[': tokens_.emplace_back("[", TokenType::LeftBracket); break;
    case ']': tokens_.emplace_back("]", TokenType::RightBracket); break;
    case '{': tokens_.emplace_back("{", TokenType::LeftBrace); break;
    case '}': tokens_.emplace_back("}", TokenType::RightBrace); break;
    case ',': tokens_.emplace_back(",", TokenType::Comma); break;
    case '.': tokens_.emplace_back(".", TokenType::Dot); break;
    case ';': tokens_.emplace_back(";", TokenType::Semicolon); break;
    case ':': tokens_.emplace_back(":", TokenType::Colon); break;
    case '"': handleString(); break;

    // greater, less than or equal
    case '>':
            if (!isEOF() && peekNext() == '=') {
                tokens_.emplace_back(">=", TokenType::GreaterThanOrEqual);
                ++current_;     // skip equal
            } else
                tokens_.emplace_back(">", TokenType::GreaterThan);

    break;
    case '<':
            if (!isEOF() && peekNext() == '=') {
                tokens_.emplace_back("<=", TokenType::LessThanOrEqual);
                ++current_;
            } else
                tokens_.emplace_back("<", TokenType::LessThan);
    break;
    default:
            tokens_.emplace_back(code_[current_], TokenType::Unknown);
    }

    current_++;
}

TokenType Lexer::checkKeyword(std::string_view lexeme)
{
    TokenType type{};

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
    else return TokenType::Unknown;
}

bool Lexer::isEOF() const
{
    return current_ >= code_.length();
}

void Lexer::handleAlpha()
{
    while (std::isalnum(peek()) || peek() == '_') {
        advance();
    }

    auto lexeme { code_.substr(start_, current_ - start_) };    // could potentially make a helper for this
    TokenType type { checkKeyword(lexeme) };

    if (type != TokenType::Unknown) {
        addToken(lexeme, type);
    } else {
        addToken(lexeme, TokenType::Ident);
    }
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

    auto lexeme { code_.substr(start_, current_ - start_) };

    if (hasDecimal) {
        addToken(lexeme, TokenType::DoubleLiteral);
    } else {
        addToken(lexeme, TokenType::IntegerLiteral);
    }
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

    auto lexeme { code_.substr(start_, current_ - start_) };
    addToken(lexeme, TokenType::StringLiteral);
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

/*
*   i could've done: return code_[++current_];
*   but this will do incase i have more things to track
*/

char Lexer::advance()
{
    char c { peek() };
    ++current_;

    return c;
}

void Lexer::addToken(std::string_view lexeme, TokenType type)
{
    tokens_.emplace_back(lexeme, type);
}

