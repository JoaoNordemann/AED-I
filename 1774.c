#include <stdio.h>
#include <stdlib.h>

// Definiciones de constantes
#define true 1
#define false 0

// Estructura que representa una arista del grafo
typedef struct {
    int v, u, w; // Dos vértices y el peso de la arista
} edge;

// Arreglos globales para almacenar las aristas y el conjunto de padres
edge g[250];
int p[70];

// Prototipos de funciones
int compara(edge *, edge *);
int componente(int);
int kruskal(int);

int main(int argc, char **argv) {
    int r, c, i;

    // Leer el número de vértices (r) y el número de aristas (c)
    scanf("%d %d", &r, &c);

    // Leer todas las aristas del grafo
    for (i = 0; i < c; ++i) {
        scanf("%d %d %d", &g[i].v, &g[i].u, &g[i].w);
    }

    // Ordenar las aristas por peso usando qsort y la función de comparación
    qsort(g, c, sizeof(edge), compara);

    // Inicializar el arreglo de padres para cada vértice
    for (i = 1; i <= r; ++i) {
        p[i] = i;
    }

    // Ejecutar el algoritmo de Kruskal y mostrar el costo del MST
    printf("%d\n", kruskal(c));

    return 0;
}

// Función de comparación para qsort, compara los pesos de dos aristas
int compara(edge *a, edge *b) {
    return a->w - b->w;
}

// Función para encontrar el componente (raíz) de un vértice usando recursión
int componente(int __i) {
    if (__i == p[__i]) {
        return __i;
    }
    return componente(p[__i]);
}

// Función que implementa el algoritmo de Kruskal para encontrar el MST
int kruskal(int __c) {
    int i, ans, v, u;

    ans = 0; // Inicializar el costo del MST

    // Iterar sobre todas las aristas ordenadas por peso
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
