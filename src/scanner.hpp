#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <vector>
#include <string>

#include "token.hpp"

struct Scanner {
    std::vector<Token> tokens;
    std::string contents;
    int line;
    int index;
};

std::string stringify_file_contents(const std::string& file_name);
std::vector<Token> tokenize_file_contents(const std::string& file_contents);

std::string stringify_token_type(TokenType token_type);
Token tokenize_single_character_token(char character, int line);

#endif
