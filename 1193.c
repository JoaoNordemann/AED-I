#include <stdio.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0

// Função para reverter uma string
void strrev(char *);

// Função que converte um valor numérico em um caractere correspondente
char valueToChar(unsigned);

// Função que converte uma string numérica para um inteiro sem sinal
unsigned int StrToInt(char *);

// Função que converte um número em uma base qualquer para decimal
unsigned baseToDec(char *, int);

// Função que converte um número decimal para uma base qualquer
char * decimalToBase(unsigned, unsigned , char *);

int main (int argc, char **argv)
{
    int n, caso = 0;            // 'n' armazena o número de casos de teste e 'caso' é um contador para identificar os casos.
    char ans[1000];             // String para armazenar a resposta da conversão.
    char numero[1000], base[6]; // Strings para armazenar o número e a base em que ele está.

    // Lê o número de casos de teste
    scanf("%d", &n);

    // Loop através de todos os casos de teste
    while (n--)
    {
        // Lê o número e a base em que ele está
        scanf("%s%*c%s", numero, base);
        
        if (strcmp(base, "bin") == 0)
        {
            // Se a base for binário, converte para decimal e hexadecimal
            printf("Case %d:\n", ++caso);
            printf("%u dec\n", baseToDec(numero, 2)); // Converte de binário para decimal
            printf("%s hex\n\n", decimalToBase(baseToDec(numero, 2), 16, ans)); // Converte de decimal para hexadecimal
        }
        else if (strcmp(base, "dec") == 0)
        {
            // Se a base for decimal, converte para hexadecimal e binário
            printf("Case %d:\n", ++caso);
            printf("%s hex\n", decimalToBase(StrToInt(numero), 16, ans)); // Converte de decimal para hexadecimal
            printf("%s bin\n\n", decimalToBase(StrToInt(numero), 2, ans)); // Converte de decimal para binário
        }
        else
        {
            // Se a base for hexadecimal, converte para decimal e binário
            printf("Case %d:\n", ++caso);
            printf("%u dec\n", baseToDec(numero, 16)); // Converte de hexadecimal para decimal
            printf("%s bin\n\n", decimalToBase(baseToDec(numero, 16), 2, ans)); // Converte de decimal para binário
        }
    }
}

// Converte um número em uma base b para decimal
unsigned baseToDec(char *str, int base)
{
    int i;
    unsigned ans = 0;
    int power = 1;
    int len = strlen(str);

    // Converte cada dígito da string para o valor decimal correspondente
    for (i = len - 1; i >= 0; --i, power *= base)
        if (str[i] >= '0' && str[i] <= '9')
            ans += ((int)str[i] - '0') * power; // Para caracteres numéricos (0-9)
        else
            ans += ((int)str[i] - 'a' + 10) * power; // Para caracteres alfabéticos (a-f)

    return ans;
}

// Converte um número decimal para uma base b
char * decimalToBase(unsigned x, unsigned base, char *dest)
{
    unsigned idx = 0;

    // Realiza a conversão para a base desejada
    while (x > 0)
        dest[idx++] = valueToChar(x % base), x /= base; // Armazena o dígito correspondente na base

    dest[idx] = '\0';
    strrev(dest); // Reverte a string para que os dígitos fiquem na ordem correta
    return dest;
}

// Função auxiliar que converte um valor numérico em um caractere correspondente
char valueToChar(unsigned a)
{
    if (a >= 0 && a <= 9)
        return (char)(a + '0'); // Converte números 0-9 para caracteres '0'-'9'
    else
        return (char)(a - 10 + 'a'); // Converte números 10-15 para caracteres 'a'-'f'
}

// Reverte uma string
void strrev(char *str)
{
    unsigned i;
    unsigned len = strlen(str);
    unsigned max = len / 2;

    // Troca os caracteres para reverter a string
    for (i = 0; i < max; ++i)
    {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

// Converte uma string numérica para um inteiro
unsigned StrToInt(char *str)
{
    int tamanho;
    unsigned ret, multiplicador;

    // Realiza a conversão de string para inteiro
    for(tamanho = strlen(str) - 1, multiplicador = 1, ret = 0; tamanho >= 0; tamanho--, multiplicador *= 10)
        ret +=  (str[tamanho] - 48) * multiplicador; // Converte cada caractere para o valor correspondente

    return ret;
}
