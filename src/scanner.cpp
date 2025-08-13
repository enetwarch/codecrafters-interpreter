#include "scanner.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
        scanner.tokens.push_back(
            tokenize_single_character_token(character, scanner.line));
    }
    scanner.tokens.push_back(
        {" ", "null", TokenType::END_OF_FILE, scanner.line});

    return scanner.tokens;
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
