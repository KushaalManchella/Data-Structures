#include <stdlib.h>
#include <stdio.h>


long long int _euclidean_dist(long long int x, long long int y, long long int p, long long int q);

long long int** _make_vertex_array(long long int num_vertices);

void _free_vertex_array(long long int** vertex_arr, long long int num_vertices);

long long int** _make_adjacency_matrix(long long int vertices);

void _free_adjacency_matrix(long long int** adj_matrix, long long int num_vertices);

void _print_matrix(long long int* array[], long long int num_rows, long long int num_cols);

void _fill_adj_matrix(long long int* adj_matrix[], long long int* vertex_arr[], FILE* fp, long long int num_vertices, long long int num_edges);

void _print_adj_list(long long int* adj_matrix[], long long int num_vertices);

long long int _minimum(long long int arr[], long long int visited[], long long int arr_size);

long long int* shortest_path(long long int* adj_matrix[], long long int num_vertices, long long int* distance, long long int* prev, long long int start_node, long long int stop);

void _trace_prev(long long int* prev,long long int start, long long int stop);

void _get_query(FILE* query, long long int num_vertices, long long int* distance, long long int* prev, long long int** adj_matrix);
