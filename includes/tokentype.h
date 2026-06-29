#pragma once

enum class TokenType
{
    // KEYWORDS

    If,
    Else,
    For,
    While,
    Func,

    // OPPERATORS

    Plus,
    Minus,
    Star,
    Slash,
    Equals,
    EqualsEquals,
    GreaterThan,
    GreaterThanOrEqual,
    LessThan,
    LessThanOrEqual,
    Ampersand,
    And,
    Pipe,
    Or,
    Not,
    NotEqual,


    // MISC

    LeftParentheses,
    RightParentheses,
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,
    Comma,
    Dot,
    Semicolon,
    Colon,
    DoubleQuote,
    SingleQuote,

    // LITERAL TYPES

    IntegerLiteral,
    FloatLiteral,
    DoubleLiteral,
    StringLiteral,

    // DATA TYPES

    Integer,
    Double,
    Float,
    String,
    Character,
    Boolean,
    Void,
    Null,

    // OTHER

    Ident,
    Unknown
};
