#include <iostream>
#include <fstream>
#include "area.h"
#include "parser.h"

// Parser.h
void parserFileError(std::ifstream &file);
int addIdentifier(std::string &identifier, std::string &type, std::stack<std::string> &stack);
std::string getInfo(std::string content, const std::string tag, std::size_t cenario);
std::vector<std::string> getCenarios(std::string content);
struct InfoCenario getInfoCenario(std::string content, std::string cenario);

// Area.h
Matrix nullMatrix(int altura, int largura);

std::string getFileContent(std::ifstream &file) {
    std::stringstream buffer;
    buffer << file.rdbuf(); // bufferiza o conteudo do arquivo  
    std::string content = buffer.str(); // conteudo do arquivo passa de stringstream para string
    return content;
}

int main() {

    // Nome do arquivo
    //char xmlfilename[100];
    //std::cin >> xmlfilename;

    // Abrindo o arquivo
    std::ifstream file;
    //file.open("cenarios/" + std::string(xmlfilename) + ".xml");
    file.open("cenarios/teste.xml");

    // Checando se o arquivo foi aberto corretamente
    if (!file.is_open()) {
        std::cout << "ERRO: falha abertura do arquivo." << std::endl;
        return 1;
    }

    // Testando o arquivo para aninhamento correto
    parserFileError(file);
    file.clear();
    file.seekg(0, std::ios::beg); // limpando buffer/ponteiro do arquivo

    // Transforma arquivo em string
    std::string content = getFileContent(file);

    // Pega o nome dos cenarios no arquivo
    std::vector<std::string> cenarios = getCenarios(content);

    // Pega as informacoes dos cenarios
    std::vector<struct InfoCenario> infoCenarios;

    for (std::string cenario : cenarios) {
        infoCenarios.push_back(getInfoCenario(content, cenario));
    }
    
    for (struct InfoCenario infoCenario : infoCenarios) {
        Matrix newMatrix = MatrixCreator(infoCenario);
    }
    // Matrix matrizNova = nullMatrix(altura, largura);

    // Fecha o arquivo
    file.close();

    return 0;
}