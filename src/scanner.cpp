#include "scanner.hpp"

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
std::optional<Token> tokenize_single_character(const Scanner& scanner);
std::optional<Token> tokenize_equality_operator(const Scanner& scanner);
std::optional<Token> tokenize_potential_comment(const Scanner& scanner);

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
    scanner.tokens.push_back({"", {}, TokenType::END_OF_FILE, scanner.line});

    return scanner.tokens;
}

Scanner& tokenize_next_possible_lexeme(Scanner& scanner) {
    std::optional<Token> single_character_token =
        tokenize_single_character(scanner);
    if (single_character_token.has_value()) {
        scanner.index += single_character_token.value().lexeme.size();
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

    std::optional<Token> potential_comment_token =
        tokenize_potential_comment(scanner);
    if (potential_comment_token.has_value()) {
        if (potential_comment_token.value().type != TokenType::UNKNOWN) {
            scanner.index += potential_comment_token.value().lexeme.size();
            scanner.tokens.push_back(potential_comment_token.value());
            return scanner;
        }

        std::unordered_set<char> terminators = {'\n', '\0'};
        while (!terminators.contains(scan_character(scanner))) scanner.index++;
        return scanner;
    }

    throw_error(scanner.line, std::format("Unexpected character: {}",
                                          scan_character(scanner)));
    scanner.error = true;
    scanner.index += 1;
    return scanner;
}

std::optional<Token> tokenize_single_character(const Scanner& scanner) {
    switch (scan_character(scanner)) {
        case '(': return Token{.lexeme = "(", .type = TokenType::LEFT_PAREN};
        case ')': return Token{.lexeme = ")", .type = TokenType::RIGHT_PAREN};
        case '{': return Token{.lexeme = "{", .type = TokenType::LEFT_BRACE};
        case '}': return Token{.lexeme = "}", .type = TokenType::RIGHT_BRACE};

        case ',': return Token{.lexeme = ",", .type = TokenType::COMMA};
        case '.': return Token{.lexeme = ".", .type = TokenType::DOT};
        case ';': return Token{.lexeme = ";", .type = TokenType::SEMICOLON};

        case '+': return Token{.lexeme = "+", .type = TokenType::PLUS};
        case '-': return Token{.lexeme = "-", .type = TokenType::MINUS};
        case '*': return Token{.lexeme = "*", .type = TokenType::STAR};

        default: return std::nullopt;
    }
}

std::optional<Token> tokenize_equality_operator(const Scanner& scanner) {
    bool next_character_is_equal = scan_character(scanner, 1) == '=';

    switch (scan_character(scanner)) {
        case '=':
            if (next_character_is_equal)
                return Token{.lexeme = "==", .type = TokenType::EQUAL_EQUAL};
            return Token{.lexeme = "=", .type = TokenType::EQUAL};
        case '!':
            if (next_character_is_equal)
                return Token{.lexeme = "!=", .type = TokenType::BANG_EQUAL};
            return Token{.lexeme = "!", .type = TokenType::BANG};
        case '<':
            if (next_character_is_equal)
                return Token{.lexeme = "<=", .type = TokenType::LESS_EQUAL};
            return Token{.lexeme = "<", .type = TokenType::LESS};
        case '>':
            if (next_character_is_equal)
                return Token{.lexeme = ">=", .type = TokenType::GREATER_EQUAL};
            return Token{.lexeme = ">", .type = TokenType::GREATER};

        default: return std::nullopt;
    }
}

std::optional<Token> tokenize_potential_comment(const Scanner& scanner) {
    if (scan_character(scanner) != '/') return std::nullopt;

    if (scan_character(scanner, 1) == '/') return Token{};
    return Token{.lexeme = "/", .type = TokenType::SLASH};
}

char scan_character(const Scanner& scanner, size_t offset) {
    size_t character_index = scanner.index + offset;

    if (scanner.contents.size() < character_index) return '\0';
    return scanner.contents[character_index];
}

void throw_error(int line, const std::string& message) {
    std::cout << "[line " << line << "] Error: " << message << std::endl;
}
