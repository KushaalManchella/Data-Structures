#include<stdio.h>
#include<stdlib.h>


typedef struct _Vertex{
  int x;
  int y;
  int distance;
  int vertex_ind;
  int prev_node;
  int visited;
}vertex;

typedef struct _List_Node{
  struct list_node* next;
  int weight;
  int index;
}list_node;

typedef struct _List{
  struct list_node* head;
}list;


list* _initialize_adjacency_list(int num_vertices);
vertex* _initialize_vertices(FILE* input, int num_vertices);
int _euclidean_dist(int x, int y, int p, int q);
list_node* _create_list_node(int index, int weight);
