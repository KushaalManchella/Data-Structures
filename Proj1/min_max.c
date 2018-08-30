		while( p < q){
			// finding min 
			min = a[p];
			for(int i = p; i<=q; i += 1){
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
			for(int j = p; j<= q; j += 1){
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

//			printf("p = %d q = %d\n", p, q);
		}

