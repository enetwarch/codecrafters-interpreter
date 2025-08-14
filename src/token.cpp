#include "token.hpp"

#include <string>

std::string stringify_token_type(TokenType token_type) {
    switch (token_type) {
        // Single-character tokens.
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";

        // One or two character tokens.
        case TokenType::BANG: return "BANG";
        case TokenType::BANG_EQUAL: return "BANG_EQUAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";

        // Literals.
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";

        // Keywords.
        case TokenType::AND: return "AND";
        case TokenType::CLASS: return "CLASS";
        case TokenType::ELSE: return "ELSE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::FUN: return "FUN";
        case TokenType::FOR: return "FOR";
        case TokenType::IF: return "IF";
        case TokenType::NIL: return "NIL";
        case TokenType::OR: return "OR";
        case TokenType::PRINT: return "PRINT";
        case TokenType::RETURN: return "RETURN";
        case TokenType::SUPER: return "SUPER";
        case TokenType::THIS: return "THIS";
        case TokenType::TRUE: return "TRUE";
        case TokenType::VAR: return "VAR";
        case TokenType::WHILE: return "WHILE";

        case TokenType::END_OF_FILE: return "EOF";
        default: return "UNKNOWN";
    }
}

std::string lexemize_token_type(TokenType token_type) {
    switch (token_type) {
        // Single-character tokens.
        case TokenType::LEFT_PAREN: return "(";
        case TokenType::RIGHT_PAREN: return ")";
        case TokenType::LEFT_BRACE: return "{";
        case TokenType::RIGHT_BRACE: return "}";
        case TokenType::COMMA: return ",";
        case TokenType::DOT: return ".";
        case TokenType::MINUS: return "-";
        case TokenType::PLUS: return "+";
        case TokenType::SEMICOLON: return ";";
        case TokenType::SLASH: return "/";
        case TokenType::STAR: return "*";

        // One or two character tokens.
        case TokenType::BANG: return "!";
        case TokenType::BANG_EQUAL: return "!=";
        case TokenType::EQUAL: return "=";
        case TokenType::EQUAL_EQUAL: return "==";
        case TokenType::GREATER: return ">";
        case TokenType::GREATER_EQUAL: return ">=";
        case TokenType::LESS: return "<";
        case TokenType::LESS_EQUAL: return "<=";

        // Literals.
        case TokenType::IDENTIFIER: return "<identifier>";
        case TokenType::STRING: return "<string>";
        case TokenType::NUMBER: return "<number>";

        // Keywords.
        case TokenType::AND: return "and";
        case TokenType::CLASS: return "class";
        case TokenType::ELSE: return "else";
        case TokenType::FALSE: return "false";
        case TokenType::FUN: return "fun";
        case TokenType::FOR: return "for";
        case TokenType::IF: return "if";
        case TokenType::NIL: return "nil";
        case TokenType::OR: return "or";
        case TokenType::PRINT: return "print";
        case TokenType::RETURN: return "return";
        case TokenType::SUPER: return "super";
        case TokenType::THIS: return "this";
        case TokenType::TRUE: return "true";
        case TokenType::VAR: return "var";
        case TokenType::WHILE: return "while";

        case TokenType::END_OF_FILE: return "";
        default: return "<unknown>";
    }
}
