#include "../../includes/lexer.h"
#include "../../includes/filereader.h"

#include <iostream>
#include <stdexcept>

void printTokens(const std::vector<Dumblang::Token>& tokens)
{
    for (const auto& token : tokens) {
        std::cout << token << '\n';
    }
}

int main (int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "ERROR: Please enter the file path.\n";
    }

    try {
        std::string sourceCode { FileReader::readFile(argv[1]) };

        Lexer lexer{ sourceCode };
        lexer.tokenize();

        printTokens(lexer.getTokens());
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
    }

    return 0;
}
