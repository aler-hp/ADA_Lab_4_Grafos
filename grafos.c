#include <stdio.h>
#include <stdlib.h>

#define vertex int

typedef struct graph *Graph;

typedef struct node *link;

struct graph {
    int V;
    int A;
    link *adj;
};

struct node {
    vertex w;  //value
    link next;
};

static link NEWnode( vertex w, link next) {
    link a = (link) malloc( sizeof (struct node));
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit( int V) {
    Graph G = (Graph) malloc( sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = (link *) malloc( V * sizeof (link));
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc( Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
        G->adj[v] = NEWnode( w, G->adj[v]);
        G->A++;
}

int GRAPHoutdeg(Graph G, vertex v) {
  int count = 0;
  for (link a = G->adj[v]; a != NULL; a = a->next)
      count++;
  return count;
}

int GRAPHindeg(Graph G, vertex v) {
  int count = 0;
  for (vertex u = 0; u < G->V; u++) {
      for (link a = G->adj[u]; a != NULL; a = a->next) {
          if (a->w == v)
              count++;
      }
  }
  return count;
}

void GRAPHshow(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        printf("Vertice %d :", v);
        for (link a = G->adj[v]; a != NULL; a = a->next)
            printf("%d--", a->w);
        printf("\n");
    }
}

void GRAPHdestroy(Graph G) {
    if (G == NULL) return;

    // Liberar cada lista de adyacencia
    for (vertex v = 0; v < G->V; v++) {
        link a = G->adj[v];
        while (a != NULL) {
            link next = a->next;
            free(a);
            a = next;
        }
    }

    // Liberar el vector de listas
    free(G->adj);

    // Liberar la estructura del grafo
    free(G);
}
void GRAPHremoveArc(Graph G, int v, int w) {
    if (!G) return;
    if (v < 0) return;

    link curr = G->adj[v];
    link prev = NULL;

    while (curr != NULL) {
        if (curr->w == w) {
            if (prev == NULL) {
                G->adj[v] = curr->next; //actualiza cabeza
            } else {
                prev->next = curr->next;
            }
            free(curr);
            G->A--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int search(Graph G, vertex v, vertex w) { //verifica dentro de cada vertice
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        if (a->w == w)
            return 1;
    }
    return 0;
}

int GRAPHundir(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            vertex w = a->w;
            if (!search(G, w, v))
                return 0; // No es no dirigido
        }
    }
    return 1; //Si es no dirigido
}
void UGRAPHinsertEdge(Graph G, vertex v, vertex w) {
    // Evitar bucles y aristas duplicadas
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;

    // Insertar arista en ambos sentidos
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->adj[w] = NEWnode(v, G->adj[w]);
    G->A++;
}

int UGRAPHdegrees(Graph G) { //grado maximo
    int maxDegree = 0;

    for (vertex v = 0; v < G->V; v++) {
        int degree = 0;
        for (link a = G->adj[v]; a != NULL; a = a->next) //contar adyacentes
            degree++;

        if (degree > maxDegree)
            maxDegree = degree; 
    }

    return maxDegree;
}


int main(void) {
    Graph G = GRAPHinit(5); 

    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 3);
    GRAPHinsertArc(G, 1, 4);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 3, 4);
    GRAPHinsertArc(G, 4, 0);

    GRAPHremoveArc(G, 3, 4);

    GRAPHshow(G);

    printf("\nLiberando memoria del grafo...\n");
    GRAPHdestroy(G);
    printf("Memoria liberada correctamente.\n");

    return 0;
}
