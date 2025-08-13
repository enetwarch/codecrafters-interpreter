#include "scanner.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "token.hpp"

Scanner& tokenize_next_possible_lexeme(Scanner& scanner);
std::optional<Token> tokenize_single_character_token(char character, int line);

void throw_error(int line, const std::string& message);

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
        scanner = tokenize_next_possible_lexeme(scanner);
    }
    scanner.tokens.push_back(
        {" ", "null", TokenType::END_OF_FILE, scanner.line});

    return scanner.tokens;
}

Scanner& tokenize_next_possible_lexeme(Scanner& scanner) {
    char character = scanner.contents[scanner.index];

    std::optional<Token> single_character_token =
        tokenize_single_character_token(character, scanner.line);
    if (single_character_token.has_value()) {
        scanner.index += 1;
        scanner.tokens.push_back(single_character_token.value());
        return scanner;
    }

    throw_error(scanner.line, std::format("Unexpected character: {}", character));
    scanner.error = true;
    scanner.index += 1;
    return scanner;
}

std::optional<Token> tokenize_single_character_token(char character, int line) {
    switch (character) {
        case '(': return Token{"(", "null", TokenType::LEFT_PAREN, line};
        case ')': return Token{")", "null", TokenType::RIGHT_PAREN, line};
        case '{': return Token{"{", "null", TokenType::LEFT_BRACE, line};
        case '}': return Token{"}", "null", TokenType::RIGHT_BRACE, line};
        case ',': return Token{",", "null", TokenType::COMMA, line};
        case '.': return Token{".", "null", TokenType::DOT, line};
        case '-': return Token{"-", "null", TokenType::MINUS, line};
        case '+': return Token{"+", "null", TokenType::PLUS, line};
        case ';': return Token{";", "null", TokenType::SEMICOLON, line};
        case '/': return Token{"/", "null", TokenType::SLASH, line};
        case '*': return Token{"*", "null", TokenType::STAR, line};

        default: return std::nullopt;
    }
}

void throw_error(int line, const std::string& message) {
    std::cout << "[line " << line << "] Error: " << message << std::endl;
}
