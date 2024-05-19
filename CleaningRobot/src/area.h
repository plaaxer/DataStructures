#ifndef HEADER2_H
#define HEADER2_H
#include <iostream>
#include <queue>
#include "parser.h"

struct Matrix {
    int rows;
    int cols;
    std::vector<std::vector<int>> data;

    Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<int>(c)) {}
};

Matrix nullMatrix(int altura, int largura) {

    Matrix newMatrix = Matrix(altura, largura);
    return newMatrix; // retorna matriz nula
}

Matrix MatrixCreator(const struct InfoCenario info){

    Matrix newMatrix = nullMatrix(info.altura, info.largura); // cria uma nova matriz (por enquanto zerada)
    int add; // variavel para adicionar valores a matriz

    // Transformar info.matriz em newMatrix.data
    for (int i = 0; i < info.altura; ++i) {
        for (int j = 0; j < info.largura; ++j) {
            add = (j+1)+(i*info.largura) + i; // formula para adicionar valores a matriz (explicacao em readme.md)
            newMatrix.data[i][j] = std::stoi(info.matriz.substr(add, 1)); // pega o valor, transforma em int, e adiciona a matriz
        }
    }
    return newMatrix;
}

void printMatrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            std::cout << matrix.data[i][j];
        }
        std::cout << std::endl;
    }
}


void calculateArea(const Matrix& matrix, const InfoCenario& info) {
    int area = 0;
    std::queue<std::pair<int, int>> q; // fila que armazena as coordenadas x e y
    Matrix newMatrix = nullMatrix(info.altura, info.largura); // cria a matriz auxiliar (por enquanto zerada)

    // Direções possíveis na vizinhança-4: cima, baixo, esquerda, direita
    std::vector<std::pair<int, int>> direcoes = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // START: IGUAL O ALGORITMO SOLICITADO
    q.push(std::make_pair(info.x, info.y)); // adiciona as coordenadas iniciais a fila
    newMatrix.data[info.x][info.y] = 1; // marca a posição atual como visitada (atribui 1 em R)
    area++; // incrementa a área já que (x, y) é a posição inicial

    while (!q.empty()) {
        std::pair<int, int> point = q.front(); // extraindo o topo da fila
        int x = point.first;
        int y = point.second;
        q.pop(); // remove o topo da fila

        for (const auto& direction : direcoes) { // verifica os vizinhos (direcoes para quais se pode mover)
            int dx = direction.first;
            int dy = direction.second;
            int novo_x = x + dx;
            int novo_y = y + dy;

            // verificar se está dentro dos limites da matriz
            if (novo_x >= 0 && novo_x < info.altura && novo_y >= 0 && novo_y < info.largura) {
                // verificar se o vizinho é 1 na matriz e ainda não foi visitado (0 em newMatrix)
                if (matrix.data[novo_x][novo_y] == 1 && newMatrix.data[novo_x][novo_y] == 0) {
                    q.push(std::make_pair(novo_x, novo_y));
                    newMatrix.data[novo_x][novo_y] = 1; // marca como visitado
                    area++; // finalmente, incrementa a área
                }
            }
        }
    }
    // CASO ESPECIAL
    if (area == 1 && matrix.data[info.x][info.y] == 0) { // se o robo apenas "nasceu" e nao tem que visitar nenhum lugar
        area = 0;
    }

    std::cout << info.nome << " " << area << std::endl;
}

#endif