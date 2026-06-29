#include "../../includes/lexer.h"
#include "../../includes/token.h"

const std::vector<Dumblang::Token>& Lexer::tokenize()
{
    while (!isEOF()) {
        if (std::isspace(current())) {
            skipWhiteSpace();
        } else if (std::isalpha(current()) || current() == '_') {
            handleAlpha();
        } else if (std::isdigit(current())) {
            handleNumber();
        } else {
            try {
                handleSingleChar();
            } catch (const std::runtime_error&) {
                throw;
            }
        }

        m_start = m_curr;
    }

    return m_tokens;
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
    case '#': handleComment(); break;
    case '"': handleString(); break;

    // double chars
    case '=': addToken(advanceIf('=') ? TokenType::EqualsEquals : TokenType::Equals); break;
    case '>': addToken(advanceIf('=') ? TokenType::GreaterThanOrEqual : TokenType::GreaterThan); break;
    case '<': addToken(advanceIf('=') ? TokenType::LessThanOrEqual : TokenType::LessThan); break;
    case '&': addToken(advanceIf('&') ? TokenType::And : TokenType::Ampersand); break;
    case '|': addToken(advanceIf('|') ? TokenType::Or : TokenType::Pipe); break;
    case '!': addToken(advanceIf('=') ? TokenType::NotEqual : TokenType::Not); break;

    default:  addToken(TokenType::Unknown);
    }
}

TokenType Lexer::checkKeyword(std::string_view lexeme) noexcept
{
    if      (lexeme == "if") return TokenType::If;
    else if (lexeme == "else") return TokenType::Else;
    else if (lexeme == "for") return TokenType::For;
    else if (lexeme == "while") return TokenType::While;
    else if (lexeme == "func") return TokenType::Func;
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
    while (std::isalnum(current()) || current() == '_') {
        advance();
    }

    addToken(checkKeyword(substr()));
}

void Lexer::handleNumber()
{
    bool hasDecimal{};

    while (std::isdigit(current()) || current() == '.') {
        if (current() == '.') {
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
    for (++m_start; current() != '"'; advance()) {
        if (isEOF()) {
            throw std::runtime_error{ "ERROR: Unterminated string." };
        }
    }

    addToken(TokenType::StringLiteral);
    advance();
}

void Lexer::handleComment()
{
    while (current() != '\n') {
        advance();
    }

    addToken(TokenType::Comment);
}

void Lexer::skipWhiteSpace() noexcept
{
    for (; !isEOF(); advance()) {
        if (current() == ' ' || current() == '\t') {
        } else if (current() == '\n') {
            ++m_line;
        } else {
            break;
        }
    }
}

bool Lexer::isEOF() const noexcept
{
    return m_curr >= m_sourceCode.length();
}

char Lexer::current() const noexcept
{
    if (isEOF()) {
        return '\0';
    }

    return m_sourceCode[m_curr];
}

char Lexer::advance() noexcept
{
    char c { current() };
    ++m_curr;

    return c;
}

bool Lexer::advanceIf(char c) noexcept
{
    if (current() == c) {
        advance();
        return true;
    }

    return false;
}

void Lexer::addToken(TokenType type)
{
    m_tokens.emplace_back(substr(), type);
}

std::string_view Lexer::substr() const
{
    auto s { m_sourceCode.substr(m_start, m_curr - m_start) };

    if (isEOF() || s == "\"") {
        return "";
    }

    return m_sourceCode.substr(m_start, m_curr - m_start);
}
