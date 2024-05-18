#ifndef HEADER1_H
#define HEADER1_H

#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>

struct InfoCenario {
    std::string nome;
    int altura;
    int largura;
    int x;
    int y;
    std::string matriz; // a definicao de matriz sera feita posteriormente
};

int addIdentifier(std::string &identifier, std::string &type, std::stack<std::string> &stack) {
    // Verificando se o aninhamento de indentificadores esta correto
    if (type == "abertura") {
        stack.push(identifier);
    } else {
        if (stack.empty()) {
            return 1;
        } else {
            std::string top = stack.top();
            if (top != identifier) {
                return 1;
            }
            stack.pop();
        }
    }
    return 0;
}

void parserFileError(std::ifstream &file) {
    // Inicializando a stack
    std::stack<std::string> stack;

    bool active = false;
    std::string line;
    std::string identifier;
    std::string type;
    
    // Percorre o arquivo linha por linha
    while (std::getline(file, line)) {
        for (std::size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            // Verifica se o caractere indica o inicio de um identificador
            if (c == '>') {
                int result = addIdentifier(identifier, type, stack);
                // addIdentifier retorna 1 se houver erro
                if (result == 1) {
                    std::cout << "erro" << std::endl;
                    return;
                }
                identifier = "";
                active = false;
            }
            if (active && c != '/') {
                identifier += c;
            }
            // Tipo do identificador
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
        std::cout << "erro" << std::endl;
        return; // Se stack nao vazia
    }
}

    // retorna o conteudo dentro de uma tag a partir de um cenario
std::string getInfo(std::string content, const std::string tag, std::string cenario) { 

    std::string startSearch = "<" + cenario + ">"; // comeca a procurar a partir do cenario escolhido
    std::size_t start = content.find("<" + tag + ">", content.find(startSearch) + startSearch.size());
    std::size_t end = content.find("</" + tag + ">", start);

    std::string result = content.substr(start + tag.size() + 2, end - start - tag.size() - 2); // retorna o conteudo da tag (o que estiver entre)
    return result;
}

    // retorna os nomes dos cenarios presentes no arquivo
std::vector<std::string> getCenarios(std::string content) {

    std::vector<std::string> cenarios;

    std::size_t start = content.find("<nome>");
    while (start != std::string::npos) { // enquanto houver cenarios (arquivo nao acabou)
        std::size_t end = content.find("</nome>", start);
        std::string result = content.substr(start + 6, end - start - 6); // conteudo da tag (nome dos cenarios)
        cenarios.push_back(result); // adiciona o nome do cenario ao vetor

        start = content.find("<nome>", end);
    }
    return cenarios;
}

    // retorna todos as informacoes de cada cenario
struct InfoCenario getInfoCenario(std::string content, std::string cenario) {

    InfoCenario info;

    // utiliza a funcao getInfo para obter e atribui os valores a struct InfoCenario
    info.nome = cenario;
    info.altura = std::stoi(getInfo(content, "altura", cenario));
    info.largura = std::stoi(getInfo(content, "largura", cenario));
    info.x = std::stoi(getInfo(content, "x", cenario));
    info.y = std::stoi(getInfo(content, "y", cenario));
    info.matriz = getInfo(content, "matriz", cenario);

    return info;
}
#endif