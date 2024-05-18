#include <iostream>

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
            std::cout << "0";
            next.data[i][j] = 0;
        }
    }
    return next;
}
