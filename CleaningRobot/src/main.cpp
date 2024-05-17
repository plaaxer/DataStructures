#include <iostream>
#include <fstream>
#include <stack>

void addIdentifier(std::string &identifier, std::string &type, std::stack<std::string> &stack) {
    if (type == "abertura") {
        stack.push(identifier);
    } else {
        if (stack.empty()) {
            std::cout << "ERRO: identificador de fechamento sem nenhum de abertura (stack vazia)." << std::endl;
            return;
        } else {
            std::string top = stack.top();
            if (top != identifier) {
                std::cout << "ERRO: identificador de fechamento nao corresponde ao ultimo de abertura." << std::endl;
                return;
            }
            stack.pop();
        }
    }
}

void parserFile(std::ifstream &file) {
    // Initialize the stack
    std::stack<std::string> stack;

    // Read and process the contents of the file
    bool active = false;
    std::string line;
    std::string identifier;
    std::string type;

    while (std::getline(file, line)) {
        for (std::size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '>') {
                addIdentifier(identifier, type, stack);
                identifier = "";
                active = false;
            }
            if (active && c != '/') {
                identifier += c;
            }
            if (c == '<') {
                char nextChar = line[i + 1];
                if (nextChar == '/') {
                    type = "fechamento";
                } else {
                    type = "abertura";
                }
                active = true;
            }
        }
    }
    if (!stack.empty()) {
        std::cout << "ERRO: identificador de abertura sem identificador de fechamento correspondente." << std::endl;
        return; // Stop the code execution and return the error
    }
}

int main() {

    // Get the file name
    char xmlfilename[100];
    std::cin >> xmlfilename;

    // Open the file
    std::ifstream file;
    file.open("cenarios/" + std::string(xmlfilename) + ".xml");

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cout << "ERRO: falha abertura do arquivo." << std::endl;
        return 1;
    }

    // Test the file
    parserFile(file);

    // Close the file
    file.close();

    return 0;
}