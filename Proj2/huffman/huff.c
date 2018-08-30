#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


/*
void _print_queue(Node* temp)
{

	while(temp -> next != NULL)
	{
		printf("%c:%d", (char) temp -> ptr -> ASCII, temp -> ptr -> freq);
		printf("->");					temp = temp -> next;
	}

		printf("%c:%d", (char) temp -> ptr -> ASCII, temp -> ptr -> freq);
		printf("->");
		printf("NULL\n");
}
*/

char* _make_ASCII_count(char* ASCII_count, FILE* fp)
{
	fseek(fp, 0, SEEK_SET);

	int ch = 0;

	while(ch != EOF)
	{
		ch = fgetc(fp);
		ASCII_count[ch]++;
	}
	return ASCII_count;
}



unsigned int _get_num_chars(char* Filename)
{
	FILE* fp = fopen(Filename,"r");
	fseek(fp, 0, SEEK_SET);

	unsigned int num_chars = 0;
	int ch = 0;

	while((ch = fgetc(fp) != EOF))
	{
	//	printf("ch = %c ", ch );
		num_chars++;
	}

	fclose(fp);
	return num_chars;
}


int _cmp_fn2(TreeNode* p1, TreeNode * p2){
	if((p1 -> freq) < (p2 -> freq))
	{
		return -1;
	}
	else if((p1 -> freq) > (p2 -> freq))
	{
		return 1;
	}
	else if(p1 -> freq == p2 -> freq)
	{
		if(p1 -> left == NULL && p2 -> right != NULL)
		{
			return -1;
		}
		else if(p1 -> left != NULL && p2 -> right == NULL)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}



int _cmp_fn(TreeNode *p1, TreeNode *p2){
	if((p1 -> freq) < (p2 -> freq))
	{
		return -1;
	}
	else if((p1 -> freq) > (p2 -> freq))
	{
		return 1;
	}
	else
	{
		return (p1 -> ASCII) - (p2 -> ASCII);
	}
}

Node *pq_enqueue(Node **pq, TreeNode *new_object, int (*cmp_fn)(TreeNode *,TreeNode *)){
	if( new_object == NULL){
		return NULL;
	}
	Node* head = malloc(sizeof(*head));

	if(head == NULL){
		return NULL;
	}

	head -> ptr = (TreeNode*)new_object;
	head -> next = NULL;

	Node* temp = *pq;
	Node* curr = NULL;

	while(temp !=  NULL && cmp_fn(temp -> ptr, new_object) < 0){
		curr = temp;
		temp = temp -> next;
	}

	if(temp == *pq){
		head -> next = *pq;
		*pq = head;
		return head;
	}
	curr -> next = head;
	head -> next = temp;

	return head;
}



Node *pq_dequeue(Node **pq)
{
	if(*pq == NULL)
	{
		return NULL;
	}
	Node* head = *pq;

	Node* curr = head -> next;
	head -> next = NULL;
	*pq = curr;

	return head;
}

Node* _make_queue(Node* head, char* ASCII_count)
{

	for(int i =0 ; i <256; i++)
	{
		if(ASCII_count[i] != 0)
		{
			TreeNode* curr = malloc(sizeof(*curr));
			curr -> freq = ASCII_count[i];
			curr -> ASCII = i;
			curr -> left = NULL;
			curr -> right = NULL;

			pq_enqueue(&head, curr, _cmp_fn);
		}
	}
	return head;
}

Node* _build_tree_from_queue(Node* head){
	int count_branch = 0;

	while(head -> next != NULL)
	{
		Node* left_most  = pq_dequeue(&head);
		Node* next_lm = pq_dequeue(&head);

		TreeNode* parent = malloc(sizeof(*parent));
		parent -> freq = left_most -> ptr -> freq + next_lm -> ptr -> freq;
		parent -> left = left_most -> ptr;
		parent -> right = next_lm -> ptr;

		free(left_most);
		free(next_lm);

		pq_enqueue(&head, parent, _cmp_fn2);
		count_branch++;
	}
	return head;
}

int* _make_path(int* path)
{
	for(int i = 0; i < 9; i++)
	{
		path[i] = -1;
	}

	return path;
}

void _recurse(TreeNode* curr,FILE* fp, int* path, int count)
{
	if(curr -> right == NULL)
	{
		fprintf(fp, "%c:", (char)curr -> ASCII);
		for(int i = 0; i < count; i++)
		{
			fprintf(fp, "%d", path[i]);
		}
		fprintf(fp, "\n");
	}
	else
	{
		path[count] = 0;
		_recurse( curr -> left, fp, path, count+1);
		path[count] = 1;
		_recurse( curr -> right, fp, path, count+1);
	}
}


void _destroy_node(Node* head){

	if(head == NULL)
	{
		return;
	}

	Node* curr = head;

	while(head != NULL)
	{
		curr = head -> next;
		free(head);
		head = curr;
	}
}

void _destroy_tree(TreeNode* tree){
    if(tree == NULL)
    {
        return;
    }
    _destroy_tree(tree-> left);
    _destroy_tree(tree-> right);
    free(tree);
}

void _codebook_dims(char* Filename, int* rows, int* cols){
    FILE* fp = fopen(Filename,"r");

    int ch = 0;
    int temp_cols = 0;
	int temp_rows = 0;
    *rows = 0;
    *cols = 0;
    int path = 1;


    fseek(fp, 0, SEEK_SET);

    while(ch != EOF)
    {
        if(ch == '\n')
        {
            temp_rows++;
            path = 0;
            temp_cols = 0;
        }
        if(ch == ':'){
            path = 1;
        }
        if(path == 1){
            temp_cols++;
        }
        if( temp_cols > *cols )
        {
            *cols = temp_cols;
        }

        ch = fgetc(fp);
    }
	*rows = temp_rows;

    fclose(fp);

    return;
}

int** _create_codebook(int* rows, int* cols)
{
	int** codebook = malloc(sizeof(int*) * *rows);
	int each_row = 0;

	for (each_row = 0; each_row < *rows; each_row++)
	{
			codebook[each_row]= malloc(sizeof(int) * (*cols+1));
			int each_col;

			for(each_col = 0; each_col < *cols+1; each_col++)
			{
					codebook[each_row][each_col] = -1;
			}
	}
	return codebook;
}

void _fill_codebook(char* Filename, int* array[]){

    FILE* fp = fopen(Filename,"r");
		if(fp == NULL)
		{
			return;
		}

    fseek(fp, 0, SEEK_SET);


    int ch = 0;
    int rows = 0;
    int cols = 0;
    int check = 1;


    while((ch = fgetc(fp)) != EOF)
    {
    //    printf("ch = %d\n",ch);
        if(check == 1)
        {
            array[rows][cols] = ch;
    //        printf("array[%d][%d} = %c\n",rows, cols, array[rows][cols]);
        }
        check = 0;
        if((ch < 58) && (ch > 47))
        {
            cols += 1;
            array[rows][cols] = ch - 48 ;    //
     //       printf("array[%d][%d} = %d (if)\n",rows, cols, array[rows][cols]);
        }
        if(ch == '\n')
        {
            rows+= 1;
            cols = 0;
            check = 1;
        }
   //     printf("rows = %d, cols = %d\n", rows, cols);
//        printf("array[%d][%d] = %d\n",rows, cols, array[rows][cols]);
    }
		fclose(fp);

}


void _print_codebook(int* array[], int num_rows, int num_cols)
{

    int rows = 0;
    int cols = 0;

    while( rows < num_rows )
    {
				printf("%c: ", array[rows][0]);
        cols = 1;
        while(cols < (num_cols + 1))
        {
            printf(" %d ", array[rows][cols]);
            cols++;
        }
        printf("\n");
        rows++;

    }
}


/*
static void _print_byte(unsigned char onebyte)
{

	unsigned char mask = 0x80;
	while( mask > 0)
	{
			printf("%d", (onebyte & mask) == mask);
			mask >>= 1;
	}
	printf("\n");
}
*/


int _write_bit(FILE* fp, unsigned char bit, unsigned char* bit_pos, unsigned char* byte)
{
	if((*bit_pos) == 0)
	{
		*byte = 0;
	}

		unsigned char temp = bit << ( 7 - (*bit_pos));
		*byte |= temp;
		int return_val;

	// when all bits are written, write the byte to file

	if((*bit_pos) == 7)
	{
		int success;
		success = fwrite(byte, sizeof(unsigned char), 1, fp);
//		_print_byte(*byte);
		if(success == 1)
		{
			return_val = 1;
		}
		else
		{
			return_val = -1;
		}
	}

	// incremented bit_pos
//	printf("bit_pos = %d", *bit_pos);

	(*bit_pos) = ((*bit_pos)+ 1) % 8;
	return return_val;
}

void _char_convert(FILE* fp, int ch, unsigned char* bit_pos, unsigned char* byte)
{
	unsigned char mask = 0x40;

	while(mask > 0)
	{
		_write_bit(fp, (ch & mask) == mask, bit_pos, byte);
		mask >>= 1;
	}
}


void _traverse_header(TreeNode* curr, FILE* fp, unsigned char* bit_pos,  unsigned char* byte)
{

	if( curr == NULL)
	{
		return;
	}

	TreeNode* curr_left = curr -> left;
	TreeNode* curr_right = curr -> right;
//	if((curr_left == NULL) && (curr_right == NULL))
	if( curr -> left == NULL && curr -> right == NULL)
	{
//    	fprintf(fp , "1%c", curr -> ASCII);    // implementation 1 and 2
//		printf("1%c ", curr -> ASCII);
		_write_bit(fp, 1, bit_pos, byte);
		_char_convert(fp, curr -> ASCII, bit_pos, byte);
		return;

	}
		_traverse_header(curr_left, fp, bit_pos, byte);
		_traverse_header(curr_right, fp, bit_pos, byte);
//		printf(fp"0");
		_write_bit(fp, 0, bit_pos, byte);
//		printf("bit_pos = %d ", *bit_pos );
//	fprintf(fp, "0");     // implementation 2

}

void _write_header(TreeNode* curr, unsigned int num_chars, char* Filename)
{
	FILE* fp = fopen(Filename,"w");

	if(fp == NULL)
	{
		return;
	}

	unsigned char bit_pos = 0;
	unsigned char byte = 0;
	_traverse_header(curr, fp, &bit_pos,& byte);


	// if byte is incomplete

	while( (bit_pos) != 0 )
	{
			_write_bit(fp, 0, &bit_pos, &byte);
	}


	fwrite(&num_chars, sizeof(unsigned int), 1, fp);
	unsigned char nl = '\n';
	fwrite(&nl, sizeof(unsigned char), 1 , fp);
	fclose(fp);
}

void _mapping_array(int* mapper, int** codebook, int num_rows)
{
		int max = 264;
		int index = 0;


		while( index < max)
		{
			mapper[index] = -1;
			for(int index2 = 0; index2 < num_rows; index2++)
			{
				if(codebook[index2][0] == index)
				{
					mapper[index] = index2;
				}
			}
			index++;
		}
}

void _print_mapper(int* mapper)
{
	int index3 = 0;

	while(index3 < 128)
	{
		printf("mapper[%d] = %d\n", index3, mapper[index3]);
		index3++;
	}
}

int _compress(char* input, char* output, int** codebook, int* mapper)
{
	FILE* fp = fopen(input, "r");

	if(fp == NULL)
	{
		return 0;
	}

	FILE* fe = fopen(output,"a");
	if(fe == NULL)
	{
		return 0;
	}

	unsigned char bit_pos = 0;
	unsigned char byte = 0;

	while(!feof(fp))
	{
		int ch = fgetc(fp);
		if(ch != EOF)
		{
			int ind = mapper[ch];
			int ind2 = 1;
			while(codebook[ind][ind2] != -1)
			{
				_write_bit(fe, (codebook[ind][ind2] == 1), &bit_pos, &byte);
				ind2++;
			}
		}
	}
	while(bit_pos != 0)
	{
		_write_bit(fe, 0, &bit_pos, &byte);
	}
	fclose(fp);
	fclose(fe);
	return 1;
}


void _free_everything(Node* head, int** codebook, int* path, int* rows)
{
	int each_row = 0;

	for(each_row = 0; each_row < *rows; each_row++)
	{
		free(codebook[each_row]);
	}
	free(codebook);


	// freeing nodes

	Node* free_head = head;
	while(free_head != NULL){
				_destroy_tree(free_head -> ptr);
		free_head = free_head -> next;
	}
	_destroy_node(head);

	free(path);
}
//=============================================================================//


int huff(char* input, char* output1, char* output2 )
{
	unsigned int num_chars = 0;
	num_chars = _get_num_chars(input);

//	printf("num_chars = %u ", num_chars);    // num_chars is 13 for go go gophers

	FILE* fp = fopen(input,"r");
	FILE* fe = fopen(output1,"w");

	char ASCII_count[256] = {0};
	_make_ASCII_count(ASCII_count,fp);

	// converting occurences to linked lists

	Node* head = NULL;
	head = _make_queue(head, ASCII_count);

 /*  Print queue to check if pq enqueue is working
	Node* temp = NULL;
  temp = head;

  //	_print_queue(temp);
  */

	// building the tree
	head = _build_tree_from_queue(head);

	TreeNode* huffman = head -> ptr;

	int* path = malloc(sizeof(path) * 9);
	path = _make_path(path);


	_recurse(huffman,fe, path, 0);

	fclose(fe);

  int rows = 0;
  int cols = 0;
  _codebook_dims(output1, &rows, &cols);

    // Creating 2d array for codebook.

	int** codebook;

	codebook = _create_codebook(&rows, &cols);

	_fill_codebook(output1,(int**) codebook);
//  _print_codebook((int**) codebook, rows, cols);

	TreeNode* header = head -> ptr;
	int mapper[264] = {0};

	_mapping_array(mapper, codebook, rows);
	_write_header(header, num_chars, output2);
	_compress(input, output2, codebook, mapper);

	//_print_mapper(mapper);  // check to see if mapper works
	// free everything

	_free_everything(head, codebook, path, &rows);

	fclose(fp);
	return 1;
}


int main(int argc, char* argv[]){
	if(argc != 4)
	{
		printf("ERROR: there should be 3 arguments\nFirst is the input, second is codebook irrelevant of input, third is input.huff");
		return 0;
	}
	huff(argv[1], argv[2], argv[3]);

	return 1;
}

// Test write_bit individually
// Test convert char function indvidiually
// Test compress individually
