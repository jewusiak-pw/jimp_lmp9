#include "gauss.h"
#include <math.h>

//Wybiera element główny w macierzy mat, kolumnie col
int select_max_row(Matrix *mat, int col) {
    int i, max_row = -1;

    for (i = col; i < mat->r; i++) {
        if (mat->data[i][col] != 0) {
            if (max_row == -1)
                max_row = i;
            if (fabs(mat->data[max_row][col]) < fabs(mat->data[i][col]))
                max_row = i;
        }
    }
    return max_row;
}

//Zamienia rzędy r1 i r2 w macierzy mat
void swap_rows(Matrix *mat, int r1, int r2) {
    double temp;
    int i;
    for (i = 0; i < mat->c; i++) {
        temp = mat->data[r1][i];
        mat->data[r1][i] = mat->data[r2][i];
        mat->data[r2][i] = temp;
    }
}

//odejmuje rząd main_row pomnożony przez skalar value, od l_row, w macierzy mat
void subtract_row(Matrix *mat, int main_row, int l_row, double value) {
    int i;
    for (i = 0; i < mat->c; i++)
        mat->data[l_row][i] -= value * mat->data[main_row][i];
}

//Dzieli macierz rozszerzoną A|b (ab) na macierze A (a) i b (b)
void split_matrix(Matrix *ab, Matrix *a, Matrix *b) {
    int i, j;
    for (i = 0; i < a->r; i++) {
        for (j = 0; j < a->c; j++)
            a->data[i][j] = ab->data[i][j];
        b->data[i][0] = ab->data[i][j];
    }
}

//Łączy macierze A (a) i b (b) w macierz rozszerzoną A|b (ab)
Matrix *join_matrices(Matrix *a, Matrix *b) {
    Matrix *ab = createMatrix(a->r, a->c + b->c);
    int i, j;
    for (i = 0; i < ab->r; i++) {
        for (j = 0; j < ab->c - 1; j++)
            ab->data[i][j] = a->data[i][j];
        ab->data[i][j] = b->data[i][0];
    }
    return ab;
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int i, j;

    Matrix *ab = join_matrices(mat, b);

    for (i = 0; i < ab->r; i++) {
        int row = select_max_row(ab, i);//el główny
        if (row == -1)//dzielenie przez 0
            return 1;
        if (i != ab->r - 1) {
            swap_rows(ab, row, i);
            for (j = i + 1; j < ab->r; j++)
                subtract_row(ab, i, j, ab->data[j][i] / ab->data[i][i]);
        }
    }


    split_matrix(ab, mat, b);

    return 0;
}











