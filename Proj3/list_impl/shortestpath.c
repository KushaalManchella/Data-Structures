#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include"shortestpath.h"


list* _initialize_adjacency_list(int num_vertices){
  list* adjacency_list = malloc(num_vertices* sizeof(list));

  for (int i = 0; i < num_vertices; i++)
  {
    adjacency_list[i].head = NULL;
  }
  return adjacency_list;
}

vertex* _initialize_vertices(FILE* input, int num_vertices){
  vertex* vertex_arr = malloc(sizeof(vertex) * num_vertices);
  int index = 0;

  for (int i = 0; i < num_vertices; i++)
  {
    fscanf(input, "%d", &index);
    fscanf(input, "%d", &vertex_arr[i].x);
    fscanf(input, "%d", &vertex_arr[i].y);
    vertex_arr[i].distance = INT_MAX;
    vertex_arr[i].vertex_ind = i;
    vertex_arr[i].prev_node = -1;
    vertex_arr[i].visited = -1;
  }

  return vertex_arr;
}

int _euclidean_dist(int x, int y, int p, int q)
{
  int euclidean = sqrt(pow(p-x,2)+ pow(q-y,2));

  return euclidean;
}

list_node* create_list_node(int index, int weight)
{
  list_node* node = malloc(sizeof(list_node));
  node->next  = NULL;
  node->index = index;
  node->weight = weight;
  return node;
}


list* _fill_adjacency_list(FILE* input, list* adjacency_list, vertex* vertex_arr, int num_edges)
{
  int euclidean;
  int ind1;
  int ind2;
  for (int i = 0; i < num_edges; i++)
  {
      fscanf(input, "%d%d", &ind1, &ind2);
      euclidean = _euclidean_dist(vertex_arr[ind1].x,vertex_arr[ind1].y,vertex_arr[ind2].x,vertex_arr[ind2].y);

      list_node* new_node = _create_list_node(ind1, euclidean);
      new_node -> next = NULL;
      adjacency_list -> head = new_node;

      new_node = _create_list_node(ind2, euclidean);
      new_node -> next = NULL;
      adjacency_list -> head = (list_node)new_node;
  }

  return adjacency_list;
}
