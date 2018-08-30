#include<stdio.h>
#include<stdlib.h>
#include"shortestpath.h"


int main(int argc, char* argv[])
{

  if(argc != 3)
  {
    printf("ERROR!\nEnter the right number of arguments!");
    return 0;
  }

  FILE* input = fopen(argv[1],"r");
  FILE* query = fopen(argv[2],"r");

  int num_vertices;
  int num_edges;


  fscanf(input, "%d%d", &num_vertices, &num_edges);

  // initializing adjacency list

  list* adjacency_list = _initialize_adjacency_list(num_vertices);

  // Initializing Vertex array

  vertex* vertex_arr = _initialize_vertices(input, num_vertices);





  query += 0;




}
