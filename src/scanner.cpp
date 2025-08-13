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
std::optional<Token> tokenize_single_character(const Scanner& scanner);
std::optional<Token> tokenize_equality_operator(const Scanner& scanner);

char get_scanner_character(const Scanner& scanner, size_t offset = 0);
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
    scanner.tokens.push_back({"", {}, TokenType::END_OF_FILE, scanner.line});

    return scanner.tokens;
}

Scanner& tokenize_next_possible_lexeme(Scanner& scanner) {
    std::optional<Token> single_character_token =
        tokenize_single_character(scanner);
    if (single_character_token.has_value()) {
        scanner.index += 1;
        scanner.tokens.push_back(single_character_token.value());
        return scanner;
    }

    std::optional<Token> equality_operator_token =
        tokenize_equality_operator(scanner);
    if (equality_operator_token.has_value()) {
        scanner.index += equality_operator_token.value().lexeme.size();
        scanner.tokens.push_back(equality_operator_token.value());
        return scanner;
    }

    throw_error(scanner.line, std::format("Unexpected character: {}",
                                          get_scanner_character(scanner)));
    scanner.error = true;
    scanner.index += 1;
    return scanner;
}

std::optional<Token> tokenize_single_character(const Scanner& scanner) {
    switch (get_scanner_character(scanner)) {
        case '(': return Token{"(", {}, TokenType::LEFT_PAREN, scanner.line};
        case ')': return Token{")", {}, TokenType::RIGHT_PAREN, scanner.line};
        case '{': return Token{"{", {}, TokenType::LEFT_BRACE, scanner.line};
        case '}': return Token{"}", {}, TokenType::RIGHT_BRACE, scanner.line};

        case ',': return Token{",", {}, TokenType::COMMA, scanner.line};
        case '.': return Token{".", {}, TokenType::DOT, scanner.line};
        case ';': return Token{";", {}, TokenType::SEMICOLON, scanner.line};

        case '+': return Token{"+", {}, TokenType::PLUS, scanner.line};
        case '-': return Token{"-", {}, TokenType::MINUS, scanner.line};
        case '*': return Token{"*", {}, TokenType::STAR, scanner.line};
        case '/': return Token{"/", {}, TokenType::SLASH, scanner.line};

        default: return std::nullopt;
    }
}

std::optional<Token> tokenize_equality_operator(const Scanner& scanner) {
    bool next_character_is_equal = get_scanner_character(scanner, 1) == '=';

    switch (get_scanner_character(scanner)) {
        case '=': {
            if (next_character_is_equal) {
                return Token{"==", {}, TokenType::EQUAL_EQUAL, scanner.line};
            }
            return Token{"=", {}, TokenType::EQUAL, scanner.line};
        }
        case '!': {
            if (next_character_is_equal) {
                return Token{"!=", {}, TokenType::BANG_EQUAL, scanner.line};
            }
            return Token{"!", {}, TokenType::BANG, scanner.line};
        }

        default: return std::nullopt;
    }
}

char get_scanner_character(const Scanner& scanner, size_t offset) {
    size_t character_index = scanner.index + offset;

    if (scanner.contents.size() < character_index) return '\0';
    return scanner.contents[character_index];
}

void throw_error(int line, const std::string& message) {
    std::cout << "[line " << line << "] Error: " << message << std::endl;
}
