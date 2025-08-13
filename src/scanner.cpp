#include "scanner.hpp"

#include <cctype>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "token.hpp"

Scanner& tokenize_next_possible_lexeme(Scanner& scanner);

std::optional<Scanner*> tokenize_single_character(Scanner& scanner);
std::optional<Scanner*> tokenize_equality_operator(Scanner& scanner);
std::optional<Scanner*> tokenize_potential_comment(Scanner& scanner);
Scanner& report_unknown_character_error(Scanner& scanner);

Scanner* tokenize(Scanner& scanner, TokenType token_type, int advance);
char scan_character(const Scanner& scanner, size_t offset = 0);
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
    scanner.tokens.push_back(Token{.type = TokenType::END_OF_FILE});

    return scanner.tokens;
}

Scanner& tokenize_next_possible_lexeme(Scanner& scanner) {
    while (std::isspace(scan_character(scanner))) scanner.index++;
    if (scanner.index >= scanner.contents.size()) return scanner;

    if (tokenize_single_character(scanner).has_value()) return scanner;
    if (tokenize_equality_operator(scanner).has_value()) return scanner;
    if (tokenize_potential_comment(scanner).has_value()) return scanner;

    return report_unknown_character_error(scanner);
}

std::optional<Scanner*> tokenize_single_character(Scanner& scanner) {
    switch (scan_character(scanner)) {
        case '(': return tokenize(scanner, TokenType::LEFT_PAREN, 1);
        case ')': return tokenize(scanner, TokenType::RIGHT_PAREN, 1);
        case '{': return tokenize(scanner, TokenType::LEFT_BRACE, 1);
        case '}': return tokenize(scanner, TokenType::RIGHT_BRACE, 1);
        case ',': return tokenize(scanner, TokenType::COMMA, 1);
        case '.': return tokenize(scanner, TokenType::DOT, 1);
        case ';': return tokenize(scanner, TokenType::SEMICOLON, 1);
        case '+': return tokenize(scanner, TokenType::PLUS, 1);
        case '-': return tokenize(scanner, TokenType::MINUS, 1);
        case '*': return tokenize(scanner, TokenType::STAR, 1);

        default: return std::nullopt;
    }
}

std::optional<Scanner*> tokenize_equality_operator(Scanner& scanner) {
    bool equal_next = scan_character(scanner, 1) == '=';
    switch (scan_character(scanner)) {
        case '=':
            if (!equal_next) return tokenize(scanner, TokenType::EQUAL, 1);
            return tokenize(scanner, TokenType::EQUAL_EQUAL, 2);
        case '!':
            if (!equal_next) return tokenize(scanner, TokenType::BANG, 1);
            return tokenize(scanner, TokenType::BANG_EQUAL, 2);
        case '<':
            if (!equal_next) return tokenize(scanner, TokenType::LESS, 1);
            return tokenize(scanner, TokenType::LESS_EQUAL, 2);
        case '>':
            if (!equal_next) return tokenize(scanner, TokenType::GREATER, 1);
            return tokenize(scanner, TokenType::GREATER_EQUAL, 2);

        default: return std::nullopt;
    }
}

std::optional<Scanner*> tokenize_potential_comment(Scanner& scanner) {
    if (scan_character(scanner) != '/') return std::nullopt;
    if (scan_character(scanner, 1) != '/') {
        return tokenize(scanner, TokenType::SLASH, 1);
    }

    std::unordered_set<char> terminators = {'\n', '\0'};
    while (!terminators.contains(scan_character(scanner))) scanner.index++;
    return &scanner;
}

Scanner& report_unknown_character_error(Scanner& scanner) {
    char c = scan_character(scanner);
    throw_error(scanner.line, std::format("Unknown character: {}", c));

    scanner.error = true;
    scanner.index += 1;
    return scanner;
}

Scanner* tokenize(Scanner& scanner, TokenType token_type, size_t advance) {
    scanner.index += advance;
    scanner.tokens.push_back(Token{.type = token_type});

    return &scanner;
}

char scan_character(const Scanner& scanner, size_t offset) {
    size_t character_index = scanner.index + offset;

    if (character_index >= scanner.contents.size()) return '\0';
    return scanner.contents[character_index];
}

void throw_error(int line, const std::string& message) {
    std::cout << "[line " << line << "] Error: " << message << std::endl;
}
