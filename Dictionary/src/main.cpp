#include "trie.h"
#include <iostream>
#include <fstream>
#include <sstream>

// trie.h
void insert(NodeTrie* root, const std::string& word, int initial_pos, int length);
void tryWord(std::string& word, NodeTrie* root);

void loadDictionary(const std::string& filePath, NodeTrie* root) {

    std::string word;
    std::string definition;
    std::ifstream file("dics/" + filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    char ch;
    int pos = 0;
    int initial_pos;
    int end_pos;

    while (file.get(ch)) {
        if (ch == '[') {
            initial_pos = pos;
            word.clear();
            definition.clear();
            while (file.get(ch) && ch != ']') {
                pos++;
                word += ch;
            }
            while (file.get(ch) && ch != '\n') {
                pos++;
                definition += ch;
            }
            end_pos = pos;
            insert(root, word, initial_pos, end_pos - initial_pos - 1);
        }
    }

    file.close();
}

int main() {

    NodeTrie* root = new NodeTrie(0, 0);  // inicializa a raiz

    // --------ABERTURA DO ARQUIVO--------

    std::string filename;
    std::string word;
    std::string content;

    std::cin >> filename;  // entrada
    
    loadDictionary(filename, root);

    // --------LEITURA DAS PALAVRAS--------

    while (1) {  // leitura das palavras ate' encontrar "0"
        std::cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        tryWord(word, root);
    }

    return 0;
}