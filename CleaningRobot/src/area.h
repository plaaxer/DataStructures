#ifndef HEADER2_H
#define HEADER2_H
#include <iostream>
#include "parser.h"

struct Matrix {
    int rows;
    int cols;
    int** data;

    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
};

Matrix nullMatrix(int altura, int largura) {
    // Matriz auxiliar, cheia de 0s
    Matrix next(altura, largura);
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            next.data[i][j] = 0;
        }
    }
    return next;
}

Matrix MatrixCreator(struct InfoCenario info){
    Matrix newMatrix = nullMatrix(info.altura, info.largura); // cria uma nova matriz (por enquanto zerada)
    // Transformar info.matriz em newMatrix.data
    for (int i = 0; i < info.altura; ++i) {
        for (int j = 0; j < info.largura; ++j) {
            // a logica de acesso esta correta, o erro eh na hora de atribuir o valor NAO APAGAR OS PRINTS, COMENTAR
            std::cout << "info.matriz[" << (j+1)+(i*info.largura) + i << "] = " << info.matriz[(j+1)+(i*info.largura) + i] << "\n";

            newMatrix.data[i][j] = info.matriz[(j+1)+(i*info.largura) + i] -48; // explicacao em README.md

            std::cout << "NewMatrix.data[" << i << "][" << j << "] = " << newMatrix.data[i][j] << "\n";
        }
    }
    return newMatrix;
}

#endif