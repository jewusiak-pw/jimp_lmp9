#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdio.h>

/*
 * Zwraca:
 *  0 - poprawne działanie
 *  1 - problem ładowania macierzy A
 *  2 - problem ładowania macierzy b
 *  3 - dzielenie przez 0
 *  4 - złe wymiary macierzy
 *  5 - za mało argumentów
 */
int main(int argc, char **argv) {
    int res;
    if(argc<3){
        puts("Za mala liczba argumentow!");
        return 5;
    }

    Matrix *A = readFromFile(argv[1]);
    Matrix *b = readFromFile(argv[2]);
    Matrix *x;

    if (A == NULL) return 1;
    if (b == NULL) return 2;


    if ((res = eliminate(A, b)) == 1) {
        puts("Dzielenie przez 0!");
        return 3;
    }

    //printToScreen(A);
    //printToScreen(b);

    x = createMatrix(b->r, 1);
    if (x != NULL) {

        res = backsubst(x, A, b);
        if (res == 2) {
            puts("Złe wymiary macierzy!");
            return 4;
        }
        if (res == 1) {
            puts("Dzielenie przez 0!");
            return 3;
        }
        printToScreen(x);
        freeMatrix(x);
    } else {
        fprintf(stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
    }

    freeMatrix(A);
    freeMatrix(b);

    return 0;
}
