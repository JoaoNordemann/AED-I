#include <stdio.h>

#define TAMANHO 9

int verificar_linha(int sudoku[TAMANHO][TAMANHO], int linha) {
    int presenca[TAMANHO + 1] = {0}; // Inicializa um array para rastrear os números de 1 a 9

    for (int j = 0; j < TAMANHO; j++) {
        int num = sudoku[linha][j];
        if (presenca[num] == 1) // Se o número já estiver presente nesta linha
            return 0;
        presenca[num] = 1;
    }

    return 1;
}

int verificar_coluna(int sudoku[TAMANHO][TAMANHO], int coluna) {
    int presenca[TAMANHO + 1] = {0}; // Inicializa um array para rastrear os números de 1 a 9

    for (int i = 0; i < TAMANHO; i++) {
        int num = sudoku[i][coluna];
        if (presenca[num] == 1) // Se o número já estiver presente nesta coluna
            return 0;
        presenca[num] = 1;
    }

    return 1;
}

int verificar_regiao(int sudoku[TAMANHO][TAMANHO], int inicioLinha, int inicioColuna) {
    int presenca[TAMANHO + 1] = {0}; // Inicializa um array para rastrear os números de 1 a 9

    for (int i = inicioLinha; i < inicioLinha + 3; i++) {
        for (int j = inicioColuna; j < inicioColuna + 3; j++) {
            int num = sudoku[i][j];
            if (presenca[num] == 1) // Se o número já estiver presente nesta região
                return 0;
            presenca[num] = 1;
        }
    }

    return 1;
}

int verificar_sudoku(int sudoku[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        if (!verificar_linha(sudoku, i) || !verificar_coluna(sudoku, i))
            return 0;
    }

    for (int i = 0; i < TAMANHO; i += 3) {
        for (int j = 0; j < TAMANHO; j += 3) {
            if (!verificar_regiao(sudoku, i, j))
                return 0;
        }
    }

    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int instancia = 1; instancia <= n; instancia++) {
        int sudoku[TAMANHO][TAMANHO];

        // Lendo a grade do Sudoku
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = 0; j < TAMANHO; j++) {
                scanf("%d", &sudoku[i][j]);
            }
        }

        printf("Instancia %d\n", instancia);

        if (verificar_sudoku(sudoku))
            printf("SIM\n\n");
        else
            printf("NAO\n\n");
    }

    return 0;
}