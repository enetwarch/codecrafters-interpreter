#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <any>
#include <cstdlib>
#include <string>
#include <vector>

#include "token.hpp"

class Scanner {
    const std::string file_contents;
    std::vector<Token> tokens;
    std::size_t starting_index{0};
    std::size_t current_index{0};
    int current_line{1};
    bool has_error{false};

   public:
    explicit Scanner(std::string file_contents);
    std::vector<Token>& scan_tokens();

   private:
    void scan_token();
    void skip_space();
    void skip_line();

    void string();
    void number();

    void add_token(TokenType type);
    void add_token(TokenType type, const Literal& literal);

    char advance();
    char peek() const;
    char peek_next() const;
    bool is_at_end() const;
    bool match(char expected);

    void error(int line, const std::string& message);
};

#endif
