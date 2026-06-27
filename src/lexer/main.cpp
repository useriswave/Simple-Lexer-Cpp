#include "../../includes/lexer.h"
#include "../../includes/filereader.h"

#include <iostream>
#include <stdexcept>
#include <limits>

enum class InputMethod
{
    ReadFromFile = 1,
    WriteCode = 2
};

int userInput();
std::string getCodeFromFile();
std::string inputCode();
std::string getSourceCode();
void printTokens(const std::vector<Dumblang::Token>& tokens);

int main ()
{
    try {
        std::string code { getSourceCode() };

        Lexer lexer{ code };
        printTokens(lexer.tokenize());
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
    }

    return 0;
}

int userInput()
{
    while (true) {
        std::cout << "1. Enter code file path\n2. Write code directly.\n";
        std::cout << "\nInput: ";

        int input{};
        std::cin >> input;

        if (!std::cin || std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid. Please input (1-2)\n\n";
        } else {
            return input;
        }
    }
}

std::string getCodeFromFile()
{
    std::cout << "Enter the code file path: ";

    std::string path{};
    std::cin >> path;

    std::string temp{};

    return FileReader::readFile(path);
}

std::string inputCode()
{
    std::cout << "Write your code. When you're done, enter a new line and press: CTRL+D\n\n";

    std::string sourceCode{};
    std::string buffer{};

    while (getline(std::cin, buffer)) {
        sourceCode += buffer + '\n' ;
    }

    return sourceCode;
}

std::string getSourceCode()
{
    switch (static_cast<InputMethod>(userInput()))
    {
    case InputMethod::ReadFromFile:  return getCodeFromFile();
    case InputMethod::WriteCode:     return inputCode();
    default: throw std::runtime_error{ "ERROR: Unknown input" };
    }
}

void printTokens(const std::vector<Dumblang::Token>& tokens)
{
    for (const auto& token : tokens) {
        std::cout << token << '\n';
    }
}
