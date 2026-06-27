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
    advance();
    ++m_start;

    while (current() != '"') {
        if (isEOF()) {
            throw std::runtime_error{"ERROR: Reached EOF while tokenizing string.\n" };
        }

        advance();
    }

    addToken(TokenType::StringLiteral);
    advance();      // IMPORTANT!!! SKIPS THE CLOSING (") WHEN LOOP BREAKS
}

void Lexer::skipWhiteSpace()
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

bool Lexer::isEOF() const
{
    return m_curr >= m_sourceCode.length();
}

char Lexer::current() const
{
    if (isEOF()) {
        return '\0';
    }

    return m_sourceCode[m_curr];
}

char Lexer::peek() const
{
    if (isEOF()) {
        return '\0';
    }

    return m_sourceCode[m_curr+1];
}

char Lexer::advance()
{
    char c { current() };
    ++m_curr;

    return c;
}

bool Lexer::advanceIf(char c)
{
    if (current() == c) {
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

    return m_sourceCode.substr(m_start, m_curr - m_start);
}
