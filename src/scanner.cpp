#include "scanner.hpp"

#include <cctype>
#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

#include "token.hpp"
using enum TokenType;

Scanner::Scanner(std::string file_contents)
    : file_contents{std::move(file_contents)} {}

std::vector<Token>& Scanner::scan_tokens() {
    while (!is_at_end()) {
        starting_index = current_index;
        scan_token();
    }

    tokens.push_back(Token{.type = END_OF_FILE, .line = current_line});
    return tokens;
}

void Scanner::scan_token() {
    switch (advance()) {
        case '(': add_token(LEFT_PAREN); break;
        case ')': add_token(RIGHT_PAREN); break;
        case '{': add_token(LEFT_BRACE); break;
        case '}': add_token(RIGHT_BRACE); break;
        case ',': add_token(COMMA); break;
        case '.': add_token(DOT); break;
        case '-': add_token(MINUS); break;
        case '+': add_token(PLUS); break;
        case ';': add_token(SEMICOLON); break;
        case '*': add_token(STAR); break;

        case '!': add_token(match('=') ? BANG_EQUAL : BANG); break;
        case '=': add_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
        case '>': add_token(match('=') ? GREATER_EQUAL : EQUAL); break;
        case '<': add_token(match('=') ? LESS_EQUAL : EQUAL); break;
        case '/': match('/') ? skip_line() : add_token(SLASH); break;

        case ' ': [[fallthrough]];
        case '\f': [[fallthrough]];
        case '\r': [[fallthrough]];
        case '\t': [[fallthrough]];
        case '\v': break;
        case '\n': current_line++; break;

        default: error(current_line, "Unexpected character."); break;
    }
}

void Scanner::skip_space() {
    if (!std::isspace(peek())) return;
}

void Scanner::skip_line() {
    while (!is_at_end() && peek() != '\n') advance();
}

void Scanner::add_token(TokenType type) { add_token(type, "null"); }
void Scanner::add_token(TokenType type, const std::string& literal) {
    std::string lexeme =
        file_contents.substr(starting_index, current_index - starting_index);
    tokens.push_back(Token{type, lexeme, literal, current_line});
}

bool Scanner::is_at_end() const {
    return current_index >= file_contents.size();
}

char Scanner::advance() {
    if (is_at_end()) return '\0';
    return file_contents[current_index++];
}

char Scanner::peek() const {
    if (is_at_end()) return '\0';
    return file_contents[current_index];
}

bool Scanner::match(char expected) {
    if (is_at_end() || peek() != expected) return false;
    current_index++;
    return true;
}

void Scanner::error(int line, const std::string& message) {
    has_error = true;
    std::cout << "[line " << line << "] Error: " << message << std::endl;
}
