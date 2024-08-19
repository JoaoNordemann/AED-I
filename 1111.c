#include <stdio.h>
#include <stdbool.h>

#define INF 0x3f3f3f3fU // Define um valor grande para representar o infinito.
#define MAXSIZE 123     // Define o tamanho máximo para o grafo.

typedef unsigned uint;  // Define um tipo `uint` como um alias para `unsigned int`.

uint g[MAXSIZE][MAXSIZE]; // Matriz de adjacência do grafo, onde `g[i][j]` representa a distância entre os vértices `i` e `j`.

void fw(int n);          // Declaração da função que implementa o algoritmo de Floyd-Warshall.
uint min(uint a, uint b); // Declaração da função que retorna o menor valor entre `a` e `b`.

int main(int argc, char **argv) {
    int u, v, w, n, z, x;

    // Enquanto houver entrada para o número de vértices `n`.
    while (scanf("%d%*c", &n), n) {

        // Inicializa a matriz de adjacência.
        for (int i = 0; i < n * n; ++i) {
            for (int j = 0; j < n * n; ++j)
                g[i][j] = INF; // Inicializa com "infinito" (indicando que não há caminho direto entre os vértices).
            g[i][i] = 0U; // A distância de um vértice para si mesmo é zero.
        }

        // Preenche a matriz de adjacência com base nas entradas fornecidas.
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d %d %d %d", &u, &v, &z, &w);

                // Verifica as condições para definir as arestas do grafo.
                if (u == 1)
                    g[i * n + j][(i + 1) * n + j] = 1U; // Aresta para o vértice abaixo.
                if (v == 1)
                    g[i * n + j][(i - 1) * n + j] = 1U; // Aresta para o vértice acima.
                if (z == 1)
                    g[i * n + j][i * n - 1 + j] = 1U; // Aresta para o vértice à esquerda.
                if (w == 1)
                    g[i * n + j][i * n + 1 + j] = 1U; // Aresta para o vértice à direita.
            }
        }

        x = n;

        // Chama a função para aplicar o algoritmo de Floyd-Warshall.
        fw(n * n);

        // Lê o número de consultas e processa cada uma.
        scanf("%d", &n);
        while (n--) {
            scanf("%d %d %d %d", &u, &v, &z, &w);

            u = u + v * x; // Calcula a posição linear do vértice de origem.
            z = z + w * x; // Calcula a posição linear do vértice de destino.

            // Verifica se existe um caminho entre os vértices e imprime a distância mínima.
            if (g[u][z] != INF)
                printf("%u\n", g[u][z]);
            else
                puts("Impossible"); // Imprime "Impossible" se não houver caminho.
        }

        putchar_unlocked('\n'); // Adiciona uma nova linha após cada conjunto de consultas.
    }

    return 0;
}

// Função que implementa o algoritmo de Floyd-Warshall.
void fw(int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                // Atualiza a matriz de adjacência com o menor caminho encontrado.
                g[j][k] = min(g[j][k], g[j][i] + g[i][k]);
}

// Função inline para calcular o mínimo entre dois valores.
inline uint min(uint a, uint b) {
    return a < b ? a : b;
}
