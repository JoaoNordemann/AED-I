#include <stdio.h>

int main ()
{
    // Declaração de uma matriz 12x12 de números reais e variáveis auxiliares para soma, média e contador.
    float m[12][12], soma = 0, media = 0, cont = 0;
    int i, j; // Variáveis de controle de loops.
    char operacao; // Variável para armazenar a operação escolhida ('S' para soma, 'M' para média).

    // Lê o caractere que define a operação a ser realizada.
    scanf("%c", &operacao);

    // Lê os elementos da matriz 12x12.
    for (i = 0; i < 12; i++)
    {
        for (j = 0; j < 12; j++)
        {
            scanf("%f", &m[i][j]); // Lê um número real e armazena na posição correspondente da matriz.
        }
    }

    // Verifica se a operação é soma ('S').
    if (operacao == 'S')
    {
        // Percorre a matriz para somar os elementos abaixo da diagonal principal.
        for (i = 0; i < 12; i++)
        {
            for (j = 0; j < 12; j++)
            {
                if (i > j) // Verifica se o elemento está abaixo da diagonal principal.
                {
                    soma += m[i][j]; // Adiciona o elemento à soma.
                }
            }
        }
        // Imprime o resultado da soma com uma casa decimal.
        printf("%.1f\n", soma);
    }
    else // Se a operação não for 'S', verifica se é média ('M').
    {
        if (operacao == 'M')
        {
            // Percorre a matriz para calcular a média dos elementos abaixo da diagonal principal.
            for (i = 0; i < 12; i++)
            {
                for (j = 0; j < 12; j++)
                {
                    if (i > j) // Verifica se o elemento está abaixo da diagonal principal.
                    {
                        media += m[i][j]; // Adiciona o elemento à soma parcial para média.
                        cont++; // Incrementa o contador de elementos.
                    }
                }
            }
            // Calcula a média e imprime o resultado com uma casa decimal.
            printf("%.1f\n", media/cont);
        }
    }
}
