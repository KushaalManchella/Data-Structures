#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "sorting.h"
#include <math.h>


/******************************
*[Kushaal Manchella]
*[sorting.c]: [06/26/2018].
*[kmanche@purdue.edu]
*Compiling: [gcc -Werror -lm -Wall -O3 sorting.c sorting_main.c -o proj1]
*******************************/


/*
	loads the file into Arr and returns Arr, size of array is stored in *Size
	when there is a file error, or memory allocation error, return NULL, and	
	set *Size to 0
*/
long *Load_From_File(char *Filename, int *Size)
{
    long *Arr = NULL;

	FILE* fp = fopen(Filename,"r");


	// checking if file is empty; 
	
	if( fp == NULL){
		*Size = 0;
		return Arr;
	}

	fseek(fp, 0, SEEK_SET);
	fscanf(fp,"%d", Size);



	fseek(fp, 0, SEEK_SET);
	char ch = 0;

	do{

	ch = fgetc(fp);

	}while(ch != '\n');	

	Arr = calloc((*(Size)),sizeof(long));

	for(int i = 0; i < *Size; i++){
		fscanf(fp,"%ld", &Arr[i]);
	}


	fclose(fp);
//
	

	


    return Arr;
}

/*
	Save the Array to the file Filename
	Return the number of elements saved to file
*/
int Save_To_File(char *Filename, long *Array, int Size)
{
    int n_written = 0;
	
	//
	FILE* fp = fopen(Filename,"w");
	fseek(fp, 0, SEEK_SET);
		
	for(int i = 0; i < Size; i++){
		fprintf(fp,"%ld\n", Array[i]);
		n_written++;
	}
	

	fclose(fp);
//	printf("\n n_written = %d \n", n_written);
	//
	
   return n_written;
}


/*
	Print the sequence in the order in which it appears in the triangle
 	2^(p)3^(q) is the largest number, 
	If Size is 0 or 1, an empty file should be created
*/
int Print_Seq(char *Filename, int length)
{
	int seq_size = 0;

   //
  
	FILE* fp = fopen(Filename,"w");
	fseek(fp, 0, SEEK_SET);
	
	int p;
	int q;
	int n = 0;
	int sequence = 0;

	while(sequence < length){
		q = n;

		for(p=0; p<=n; p++){
			
			sequence= pow(2,q)*pow(3,p);
			if( sequence > length){
				break;
			}
			fprintf(fp,"%d\n", sequence);
			seq_size++;

			q--;
		}
		n++;
		if(sequence > length){
			break;
		}
	}

	fclose(fp);

   //

    return seq_size;
}



void Shell_Insertion_Sort(long *a, int length, double *ncomp, double *nswap)
{
	int p;
	int q;
	int n = 0;
	int sequence = 0;
	int count = 0;

	while(sequence < length){
		q = n;

		for(p=0; p<=n; p++){
			
			sequence= pow(2,q)*pow(3,p);
			if( sequence > length){
				break;
			}
			count++;
			q--;
		}
		n++;
		if(sequence > length){
			break;
		}
	}


  	sequence = 0;
	n = 0;
	int k_size = count;	
	

	int* k_array = calloc(count+3, sizeof(int));
	int index = 0;


	while(sequence < length){
		q = n;

		for(p=0; p<=n; p++){
			
	  		sequence	=pow(2,q)*pow(3,p);
			if( sequence > length){
				break;
			}
			k_array[index] = sequence;
			index++;
			q--;
		}
		n++;
		if(sequence> length){
			break;
		}
	}



//
	for(int k = k_array[k_size]; k_size >= 0; k = k_array[k_size])
	{
			
		for(int j  = k; j < length ; j++)
		{
			long temp_r = a[j];
			int i = j;
			while((i >= k) && (a[i-k] > temp_r))
			{
				a[i] = a[i-k];
				i = i-k;
				(*ncomp)++;				
			}
			a[i] = temp_r;
			(*ncomp)++;
			(*nswap)++;

		}
		k_size--;

		if(k_size == 0){
			break;
		}


	}

		free(k_array);  // FREEING K_ARRAY



}


void Shell_Selection_Sort(long *a, int length, double *ncomp, double *nswap)
{

//	int min = 0;
//	int temp = 0;
//


//

	int p;
	int q;
	int n = 0;
	int sequence = 0;
	int count = 0;

	while(sequence < length){
		q = n;

		for(p=0; p<=n; p++){
			
			sequence= pow(2,q)*pow(3,p);
			if( sequence > length){
				break;
			}
			count++;
			q--;
		}
		n++;
		if(sequence > length){
			break;
		}
	}


  	sequence = 0;
	n = 0;
	int k_size = count;
	

	int* k_array = calloc(count+3, sizeof(int));
	int index = 0;


	while(sequence < length){
		q = n;

		for(p=0; p<=n; p++){
			
	  		sequence=pow(2,q)*pow(3,p);
			if( sequence > length){
				break;
			}
			k_array[index] = sequence;
			index++;
			q--;
		}
		n++;
		if(sequence> length){
			break;
		}
	}

	k_size += 0;
/*
//
//
int store; 
int min_ind = 0;

for(int k = k_array[k_size]; k_size >= 0; k = k_array[k_size])
	{
	for( int i = 0; i <(length - 1); i++){
		min_ind = i;
		for(int j = i+k; j < length; j++){
			if(a[j] < a[min_ind]){
				min_ind = j;
			}
			(*ncomp)++;	
		}
		store = a[i];
		a[i] = a[min_ind];
		a[min_ind] = store;
		(*nswap) += 3;
	}

	if(k_size == 0){
		break;
	}

	k_size--;

}

*/


	p= 0;
	q = length - 1;
	int store;
	int max;
	int min;

	for(int k = k_array[k_size]; k_size >= 0; k = k_array[k_size])
	{
		p = 0;
		q = length - 1;
		while(p < k){
			while( p < q){
				// finding min 
				min = a[p];
				for(int i = p; i<=q; i += k){
					if(a[i] < min){
						store = a[i];
						a[i] = min;
						min = store;
					}
					(*ncomp)++;
					(*nswap) += 3;
				}
				a[p] = min;
		
				// finding max 
				max = a[q];
				for(int j = p; j<= q; j += k){
					if(a[j] > max){
						store = a[j];
						a[j] = max;
						max = store;
					}
					(*ncomp)++;
					(*nswap) += 3;
				}
				a[q] = max;
		
				p++;
				q--;
			
			}

			p++;
		}
		k_size --;
	}

//printf("k_size at end = %d\n", k_size);
	free(k_array);



}
