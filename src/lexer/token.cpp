#include "../../includes/token.h"

#include <iostream>

namespace
{
    std::string_view toStr(TokenType type) noexcept
    {
        switch (type)
        {
            case TokenType::If: return "if";
            case TokenType::Else: return "else";
            case TokenType::For: return "for";
            case TokenType::While: return "while";
            case TokenType::Plus: return "Plus";
            case TokenType::Minus: return "Minus";
            case TokenType::Star: return "Star";
            case TokenType::Slash: return "Slash";
            case TokenType::Equals: return "Equals";
            case TokenType::EqualsEquals: return "EqualsComparison";
            case TokenType::GreaterThan: return "GreaterThan";
            case TokenType::GreaterThanOrEqual: return "GreaterThanOrEquals";
            case TokenType::LessThan: return "LessThan";
            case TokenType::LessThanOrEqual: return "GreaterThan";
            case TokenType::And: return "And";
            case TokenType::AndAnd: return "AndComparison";
            case TokenType::Or: return "Or";
            case TokenType::OrOr: return "OrComparison";
            case TokenType::Not: return "Not";

            case TokenType::LeftParentheses: return "LeftParentheses";
            case TokenType::RightParentheses: return "RightParentheses";
            case TokenType::LeftBracket: return "LeftBracket";
            case TokenType::RightBracket: return "RightBracket";
            case TokenType::LeftBrace: return "LeftBrace";
            case TokenType::RightBrace: return "RightBrace";
            case TokenType::Comma: return "Comma";
            case TokenType::Dot: return "Dot";
            case TokenType::Semicolon: return "Semicolon";
            case TokenType::Colon: return "Colon";

            case TokenType::IntegerLiteral: return "Integer Literal";
            case TokenType::DoubleLiteral: return "Double Literal";
            case TokenType::FloatLiteral: return "Float Literal";
            case TokenType::StringLiteral: return "String Literal";

            case TokenType::Integer: return "int";
            case TokenType::Double: return "double";
            case TokenType::Float: return "float";
            case TokenType::String: return "string";
            case TokenType::Character: return "char";
            case TokenType::Boolean: return "boolean";
            case TokenType::Void: return "void";
            case TokenType::Null: return "null";
            case TokenType::Ident: return "Ident";
            default: return "Unknown";
        }
    }
}

std::ostream& Dumblang::operator<<(std::ostream& out, const Token& t)
{
    return out << "Lexeme: " << t.m_lexeme << "\t " << "TokenType: " << toStr(t.m_type);
}
