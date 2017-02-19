#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned t1, t2, t3, t4;

int c0=0;
int c1=0;
int c2=0;
int c3=0;
int c4=0;

void func(int a1, int a2, int a3, int a4)
{
	int i,j,k;

	if(a1){
        c0++;
		i++;
        if(a2){
			j++;
		} else {
            c2++;
			i++;
			goto b1;
		}

		k++;
		goto b2;
	} else {
        c1++;
		if(a3){
			j++;
		} else {
            c4++;
			k++;
			goto b1;
		}

		k++;
		goto b2;
	}

b1: if(a4){
    c3++;
		j++;
	}

b2: k++;
}

/* Input set 1 */
void input1()
{
	t1 = 0.5 * RAND_MAX;
	t2 = 0.5 * RAND_MAX;
	t3 = 0.5 * RAND_MAX;
	t4 = 0.5 * RAND_MAX;
}
/* End input set 1*/

/* Input set 2 */
void input2()
{
	t1 = 0.2 * RAND_MAX;
	t2 = 0.6 * RAND_MAX;
	t3 = 0.8 * RAND_MAX;
	t4 = 0.3 * RAND_MAX;
}
/* End input set 2*/


int main()
{
	int i;
	unsigned a1, a2, a3, a4;

	input1();
	
    printf("\nINPUT1\n");

	srand(time(NULL));

	for(i=0; i<10000; i++){
		a1 = (rand() > t1);
		a2 = (rand() > t2);
		a3 = (rand() > t3);
		a4 = (rand() > t4);

		func(a1, a2, a3, a4);
	}

	/* Print out your profiling results here */
    printf("AB:%d\n",c0);
    printf("AC:%d\n",c1);
    printf("BD:%d\n",c2);
    printf("BE:%d\n",c0-c2);
    printf("EI:%d\n",c0-c2);
    printf("CD:%d\n",c4);
    printf("CF:%d\n",c1-c4);
    printf("FI:%d\n",c1-c4);
    printf("DG:%d\n",c2+c4-c3);
    printf("DH:%d\n",c3);
    printf("IJ:%d\n",c0+c1-c2-c4);
    
    c0=0;c1=0;c2=0;c3=0;c4=0;
    
    input2();
    printf("\nINPUT2\n");
    
    srand(time(NULL));
    
    for(i=0; i<10000; i++){
        a1 = (rand() > t1);
        a2 = (rand() > t2);
        a3 = (rand() > t3);
        a4 = (rand() > t4);
        
        func(a1, a2, a3, a4);
    }
    
    /* Print out your profiling results here */
    printf("AB:%d\n",c0);
    printf("AC:%d\n",c1);
    printf("BD:%d\n",c2);
    printf("BE:%d\n",c0-c2);
    printf("EI:%d\n",c0-c2);
    printf("CD:%d\n",c4);
    printf("CF:%d\n",c1-c4);
    printf("FI:%d\n",c1-c4);
    printf("DG:%d\n",c2+c4-c3);
    printf("DH:%d\n",c3);
    printf("IJ:%d\n",c0+c1-c2-c4);

	
	return EXIT_SUCCESS;
}

