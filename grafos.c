#include <stdio.h>

#define vertex int

/* REPRESENTACIÓN POR LISTAS DE ADYACENCIA: La estructura graph representa un
grafo. El campo adj es un puntero al vector de listas de adyacencia, el campo V
contiene el número de vértices y el campo A contiene el número de arcos del grafo.
*/
struct graph {
    int V;
    int A;
    link *adj;
};
/* Un Graph es un puntero para un graph. */
typedef struct graph *Graph;
/* La lista de adyacencia de un vértice v está formada por nodos de tipo nodo. Cada
nodo de la lista corresponde a un arco y contiene un vecino w de v y la dirección
del siguiente nodo de la lista. Un link es un puntero a un nodo. */
typedef struct node *link;
struct node {
    vertex w;  //value
    link next;
};
/* La función NEWnode() recibe un vértice w y la dirección next de un nodo y
devuelve la dirección a de un nuevo nodo tal que a->w == w y a->next == next. */
static link NEWnode( vertex w, link next) {
    link a = malloc( sizeof (struct node));
    a->w = w;
    a->next = next;
    return a;
}

/* REPRESENTACIÓN POR LISTAS DE ADYACENCIA: La función GRAPHinit() construye un grafo con
vértices 0 1 .. V-1 y ningún arco. */
Graph GRAPHinit( int V) {
    Graph G = malloc( sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc( V * sizeof (link));
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}
/* REPRESENTACIÓN POR LISTAS DE ADYACENCIA: La función GRAPHinsertArc() inserta un arco v-w
en el grafo G. La función asume que v y w son distintos, positivos y menores que G->V. Si el
grafo ya tiene un arco v-w, la función no hace nada. */
void GRAPHinsertArc( Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
        G->adj[v] = NEWnode( w, G->adj[v]);
        G->A++;
}