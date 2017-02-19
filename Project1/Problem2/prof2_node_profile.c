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
    printf("A:%d\n",c0+c1);
    printf("B:%d\n",c0);
    printf("C:%d\n",c1);
    printf("D:%d\n",c2+c4);
    printf("E:%d\n",c0-c2);
    printf("F:%d\n",c1-c4);
    printf("G:%d\n",c2-c3+c4);
    printf("H:%d\n",c3);
    printf("I:%d\n",c0+c1-c2-c4);
    printf("J:%d\n",c0+c1-c2-c4);
    
    c0=0;c1=0;c2=0;c3=0;c4=0;
    
    input2();
    printf("\nINPUT2\n")
    
    srand(time(NULL));
    
    for(i=0; i<10000; i++){
        a1 = (rand() > t1);
        a2 = (rand() > t2);
        a3 = (rand() > t3);
        a4 = (rand() > t4);
        
        func(a1, a2, a3, a4);
    }
    
    /* Print out your profiling results here */
    printf("A:%d\n",c0+c1);
    printf("B:%d\n",c0);
    printf("C:%d\n",c1);
    printf("D:%d\n",c2+c4);
    printf("E:%d\n",c0-c2);
    printf("F:%d\n",c1-c4);
    printf("G:%d\n",c2-c3+c4);
    printf("H:%d\n",c3);
    printf("I:%d\n",c0+c1-c2-c4);
    printf("J:%d\n",c0+c1-c2-c4);
	
	return EXIT_SUCCESS;
}

