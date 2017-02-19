#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned t1, t2, t3;
/*intializing counters*/
int c0=0;
int c1=0;
int c2=0;
int c3=0;
void func(int a1, int a2, int a3)
{
	int i,j,k;

	if(a1){
        c0++;
		i++;
		if(a2){
            c1++;
			j++;
		}
	} else {
        c2++;
		k++;
	}

	if(a3){
        c3++;
		k++;
	}
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
    printf("AB:%d\n",c0);
    printf("AC:%d\n",c2);
    printf("BD:%d\n",c0-c1);
    printf("BE:%d\n",c1);
    printf("CF:%d\n",c2);
    printf("DF:%d\n",c0-c1);
    printf("EF:%d\n",c1);
    printf("FG:%d\n",c3);
    printf("FH:%d\n",c0+c2-c3);
	
    c0=0;c1=0;c2=0;c3=0;
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
    printf("AB:%d\n",c0);
    printf("AC:%d\n",c2);
    printf("BD:%d\n",c0-c1);
    printf("BE:%d\n",c1);
    printf("CF:%d\n",c2);
    printf("DF:%d\n",c0-c1);
    printf("EF:%d\n",c1);
    printf("FG:%d\n",c3);
    printf("FH:%d\n",c0+c2-c3);

	return EXIT_SUCCESS;
}

