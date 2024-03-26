#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 1000
#define MAX_LENGTH 21

// Função para comparar duas strings para uso no qsort
int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int n;
    scanf("%d", &n); // Lê a quantidade de listas de compras

    char buffer[MAX_LENGTH * MAX_ITEMS]; // Buffer para armazenar os itens de cada lista
    char *allItems[n][MAX_ITEMS]; // Matriz para armazenar os itens de todas as listas
    int allItemsCount[n]; // Vetor para contar a quantidade de itens em cada lista

    // Lê e processa todas as listas de compras
    for (int i = 0; i < n; i++) {
        allItemsCount[i] = 0; // Inicializa o contador de itens

        // Lê a linha inteira de itens
        scanf(" %[^\n]", buffer);

        // Tokeniza a linha para separar os itens
        char *token = strtok(buffer, " ");
        while (token != NULL) {
            // Verifica se o item já foi adicionado
            int duplicate = 0;
            for (int j = 0; j < allItemsCount[i]; j++) {
                if (strcmp(allItems[i][j], token) == 0) {
                    duplicate = 1;
                    break;
                }
            }
            // Se não foi adicionado, adiciona à lista de itens
            if (!duplicate) {
                allItems[i][allItemsCount[i]] = strdup(token);
                allItemsCount[i]++;
            }
            token = strtok(NULL, " ");
        }

        // Ordena os itens alfabeticamente
        qsort(allItems[i], allItemsCount[i], sizeof(char *), compareStrings);
    }

    // Imprime as respostas
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < allItemsCount[i]; j++) {
            printf("%s", allItems[i][j]);
            if (j < allItemsCount[i] - 1) {
                printf(" ");
            }
            free(allItems[i][j]); // Libera a memória alocada para o item
        }
        printf("\n");
    }

    return 0;
}