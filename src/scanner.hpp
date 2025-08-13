#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>

#include "token.hpp"

struct Scanner {
    std::vector<Token> tokens;
    std::string contents;
    int line;
    int index;
    bool error;
};

std::string stringify_file_contents(const std::string& file_name);
std::vector<Token> tokenize_file_contents(const std::string& file_contents);

#endif
