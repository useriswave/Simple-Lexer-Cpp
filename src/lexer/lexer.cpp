#include "../../includes/lexer.h"
#include "../../includes/token.h"

#include <algorithm>
#include <cctype>

const std::vector<Dumblang::Token>& Lexer::tokenize()
{
    while (current_ < code_.length())  {
        if (std::isspace(code_[current_])) {
            ++current_;
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

    // greater - less than OR equal
    case '>':
            if (!isEOF() && code_[current_+1] == '=') {
                tokens_.emplace_back(">=", TokenType::GreaterThanOrEqual);
                ++current_;     // skip checked equal
            } else
                tokens_.emplace_back(">", TokenType::GreaterThan);

    break;
    case '<':
            if (!isEOF() && code_[current_+1] == '=') {
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

TokenType Lexer::checkKeyword(std::string_view buffer)
{
    TokenType type{};

    if      (buffer == "if") return TokenType::If;
    else if (buffer == "else") return TokenType::Else;
    else if (buffer == "while") return TokenType::While;
    else if (buffer == "for") return TokenType::For;
    else if (buffer == "int") return TokenType::Integer;
    else if (buffer == "double") return TokenType::Double;
    else if (buffer == "float") return TokenType::Float;
    else if (buffer == "string") return TokenType::String;
    else if (buffer == "boolean")return TokenType::Boolean;
    else if (buffer == "void") return TokenType::Void;
    else if (buffer == "null") return TokenType::Null;
    else return TokenType::Unknown;
}

bool Lexer::isEOF() const
{
    return current_ >= code_.length();
}

void Lexer::handleAlpha()
{
    std::string buffer{};

    for (; std::isalpha(code_[current_]) || code_[current_] == '_'; ++current_) {
        buffer += code_[current_];
    }

    TokenType keyword { checkKeyword(buffer) };

    if (keyword != TokenType::Unknown) {
        tokens_.emplace_back(buffer, keyword);
    } else {
        tokens_.emplace_back(buffer, TokenType::Ident);
    }
}

void Lexer::handleNumber()
{
    std::string buffer{};
    bool hasDecimal{};

    for (; std::isdigit(code_[current_]) || code_[current_] == '.'; ++current_) {
        if (code_[current_] == '.') {
            if (hasDecimal) break;
            hasDecimal = true;
        }

        buffer += code_[current_];
    }

    if (hasDecimal) {
        tokens_.emplace_back(buffer, TokenType::DoubleLiteral);
    } else {
        tokens_.emplace_back(buffer, TokenType::IntegerLiteral);
    }
}

bool Lexer::isValidIdentifier(const std::string& buffer)
{
    return std::all_of(buffer.begin(), buffer.end(), [](unsigned char c){
        return std::isalnum(c) || c == '_';
    });
}

void Lexer::handleString()
{
    ++current_;
    std::string buffer{};

    for (; code_[current_] != '"'; ++current_) {
        if (isEOF()) {
            throw std::runtime_error{"ERROR: Reached EOF while tokenizing string.\n" };
        }

        buffer += code_[current_];
    }

    tokens_.emplace_back(buffer, TokenType::StringLiteral);
}
