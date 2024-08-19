#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definiciones de constantes
#define true 1
#define false 0
#define MAXSIZE 40050
#define MAXSIZE_P 40000

// Estructura que representa una arista del grafo
typedef struct {
    int u, v, w; // Los dos vértices y el peso de la arista
} edge;

// Arreglo global para almacenar las aristas
edge g[MAXSIZE];
// Arreglo global para el conjunto de padres en el algoritmo de unión y búsqueda
int p[MAXSIZE_P];

// Prototipos de funciones
int compara(edge *, edge *);
int kruskal(int);
int componente(int);

int main(int argc, char **argv) {
    int m, n, i;

    // Leer los datos de entrada mientras m y n no sean cero
    while (scanf("%d %d", &m, &n), m && n) {
        // Inicializar las estructuras
        memset(g, 0, sizeof(g));
        memset(p, 0, sizeof(p));

        // Leer las aristas
        for (i = 0; i < n; ++i)
            scanf("%d %d %d", &g[i].v, &g[i].u, &g[i].w);

        // Ordenar las aristas por peso usando qsort y la función de comparación
        qsort(g, n, sizeof(edge), compara);

        // Inicializar el arreglo de padres
        for (i = 1; i <= m; ++i)
            p[i] = i;

        // Ejecutar el algoritmo de Kruskal y mostrar el resultado
        printf("%d\n", kruskal(n));
    }

    return 0;
}

// Función de comparación para qsort, compara los pesos de dos aristas
int compara(edge *a, edge *b) {
    return a->w - b->w;
}

// Función para encontrar el componente (raíz) de un vértice usando recursión
int componente(int __i) {
    if (__i == p[__i])
        return __i;
    return componente(p[__i]);
}

// Función que implementa el algoritmo de Kruskal para encontrar el MST
int kruskal(int __c) {
    int i, ans, v, u;

    ans = 0; // Inicializar el costo del MST

    // Iterar sobre todas las aristas
    for (i = 0; i < __c; ++i) {
        v = componente(g[i].v); // Encontrar el componente del vértice v
        u = componente(g[i].u); // Encontrar el componente del vértice u

        // Si v y u están en componentes diferentes, añadir la arista al MST
        if (v != u) {
            p[v] = p[u]; // Unir los componentes
            ans += g[i].w; // Añadir el peso de la arista al costo total
        }
    }

    return ans; // Retornar el costo total del MST
}
