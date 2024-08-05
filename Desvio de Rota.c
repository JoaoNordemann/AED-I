#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 501
#define INF 1000000

int n, p;
int board[MAXN][MAXN];
int prefix_black[MAXN][MAXN];
int prefix_white[MAXN][MAXN];

// Função para calcular os prefix sums
void compute_prefix_sums() {
    memset(prefix_black, 0, sizeof(prefix_black));
    memset(prefix_white, 0, sizeof(prefix_white));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            prefix_black[i][j] = prefix_black[i - 1][j] + prefix_black[i][j - 1] - prefix_black[i - 1][j - 1] + (board[i][j] == 1);
            prefix_white[i][j] = prefix_white[i - 1][j] + prefix_white[i][j - 1] - prefix_white[i - 1][j - 1] + (board[i][j] == 2);
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);

    // Inicializar o tabuleiro
    memset(board, 0, sizeof(board));

    // Ler as coordenadas das pedras pretas
    for (int i = 0; i < p; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        board[x][y] = 1; // Pedra preta
    }

    // Ler as coordenadas das pedras brancas
    for (int i = 0; i < p; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        board[x][y] = 2; // Pedra branca
    }

    // Calcular os prefix sums
    compute_prefix_sums();

    int black_areas = 0;
    int white_areas = 0;

    // Contar as sub-áreas quadradas de todas as dimensões
    for (int size = 1; size <= n; size++) {
        for (int i = size; i <= n; i++) {
            for (int j = size; j <= n; j++) {
                int x1 = i - size + 1;
                int y1 = j - size + 1;
                int x2 = i;
                int y2 = j;

                int black_count = prefix_black[x2][y2] - prefix_black[x1 - 1][y2] - prefix_black[x2][y1 - 1] + prefix_black[x1 - 1][y1 - 1];
                int white_count = prefix_white[x2][y2] - prefix_white[x1 - 1][y2] - prefix_white[x2][y1 - 1] + prefix_white[x1 - 1][y1 - 1];

                if (black_count > 0 && white_count == 0) {
                    black_areas++;
                }

                if (white_count > 0 && black_count == 0) {
                    white_areas++;
                }
            }
        }
    }

    // Imprimir o resultado
    printf("%d %d\n", black_areas, white_areas);

    return 0;
}
