#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LOG 18  // Define o número máximo de níveis para a tabela de ancestrais.
#define MAXSIZE 100005  // Define o tamanho máximo do grafo.
#define INF 0x3f3f3f3fLLU  // Define um valor de "infinito" como um número muito grande.

typedef long long ll;  // Define `ll` como um alias para `long long`, para manipulação de números grandes.

typedef struct _node {
    int u, w;  // `u` é o vértice conectado, `w` é o peso da aresta.
    struct _node *next;  // Ponteiro para o próximo nó na lista de adjacências.
} node_t;

typedef struct _g {
    node_t *adj;  // Ponteiro para o array de listas de adjacências.
} g_t;

int n;  // Número de vértices na árvore.

ll dist[MAXSIZE];  // Array que armazena as distâncias da raiz para cada nó.
int depth[MAXSIZE];  // Array que armazena a profundidade (nível) de cada nó na árvore.
int parent[MAXSIZE][LOG];  // Tabela de ancestrais binários (Sparse Table).

// Funções para criar o grafo, nós e para manipulação.
g_t * make_graph(int __size);
node_t * make_node(int u, int w);
void push_in(g_t *g, int u, int v, int w);

// Funções principais do algoritmo.
void pst();  // Preenche a tabela de ancestrais binários.
void dfs(int s, g_t *g);  // Realiza uma busca em profundidade (DFS) na árvore.
int LCA(int u, int v);  // Encontra a menor ancestral comum entre `u` e `v`.
void swap(int *a, int *b);  // Troca os valores de dois inteiros.

int main(int argc, char **argv) {
    int u, v, w, q;

    // Loop para processar múltiplos casos de teste até que n seja zero.
    while (scanf("%d%*c", &n), n) {

        g_t *g = make_graph(n + 1);  // Cria um grafo com n+1 vértices.

        // Lê as arestas da árvore.
        for (int u = 1; u < n; ++u) {
            scanf("%d %d", &v, &w);
            if (u < v)
                push_in(g, v, u, w);  // Adiciona aresta de `v` para `u`.
            else
                push_in(g, u, v, w);  // Adiciona aresta de `u` para `v`.
        }

        // Inicializa as distâncias e profundidades como infinito.
        for (int i = 0; i <= n; ++i)
            dist[i] = depth[i] = INF;

        parent[0][0] = 0;  // Define a raiz como seu próprio ancestral.
        depth[0] = dist[0] = 0;  // A raiz tem profundidade e distância zero.

        dfs(0, g);  // Executa DFS a partir da raiz para preencher distâncias e profundidades.
        pst();  // Preenche a tabela de ancestrais.

        scanf("%d", &q);  // Lê o número de consultas.

        while (q--) {
            scanf("%d %d", &u, &v);  // Lê os dois vértices `u` e `v`.

            int lca = LCA(u, v);  // Encontra a menor ancestral comum entre `u` e `v`.
            ll ans = (dist[u] - dist[lca]) + (dist[v] - dist[lca]);  // Calcula a distância entre `u` e `v` passando pela LCA.
            printf("%lld%c", ans, q > 0 ? ' ' : '\n');  // Imprime a resposta, separando por espaço se não for a última consulta.
        }

    }

    return 0;
}

// Função que realiza DFS para calcular profundidades e distâncias.
void dfs(int s, g_t *g) {
    for (node_t *i = g->adj[s].next; i != NULL; i = i->next) {
        int v = i->u;
        int w = i->w;

        if (depth[v] == INF) {  // Se o vértice `v` não foi visitado ainda.
            depth[v] = depth[s] + 1;  // Define a profundidade de `v`.
            dist[v] = dist[s] + (ll)w;  // Calcula a distância acumulada até `v`.
            parent[v][0] = s;  // Define `s` como o ancestral imediato de `v`.
            dfs(v, g);  // Chama DFS recursivamente para `v`.
        }
    }
}

// Função que preenche a tabela de ancestrais binários.
void pst() {
    for (int i = 1; i < LOG; ++i)
        for (int u = 0; u < n; ++u)
            if (parent[u][i - 1] != -1)
                parent[u][i] = parent[parent[u][i - 1]][i - 1];  // Define o ancestral de `u` no nível `i`.
}

// Função que encontra a menor ancestral comum (LCA) entre `u` e `v`.
int LCA(int u, int v) {
    if (depth[u] > depth[v])
        swap(&u, &v);  // Garante que `u` está no nível mais profundo.

    int diff = depth[v] - depth[u];  // Calcula a diferença de profundidade.

    for (int i = 0; i < LOG; ++i)
        if ((diff >> i) & 1)
            v = parent[v][i];  // Sobe `v` até que esteja no mesmo nível de `u`.

    if (u == v)
        return u;  // Se `u` e `v` já são o mesmo nó, esse é o LCA.

    for (int i = LOG - 1; i >= 0; --i)
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];  // Sobe ambos `u` e `v` ao mesmo tempo até encontrar o LCA.
        }

    return parent[u][0];  // O ancestral comum mais baixo de `u` e `v` é o LCA.
}

// Função para criar o grafo.
g_t * make_graph(int __size) {
    g_t *g = (g_t *) malloc(sizeof(g_t));
    g->adj = (node_t *) malloc(sizeof(node_t) * (__size + 1));

    for (int i = 0; i <= __size; ++i)
        g->adj[i].next = NULL;  // Inicializa a lista de adjacência de cada vértice como vazia.

    return g;
}

// Função para criar um nó de lista de adjacência.
node_t * make_node(int u, int w) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->u = u;
    new_node->w = w;
    new_node->next = NULL;  // Inicializa o próximo nó como NULL.

    return new_node;
}

// Função para adicionar uma aresta na lista de adjacência.
void push_in(g_t *g, int u, int v, int w) {
    node_t *new_node = make_node(u, w);
    new_node->next = g->adj[v].next;  // Insere o novo nó no início da lista de adjacência de `v`.
    g->adj[v].next = new_node;
}

// Função para trocar os valores de `a` e `b`.
inline void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
