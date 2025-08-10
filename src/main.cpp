#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "scanner.hpp"
#include "token.hpp"

std::string read_file_contents(const std::string& filename);

int main(int argc, char *argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return EXIT_FAILURE;
    }

    const std::string command = argv[1];
    const std::string filename = argv[2];
    if (command == "tokenize") {
        std::string file_contents = read_file_contents(filename);
        std::vector<Token> tokens = scan_file(file_contents);

        read_tokens(tokens);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

std::string read_file_contents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
