#include <iostream>

// implementação baseada no link fornecido do geeksforgeeks
// https://www.geeksforgeeks.org/trie-insert-and-search/

// a medida em que a palavra eh adicionada ela informa aos parentes q o numero de prefixo aumentou em 1

struct NodeTrie {

    NodeTrie* childNodes[26]; // no máximo 26 filhos (26 letras)
    bool wordEnd;
    int initial_pos;
    int length;
    int prefix_count = 0;

    NodeTrie(int initial_pos, int length, bool wordEnd = false)
    {
        // construtor
        // por default não é uma palavra e todos os filhos são nulos
        this->wordEnd = wordEnd;
        this->initial_pos = initial_pos;  // posição inicial do colchete []
        this->length = length;  // comprimento
        this->prefix_count = 1;  // contador de prefixos (1 =  prefixo de si mesmo)
        for (int i = 0; i < 26; i++)
            childNodes[i] = nullptr;
    }
};

void insert(NodeTrie* root, const std::string& word, int initial_pos, int length)
{
    NodeTrie* current = root;

    for (char c : word) {
        current->prefix_count++;  // incrementa o contador de prefixos
        int index = c - 'a';  // index de 0 a 25 com base nos valores ASCII
        if (current->childNodes[index] == nullptr) {  // se o filho com essa letra não existe, cria um novo
            current->childNodes[index] = new NodeTrie(initial_pos, length);
        }
        current = current->childNodes[index];  // avança para o próximo filho
    }

    current->wordEnd = true;  // sinaliza que a palavra termina nesse nó
}

NodeTrie* search(NodeTrie* root, const std::string& word)
{
    NodeTrie* current = root;

    for (char c : word) {
        int index = c - 'a';
        if (current->childNodes[index] == nullptr) {
            return nullptr;  // se em qualquer momento essa letra não existir, retornar falso
        }
        current = current->childNodes[index];  // avança para o próximo filho
    }

    if (current != nullptr && current->wordEnd){
        return current;  // retorna true se a palavra termina nesse nó
    }
    return nullptr;  // não é uma palavra
}

void tryWord(std::string& word, NodeTrie* root) {

    NodeTrie* result = search(root, word);  //  busca a palavra na trie
    if (result == nullptr) {  // se o ponteiro for nulo não é uma palavra
        std::cout << word << " is not prefix" << std::endl;
        return;
    }
    std::cout << word << " is prefix of " << result->prefix_count << " words"  << std::endl;
    std::cout << word << " is at (" << result->initial_pos << ", " << result->length << ")" << std::endl;
}

//  duvida para o meu eu do futuro; caso digite algo que n eh word, eh para falar que n eh prefixo ou o que
//  por enquanto se n for word n eh prefixo