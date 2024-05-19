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
            std::cout << matrix.data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void calculateArea(const Matrix& matrix, const struct InfoCenario info) {

    // VARIAVEIS
    int area = 0;
    std::queue<std::pair<int,int>> q; // fila que armazena as coordenas x e y
    Matrix newMatrix = nullMatrix(info.altura, info.largura); // cria a matriz auxiliar (por enquanto zerada)

    //IMPORTANTE: CHECAR SE ESTA ZERADA MESMO

    // START: IGUAL O ALGORITMO SOLICITADO
    q.push(std::make_pair(info.x, info.y)); // adiciona as coordenadas iniciais a fila
    newMatrix.data[info.x][info.y] = 1; // marca a posicao atual como visitada

    while (!q.empty()) { // enquanto fila nao vazia

        std::pair<int,int> now = q.front(); // pega as coordenadas atuais
        q.pop(); // remove o primeiro elemento da fila
        int i = now.first;
        int j = now.second;

        // TESTES
        if (i < 0 || i >= matrix.rows || j < 0 || j >= matrix.cols) { // checa se esta dentro dos limites da matriz
            continue;
        }
        if (matrix.data[i][j] == 0) { // checa se tem que visitar
            continue;
        }

        if (newMatrix.data[i][j] == 1) { // checa se ja foi visitado
            continue;
        }

        newMatrix.data[i][j] = 1; // marca a posicao atual como visitada
        area++;
        q.push(std::make_pair(i+1, j));
        q.push(std::make_pair(i-1, j));
        q.push(std::make_pair(i, j+1));
        q.push(std::make_pair(i, j-1));
    }
    std::cout << area << std::endl;

}

#endif