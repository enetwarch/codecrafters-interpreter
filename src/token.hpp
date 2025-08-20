#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <optional>
#include <string>
#include <variant>

enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    END_OF_FILE,
    UNKNOWN
};

using Literal = std::optional<std::variant<std::string, double>>;

struct Token {
    TokenType type{TokenType::UNKNOWN};
    std::string lexeme{""};
    Literal literal{};
    int line{0};
};

std::string stringify_token_type(TokenType token_type);
std::string stringify_token_literal(const Literal& literal);

#endif
