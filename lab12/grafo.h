#ifndef GRAFO_H
#define GRAFO_H

#include "lista.h"

typedef struct Graph
{
   int n;
   p_node *adjacency;
} Graph;

typedef Graph * p_graph;

/**
 * Initialize the graph with num_vert vertices
 */
p_graph initialize_graph(int num_vert);

/**
 * Create edge from vertA to vertB
 */
void insert_edge(p_graph graph, int vertA, int vertB, int weight);

/**
 * Create edge both from vertA to vertB and from vertB to vertA
 */
void insert_bidirect_edge(p_graph graph, int vertA, int vertB, int weight);

/**
 * Get the weight of the edge between vertA and vertB
 */
int get_edge_weight(p_graph graph, int vertA, int vertB);

/**
 * Dijkstra algorithm starting from vertex start
 * Returns an array of the parent for each vertex.
 */
int * dijkstra(p_graph graph, int start);

/**
 * Remove every edge that weights more than a given threshold
 */
void remove_bigger_edges(p_graph graph, int threshold);

/**
 * Destroy the graph
 */
void destroy_graph(p_graph graph);

#endif // GRAFO_H
