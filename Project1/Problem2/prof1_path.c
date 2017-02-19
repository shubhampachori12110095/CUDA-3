#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned t1, t2, t3;
/*intializing counters*/
int c[6]={0};
void func(int a1, int a2, int a3)
{
	int i,j,k;
	int z=0;
	if(a1){
       		 i++;
       		 if(a2){
           	 j++;
           	 z++;
        }
    }
    else {
        k++;
        z+=2;
    }
    
    if(a3){
        k++;
        z+=3;
    }
    c[z]++;
}
 
/* No profiling for code below*/

/* Input set 1 */
void input1()
{
	t1 = 0.5 * RAND_MAX;
	t2 = 0.5 * RAND_MAX;
	t3 = 0.5 * RAND_MAX;
}
/* End input set 1*/

/* Input set 2 */
void input2()
{
	t1 = 0.2 * RAND_MAX;
	t2 = 0.6 * RAND_MAX;
	t3 = 0.8 * RAND_MAX;
}
/* End input set 2*/


int main()
{
	int i;
	unsigned a1, a2, a3;

	input1();
    printf("\nINPUT1\n");
	

	srand(time(NULL));

	for(i=0; i<10000; i++){
		a1 = (rand() > t1);
		a2 = (rand() > t2);
		a3 = (rand() > t3);

		func(a1, a2, a3);
	}

	/* Print out your profiling results here */
    printf("ABDFH:%d\n",c[0]);
    printf("ABDFG:%d\n",c[3]);
    printf("ABEFH:%d\n",c[1]);
    printf("ABEFG:%d\n",c[4]);
    printf("ACFG:%d\n",c[5]);
    printf("ACFH:%d\n",c[2]);
	
    for (i=0; i<6;i++){
	c[i]=0;
}

    
    input2();
    printf("\nINPUT2\n");
    
    
    srand(time(NULL));
    
    for(i=0; i<10000; i++){
        a1 = (rand() > t1);
        a2 = (rand() > t2);
        a3 = (rand() > t3);
        
        func(a1, a2, a3);
    }
    
    /* Print out your profiling results here */
    printf("ABDFH:%d\n",c[0]);
    printf("ABDFG:%d\n",c[3]);
    printf("ABEFH:%d\n",c[1]);
    printf("ABEFG:%d\n",c[4]);
    printf("ACFG:%d\n",c[5]);
    printf("ACFH:%d\n",c[2]);

	return EXIT_SUCCESS;
}

