#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


void _destroy_tree(TreeNode* tree){
    if(tree == NULL)
    {
        return;
    }
    _destroy_tree(tree-> left);
    _destroy_tree(tree-> right);
    free(tree);
}

int _read_bit(FILE* fp, unsigned char* bit, unsigned char* bit_pos, unsigned char* byte)
{
  int success = 1;
  if((*bit_pos) == 0)
  {
    success = fread(byte, sizeof(unsigned char), 1, fp);
  }
  if( success != 1)
  {
    return -1;
  }
  unsigned char temp = (*byte) >> (7-(*bit_pos));
  temp = temp & 0x01;

  *bit_pos = ((*bit_pos) + 1) % 8;
  *bit = temp;
  return 1;
}

TreeNode* _create_tree_node(int freq,char ASCII)
{
	TreeNode tree = {
		.freq = freq,
		.ASCII = ASCII,
		.left = NULL,
		.right = NULL
	};
	TreeNode* node = malloc(sizeof(*node));
	*node = tree;

	return node;
}



Node* _insert_to_list(Node* head, Node* new_node)
{
  if(new_node == NULL)
  {
    return NULL;
  }
  if(head == NULL)
  {
    head = new_node;
    new_node -> next = NULL;
  }
  else
  {
    new_node -> next = head;
  }

    return new_node;

}


Node* _merge_nodes(Node* head)
{
  if(head -> next == NULL)
  {
    return NULL;
  }
  Node* second = head -> next;
  Node* third = second -> next;

  TreeNode* first_tree = head -> ptr;
  TreeNode* second_tree = second -> ptr;


  //removing first 2 nodes

  free(head);
  free(second);

  TreeNode* combined = malloc(sizeof(*combined));
  combined -> ASCII = -1;
  combined -> freq = (first_tree -> freq) + (second_tree -> freq);
  combined -> left = second_tree;
  combined -> right = first_tree;

  Node* new_node = malloc(sizeof(*new_node));
  new_node -> ptr = combined;

  head = _insert_to_list(third, new_node);

  return head;

}


TreeNode* _build_tree(FILE* fp)
{
  int end = 0;
  unsigned char bit_pos = 0;
  unsigned char byte = 0;
  unsigned char bit = 0;

  Node* head = NULL;

  while( end == 0)
  {
    _read_bit(fp, &bit, &bit_pos, &byte);
//    printf("bit = %u\n", bit);
    if( bit == 1)
    {
      int count = 0;
      unsigned char mask = 0;
      for(count = 0; count < 7; count++)
      {
        mask <<= 1;
        _read_bit(fp, &bit, &bit_pos, &byte);
        mask |= bit;
      }
        // Creating new node containing character
      TreeNode* entry = _create_tree_node(0, mask);
      Node* new_node = malloc(sizeof(*new_node));

      new_node -> ptr = entry;
      new_node -> next = NULL;
      head = _insert_to_list(head, new_node);

    }
    else
      {
        if(head == NULL)
        {
          printf("Something is wrong with list\n");
        }
        if(head -> next == NULL)
        {
          end = 1;
        }
        else
        {
          head = _merge_nodes(head);
        }
      }
  }
  TreeNode* root = head -> ptr;
  free(head);
  return root;
}



int unhuff(char* input, char* output)
{
  FILE* fp = fopen(input,"r");
  FILE* fe = fopen(output,"w");
  unsigned int num_chars; // number of characters in input file
  unsigned char nl; // new line

  unsigned char bit_pos = 0;
  unsigned char bit = 0;
  unsigned char byte = 0;


  if(fp == NULL)
  {
    return 0;
  }
  TreeNode* root = _build_tree(fp);


  fread(&num_chars, sizeof(unsigned int), 1, fp);
//  printf("num_chars = %u", num_chars);

  fread(&nl, sizeof(unsigned char), 1, fp);
  if(nl != '\n')
  {
    printf("Error with newline");
  }

  while(num_chars != 0)
  {
    TreeNode* temp_tree = root;
    while((temp_tree -> left != NULL))
    {
      _read_bit(fp, &bit, &bit_pos, &byte);
      if(bit == 0)
      {
        temp_tree = temp_tree -> left;
      }
      else
      {
        temp_tree = temp_tree -> right;
      }
    }

//    printf("%c", temp_tree -> ASCII);
      fprintf(fe,"%c", temp_tree -> ASCII);
      num_chars--;
    }

  _destroy_tree(root);
  fclose(fp);
  fclose(fe);

  return 1;
}



int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    printf("ERROR: there should be 2 arguments\nFirst is the input.huff, second is input.unhuff");
    return 0;
  }
  unhuff(argv[1], argv[2]);

  return 1;
}
