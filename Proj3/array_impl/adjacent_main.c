#include<stdio.h>
#include<stdlib.h>
#include"dijkstra.h"


int main(int argc, char* argv[])
{

  if(argc != 2){
    printf("ERROR!\nEnter the right number of arguments!");
    return 0 ;
  }

  FILE* input = fopen(argv[1],"r");

  long long int num_vertices;
  long long int num_edges;

  fscanf(input, "%lld%lld", &num_vertices, &num_edges);

//  printf(" num_vertices, num_edges = %lld %lld \n", num_vertices, num_edges);

  long long int** adj_matrix = _make_adjacency_matrix(num_vertices);

  long long int** vertex_arr = _make_vertex_array(num_vertices);



  _fill_adj_matrix(adj_matrix, vertex_arr, input, num_vertices, num_edges);


  _print_adj_list(adj_matrix, num_vertices);

  _free_vertex_array(vertex_arr, num_vertices);
  _free_adjacency_matrix(adj_matrix, num_vertices);
}
