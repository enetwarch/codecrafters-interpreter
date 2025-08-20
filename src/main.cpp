#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "scanner.hpp"
#include "token.hpp"

std::string read_file(const std::string& filename);

int main(int argc, char* argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    const std::string command = argv[1];
    const std::string file_name = argv[2];
    if (command == "tokenize") {
        Scanner scanner(read_file(file_name));

        for (const Token& token : scanner.scan_tokens()) {
            std::cout << stringify_token_type(token.type) << " " << token.lexeme
                      << " " << stringify_token_literal(token.literal)
                      << std::endl;
        }
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

std::string read_file(const std::string& file_name) {
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
