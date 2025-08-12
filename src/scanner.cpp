#include <string>
#include <vector>
#include <iostream>
#include <format>
#include <fstream>
#include <sstream>

#include "scanner.hpp"
#include "token.hpp"

std::string stringify_file_contents(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << file_name << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

std::vector<Token> tokenize_file_contents(const std::string& file_contents) {
    Scanner scanner{.contents = file_contents, .line = 1};

    while (scanner.index < scanner.contents.size()) {
        char character = scanner.contents[scanner.index++];
        scanner.tokens.push_back(tokenize_single_character_token(character, scanner.line));
    }
    scanner.tokens.push_back({" ", "null", TokenType::END_OF_FILE, scanner.line});

    return scanner.tokens;
}

// TODO: Replace this with the magic_enum library.
std::string stringify_token_type(TokenType token_type) {
    switch (token_type) {
        // Single-character tokens
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

        // One or two character tokens
        case TokenType::BANG: return "BANG";
        case TokenType::BANG_EQUAL: return "BANG_EQUAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";

        // Literals
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";

        // Keywords
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

        // Other
        case TokenType::END_OF_FILE: return "EOF";
        case TokenType::UNKNOWN: return "UNKNOWN";

        default: return "UNKNOWN";
    }
}

Token tokenize_single_character_token(char character, int line) {
    switch (character) {
        case '(': return {"(", "null", TokenType::LEFT_PAREN, line};
        case ')': return {")", "null", TokenType::RIGHT_PAREN, line};
        case '{': return {"{", "null", TokenType::LEFT_BRACE, line};
        case '}': return {"}", "null", TokenType::RIGHT_BRACE, line};
        case ',': return {",", "null", TokenType::COMMA, line}; 
        case '.': return {".", "null", TokenType::DOT, line};
        case '-': return {"-", "null", TokenType::MINUS, line};
        case '+': return {"+", "null", TokenType::PLUS, line};
        case ';': return {";", "null", TokenType::SEMICOLON, line};
        case '/': return {"/", "null", TokenType::SLASH, line};
        case '*': return {"*", "null", TokenType::STAR, line};

        default: return {{}, {}, TokenType::UNKNOWN, line};
    }
}