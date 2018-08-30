#include<stdio.h>
#include<stdlib.h>
#include"dijkstra.h"


int main(int argc, char* argv[])
{

  if(argc != 3)
  {
    printf("ERROR!\nEnter the right number of arguments!");
    return 0;
  }

  FILE* input = fopen(argv[1],"r");
  FILE* query = fopen(argv[2],"r");

  long long int num_vertices;
  long long int num_edges;


  fscanf(input, "%lld%lld", &num_vertices, &num_edges);

//  printf(" num_vertices, num_edges = %lld %lld \n", num_vertices, num_edges);

  long long int** adj_matrix = _make_adjacency_matrix(num_vertices);

  long long int** vertex_arr = _make_vertex_array(num_vertices);



  _fill_adj_matrix(adj_matrix, vertex_arr, input, num_vertices, num_edges);
//  _print_matrix(adj_matrix, num_vertices, num_vertices);

//  _print_matrix(vertex_arr, num_vertices, 3);

//  _print_adj_list(adj_matrix, num_vertices);

 long long int* distance = (long long int*)malloc(sizeof(long long int)* num_vertices);
 long long int* prev = (long long int*)malloc(sizeof(long long int)* num_vertices);


  _get_query(query, num_vertices, prev, distance, adj_matrix);

  _free_vertex_array(vertex_arr, num_vertices);
  _free_adjacency_matrix(adj_matrix, num_vertices);


  free(distance);
  free(prev);
  fclose(input);
  fclose(query);
}
