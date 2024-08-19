#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Define uma estrutura para armazenar informações sobre os alunos
typedef struct {
	char nome[200];          // Nome do aluno
	short presenca;          // Contador de presenças
	short ausencia;          // Contador de ausências
	short atestado;          // Contador de justificativas (atestado médico)
	float taxaPresenca;      // Taxa de presença (presença / total de aulas)

} classe;

void main ()
{
	unsigned short qtsAlunos, casos;        // Quantidade de alunos e quantidade de casos de teste
	unsigned short qtsTotalFrequencia;      // Total de frequências (presenças + ausências) (não usado no código)
	unsigned short i, aux, j;               // Variáveis de controle de loop
	char registro[5000];                    // String para armazenar os registros de presença (P, A, M)

	// Lê o número de casos de teste
	scanf("%hu", &casos);

	// Loop para processar cada caso de teste
	while (casos--)
	{
		// Lê o número de alunos para o caso atual
		scanf("%hu", &qtsAlunos);

		classe alunos[qtsAlunos];            // Declaração do array de alunos
		memset(alunos, 0, sizeof(alunos));   // Inicializa todos os valores dos alunos como 0

		// Lê os nomes dos alunos
		for (i = 0; i < qtsAlunos; i++)
			scanf(" %s", alunos[i].nome);

		aux = qtsAlunos;                     // Auxiliar para controlar o número de alunos a serem processados
		i = 0;                               // Reseta o índice dos alunos
		bool primSpaco = false;              // Flag para controlar a impressão de espaço entre nomes

		// Processa os registros de presença para cada aluno
		while (aux--)
		{
			// Lê o registro de presença (P = Presente, A = Ausente, M = Atestado)
			scanf(" %s", registro);

			// Itera sobre cada caractere do registro
			for (j = 0; registro[j]; j++)
			{
				if (registro[j] == 'P')
					alunos[i].presenca++;    // Incrementa o contador de presenças
				else if (registro[j] == 'A')
					alunos[i].ausencia++;    // Incrementa o contador de ausências
				else if (registro[j] == 'M')
					alunos[i].atestado++;    // Incrementa o contador de atestados (não usado no cálculo da taxa)
			}

			// Zera o registro para a próxima iteração
			memset(registro, 0, sizeof(registro));

			// Calcula a taxa de presença do aluno
			alunos[i].taxaPresenca = (1.0f * alunos[i].presenca) / (alunos[i].presenca + alunos[i].ausencia);

			// Verifica se a taxa de presença é menor que 75%
			if (alunos[i].taxaPresenca < 0.75f)
			{
				if (primSpaco)
					printf(" "); // Adiciona um espaço entre nomes, se necessário

				printf("%s", alunos[i].nome); // Imprime o nome do aluno com baixa presença

				primSpaco = true; // Define que o próximo nome deve ser precedido por um espaço
			}

			i++; // Passa para o próximo aluno
		}

		printf("\n"); // Imprime uma nova linha após listar todos os alunos com baixa presença
	}
}
