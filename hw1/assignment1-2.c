#include <stdio.h>
#include <stdlib.h>


int main( int argc, char *argv[] ) {
	int N = atoi(argv[1]);
	if (N <=0){
	//fprintf(stderr, "Not a valid command line argument.\n");
	printf("Not a valid command line argument.\n");
	return 0;
	}
	
	typedef struct fraction {
		int up;
		int down;
		
	} fraction; 
	

        
        void print_fraction(fraction f) {
	printf("%d/%d\n",f.up,f.down);
	}
	
	void print_fraction_real(fraction f) {
	printf("%f\n", (double)f.up/(double)f.down);
	}


	
	fraction square_fraction(fraction f) {
	int su = f.up*f.up;
	int sd = f.down*f.down;
	fraction g = {su,sd};
	return g;
	}
	
	fraction square_fraction_inplace(fraction* f) {

	(*f).up = (*f).up * (*f).up ;
	(*f).down= (*f).down * (*f).down;
	
	return *f;
	}
	
	double fraction2double(fraction f) {
	double r = (double)f.up/ (double)f.down ;
	
	printf ("%f", r);
	return r;
	}
	
	
	
	fraction* arr = (fraction*) malloc (sizeof(fraction)*N);
	int i;
	printf ("a=(");
	for (i=1; i<=N; i++){
	arr[i].up=1;
	arr[i].down=i*(i+1);
	printf ("%d/(%d*%d),", 1, i, i+1);
	}
	printf ("...)\n");
	//free(arr);
		/*
	int* arrup = (int*) malloc (sizeof(int)*N);
	int* arrdown = (int*) malloc (sizeof(int)*N);
	int i;	
	for (i=1; i<=N; i++) {

	fraction r= {1, i*(i+1)};
	arrup[i]=1;
	arrdown[i]= i*(i+1);
	printf ("%d/%d\n", arrup[i], arrdown[i]);
	}	
	*/
	
	
	
	fraction fraction_sum(fraction arr[]) {
		int i;
		fraction g = {0,1};
		for (i=1; i<=N; i++) {
		//printf ("g is %d/%d arr[i]is %d/%d", g.up, g.down, arr[i].up,arr[i].down);
		g.up = g.up*arr[i].down+g.down*arr[i].up;
		g.down = g.down*arr[i].down;
		//////
		/*///No1  
		int r;
		for(r = 2; r * r <= g.up;) if(g.up % r == 0 & g.down % r == 0) {
		//printf("g.up / %d \n", r);
		//if(g.down % r ==0)
		//printf("g.dowon also / %d \n", r);	 
        	//printf("%d * ", r); 
        	g.up = g.up/r;
        	g.down= g.down/r; 
		}else { r++; }
		*/////No1
		//No2
		int a = g.up;
		int b = g.down;
		
		while (b != 0){
		int t = a%b;
		a=b; b=t;
		}
		g.up=g.up/a;
		g.down=g.down/a;
		//No2
		
		
    		//////
		//printf ("the sum is %d/%d now. for %d loop.\n", g.up, g.down, i);
		}
		//printf("\n");
		return g;	
	}
	
	
	print_fraction_real(fraction_sum(arr));
	print_fraction(fraction_sum(arr)); 
	/*
	fraction f = {2,3};
	print_fraction(f);
	fraction g = square_fraction(f);
	print_fraction(f);
	print_fraction(g);
	square_fraction_inplace(&f);
	print_fraction(f);
	fraction2double(g);
	*/
}



//still can't deal with larger N, ie N>1289.
