#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Função de comparação usada no qsort para ordenar os números.
// Ela compara dois números do tipo unsigned.
int compara(const void *a, const void *b) {
    if (*(unsigned*)a == *(unsigned *)b)
        return 0;
    else if (*(unsigned*)a > *(unsigned*)b)
        return 1;
    else
        return -1;
}

// Função de busca binária. Retorna true se encontrar o número, false caso contrário.
bool busca(unsigned *marmores, unsigned numero, unsigned short tam) {
    int inicio, fim, meio;
    inicio = 0;
    fim = tam - 1;

    while(inicio <= fim) {
        meio = (inicio + fim) / 2;

        // Se o valor central é menor, busca na metade superior.
        if (marmores[meio] < numero)
            inicio = meio + 1;
        // Se o valor central é maior, busca na metade inferior.
        else if(marmores[meio] > numero)
            fim = meio - 1;
        // Se encontrou o número, armazena a posição e retorna true.
        else {
            posicao = meio;
            return true;
        }
    }

    return false; // Retorna false se não encontrar o número.
}

// Variável global para armazenar a posição do número encontrado na busca.
int posicao;

void main () {
    unsigned short i, qtsCases = 0;
    unsigned short qtsConsultas;
    unsigned qtsMarmores, numero;

    // Loop infinito para processar vários casos de teste.
    while (true) {
        // Leitura da quantidade de mármores e de consultas.
        scanf("%u %hu", &qtsMarmores, &qtsConsultas);

        // Se ambos são 0, o programa termina.
        if (qtsConsultas == 0 && qtsMarmores == 0)
            break;

        // Cria um array para armazenar os mármores.
        unsigned marmores[qtsMarmores];

        // Leitura dos valores dos mármores.
        for (i = 0; i < qtsMarmores; i++)
            scanf("%u", &marmores[i]);

        // Ordena o array de mármores usando qsort.
        qsort(marmores, qtsMarmores, sizeof(unsigned), compara);

        // Imprime o número do caso de teste.
        printf("CASE# %u:\n", ++qtsCases);

        // Processa cada consulta.
        while (qtsConsultas--) {
            scanf("%u", &numero);

            // Se o número for encontrado na busca binária.
            if (busca(marmores, numero, qtsMarmores)) {

                // Verifica se há múltiplos números iguais.
                if (marmores[posicao - 1] == marmores[posicao]) {
                    // Move a posição para o primeiro número igual.
                    while (marmores[posicao - 1] == marmores[posicao])
                        posicao--;

                    // Imprime a posição do número encontrado.
                    printf("%u found at %u\n", numero, posicao + 1);
                } else {
                    printf("%u found at %u\n", numero, posicao + 1);
                }
            } else {
                // Se o número não foi encontrado, imprime "not found".
                printf("%u not found\n", numero);
            }
        }
    }
}
