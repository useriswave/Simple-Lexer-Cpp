#include "../../includes/token.h"

#include <iostream>
#include <string_view> //here

std::string_view Dumblang::toString(TokenType type)
{
    switch (type)
    {
        case TokenType::If: return "if";
        case TokenType::Else: return "else";
        case TokenType::For: return "for";
        case TokenType::While: return "while";

        case TokenType::Plus: return "+";
        case TokenType::Minus: return "-";
        case TokenType::Star: return "*";
        case TokenType::Slash: return "/";
        case TokenType::Equals: return "=";
        case TokenType::GreaterThan: return ">";
        case TokenType::GreaterThanOrEqual: return ">=";
        case TokenType::LessThan: return "<";
        case TokenType::LessThanOrEqual: return "<=";

        case TokenType::LeftParentheses: return "(";
        case TokenType::RightParentheses: return ")";
        case TokenType::LeftBracket: return "[";
        case TokenType::RightBracket: return "]";
        case TokenType::LeftBrace: return "{";
        case TokenType::RightBrace: return "}";
        case TokenType::Comma: return ",";
        case TokenType::Dot: return ".";
        case TokenType::Semicolon: return ";";
        case TokenType::Colon: return ":";

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

std::ostream& Dumblang::operator<<(std::ostream& out, const Token& t)
{
    return out << "Lexeme: " << t.lexeme_ << "\t " << "TokenType: " << Dumblang::toString(t.type_) << '\n';
}
