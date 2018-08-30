#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include"dijkstra.h"

long long int _euclidean_dist(long long int x, long long int y, long long int p, long long int q)
{
  long long int euclidean = sqrt(pow(p-x,2)+ pow(q-y,2));

  return euclidean;
}

long long int** _make_vertex_array(long long int num_vertices)
{
  long long int** vertex_arr = malloc(sizeof(long long int*) * num_vertices);
	long long int each_row = 0;

	for (each_row = 0; each_row < num_vertices; each_row++)
	{
			vertex_arr[each_row] = malloc(sizeof(long long int) * (4));
			long long int each_col;

			for(each_col = 0; each_col < 4; each_col++)
			{
					vertex_arr[each_row][each_col] = -1;
			}
	}

  return vertex_arr;
}

void _free_vertex_array(long long int** vertex_arr, long long int num_vertices)
{
  long long int each_row = 0;

  for(each_row = 0; each_row < num_vertices; each_row++)
  {
    free(vertex_arr[each_row]);
  }
  free(vertex_arr);

}



long long int** _make_adjacency_matrix(long long int vertices)
{
  long long int** adj_matrix= malloc(sizeof(long long int*) * vertices);

  for (int vertex = 0; vertex < vertices; vertex++) {
      adj_matrix[vertex] = malloc(sizeof(long long int) * vertices);

      for(int each_col = 0; each_col < vertices; each_col++)
      {
        adj_matrix[vertex][each_col] = 0;
      }
    }

    return adj_matrix;
}

void _free_adjacency_matrix(long long int** adj_matrix, long long int num_vertices)
{


  for(int each_row = 0; each_row < num_vertices; each_row++)
  {
    free(adj_matrix[each_row]);
  }
  free(adj_matrix);
}

void _print_matrix(long long int* array[], long long int num_rows, long long int num_cols)
{

    long long int rows = 0;
    long long int cols = 0;
    while( rows < num_rows )
    {
        cols = 0;
        while(cols < (num_cols))
        {
            printf(" %lld ", array[rows][cols]);
            cols++;
        }
        printf("\n");
        rows++;
;
    }
}

void _fill_adj_matrix(long long int* adj_matrix[], long long int* vertex_arr[], FILE* fp, long long int num_vertices, long long int num_edges)
{

    long long int count = 0;
    long long int vert_1 = 0;
    long long int vert_2 = 0;
    long long int row = 0;
    long long int col = 0;


    while(count < num_vertices)
    {
      fscanf(fp, "%lld", &vertex_arr[row][col]);
      col++;
      fscanf(fp, "%lld", &vertex_arr[row][col]);
      col++;
      fscanf(fp, "%lld", &vertex_arr[row][col]);
      row++;
      col = 0;
      count++;
    }

    long long int scans = 0;

    while(scans <= num_edges)
    {
      fscanf(fp, "%lld", &vert_1);
      fscanf(fp, "%lld", &vert_2);
//      printf("vert_1 = %lld ", vert_1);
//      printf("vert_2 = %lld\n", vert_2);
      adj_matrix[vert_1][vert_2] = _euclidean_dist(vertex_arr[vert_1][1], vertex_arr[vert_1][2], vertex_arr[vert_2][1], vertex_arr[vert_2][2]);
      adj_matrix[vert_2][vert_1] = adj_matrix[vert_1][vert_2];
      scans++;
    }
}


void _print_adj_list(long long int* adj_matrix[], long long int num_vertices)
{
  long long int rows = 0;
  long long int cols = 0;

  while( rows < num_vertices )
  {
      cols = 0;
      printf("%lld: ", rows);
      while(cols < num_vertices)
      {
          if( adj_matrix[rows][cols] != 0)
          {
            printf("%lld ", cols);
          }
          cols++;
      }
      printf("\n");
      rows++;
  }
}

long long int _minimum(long long int arr[], long long int visited[], long long int arr_size)
{
  int ind = 0;
  int min = INT_MAX;

  while(ind < arr_size)
  {
    if(arr[ind] < min && !visited[ind])
    {
      min = ind;
    }
    ind++;
  }

  return min;
}

long long int* shortest_path(long long int* adj_matrix[], long long int num_vertices, long long int* distance, long long int* prev, long long int start_node, long long int stop)
{

  long long int *visited = (long long int*)malloc(sizeof(long long int)* num_vertices);

  for (long long int i = 0; i < num_vertices; i++) {
    visited[i] = 0;
    distance[i] = 0;
    prev[i] = -1;
  }


  long long int min_node = 0;

  // initialize distance

  for (long long int i = 0; i < num_vertices; i++)
  {
    distance[i] = INT_MAX;
  }


  distance[start_node] = 0;
  //visited[start_node] = 1;
  int iteration = 0;

  while(iteration < num_vertices)
  {
    min_node = _minimum(distance, visited, num_vertices);
//    printf("min_node = %lld\n", min_node);
    for (long long int i = 0; i < num_vertices; i++)
    {
      if((adj_matrix[min_node][i] != 0) && !visited[min_node] && (distance[min_node] + adj_matrix[min_node][i] < distance[i]))
      {
        distance[i] = distance[min_node] + adj_matrix[min_node][i];
        prev[i] = min_node;
      }
    }
    visited[min_node] = 1;
    iteration++;
  }


  printf("%lld\n", distance[stop]);
  free(visited);

  return distance;

}

void _trace_prev(long long int* prev,long long int start, long long int stop)
{
  long long int count = 0;
  long long int i = stop;
  while(prev[i] != start)
  {
    i = prev[i];
    count++;
  }
  i = stop;
  long long int temp = count;

  long long int* path = malloc(sizeof(path)* (count+2));
  count++;
  path[count] = stop;



  while(prev[i] != start)
  {
    path[--count] = prev[i];
    i = prev[i];
  }

  path[0] = start;
  for (i = 0; i < (temp+2); i++) {
    printf("%lld ",path[i]);
  }

  printf("\n");
  free(path);
}


void _get_query(FILE* query, long long int num_vertices, long long int* distance, long long int* prev, long long int** adj_matrix)
{
  long long int start;
  long long int stop;
  long long int num_queries;

  fscanf(query, "%lld", &num_queries);

  for (long long int i = 0; i < num_queries; i++)
  {
    fscanf(query, "%lld%lld", &start, &stop);
    shortest_path(adj_matrix, num_vertices, distance, prev, start, stop);
    _trace_prev(prev, start, stop);
  }
}
