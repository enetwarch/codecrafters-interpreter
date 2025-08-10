#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <vector>
#include <string>

#include "token.hpp"

std::vector<Token> scan_file(const std::string& file_contents);
void read_tokens(const std::vector<Token>& tokens);

std::string stringify(Token token);
Token tokenize(char character);

#endif
