#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "scanner.hpp"
#include "token.hpp"

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
        std::string file_contents = stringify_file_contents(file_name);
        std::vector<Token> tokens = tokenize_file_contents(file_contents);

        for (Token& token : tokens) {
            std::cout << stringify_token_type(token.type) << " "
                      << lexemize_token_type(token.type) << " " << token.literal
                      << std::endl;
        }
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
