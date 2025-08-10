#include <string>
#include <vector>
#include <iostream>

#include "scanner.hpp"
#include "token.hpp"

std::vector<Token> scan_file(const std::string& file_contents) {
    std::vector<Token> tokens;

    for (char character : file_contents) {
        Token token = tokenize(character);
        if (token == Token::UNKNOWN) continue;

        tokens.push_back(token);
    }
    tokens.push_back(Token::END_OF_FILE);

    return tokens;
}

void read_tokens(const std::vector<Token>& tokens) {
    for (Token token : tokens) {
        std::cout << stringify(token) << std::endl;
    }
}

std::string stringify(Token token) {
    switch (token) {
        case Token::LEFT_PARENTHESIS: return "LEFT_PAREN ( null";
        case Token::RIGHT_PARENTHESIS: return "RIGHT_PAREN ) null";
        case Token::END_OF_FILE: return "EOF  null";

        default: return "null";
    }
}

Token tokenize(char character) {
    switch (character) {
        case '(': return Token::LEFT_PARENTHESIS;
        case ')': return Token::RIGHT_PARENTHESIS;
        case '{': return Token::LEFT_BRACE;
        case '}': return Token::RIGHT_BRACE;
        case '[': return Token::LEFT_BRACKET;
        case ']': return Token::RIGHT_BRACKET;
        case ';': return Token::SEMICOLON;
        case ':': return Token::COLON;
        case ',': return Token::COMMA;
        case '.': return Token::DOT;
        case '+': return Token::PLUS;
        case '-': return Token::MINUS;
        case '*': return Token::ASTERISK;
        case '/': return Token::SLASH;

        default: return Token::UNKNOWN;
    }
}
