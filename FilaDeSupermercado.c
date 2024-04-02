#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
  int i, n, m;

  // Lê o tamanho do vetor 'a'
  scanf("%d", &n);
  int a[n];

  // Lê o tamanho do vetor 'b'
  scanf("%d", &m);
  int b[m];

  // Lê os elementos do vetor 'a'
  for(i = 0; i < n; i++)
    scanf("%d", &a[i]);

  // Lê os elementos do vetor 'b'
  for(i = 0; i < m; i++)
    scanf("%d", &b[i]);

  // Vetor temporário para armazenar os resultados das multiplicações
  int temp[n];
  int t =0;
  while(t < m) 
  {
    if(t < n)
    {
      temp[t] = b[t] * a[t];

      t++;
    }
    else
    {
      // Caso 'm' seja maior que 'n', ajusta os valores de 'temp' para considerar os elementos excedentes de 'b'
      int index = temp[0];
      int z = 0;
      for(i = 0; i < n; i++)
        if(index > temp[i])
        {
          index = temp[i];
          z = i;
        }
      temp[z] += b[t] * a[z];

      z = 0;
      t++;
    }
  }

  // Encontra o maior valor do vetor 'temp' e imprime
  int index = temp[0];

  for(i = 0; i < n; i++)
    if(index < temp[i])
      index = temp[i];
  printf("%d\n", index);
}