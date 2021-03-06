#include <papi.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned len = 16*(1 << 20);

void func(int * a)
{
	int i,j;

	for(i=0; i<1024; i++){
	for (j=i;j<=(len-1024+i);j+=1024){
	a[j]++;
	}
	}
}

int events[1] = {PAPI_TLB_DM}; /*PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TLB_DM*/
int eventnum = 1;

int main()
{
	long long values[1];
	int eventset;
	int * a;


	if(PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT)){
		printf("Can't initiate PAPI library!\n");
		exit(-1);
	}

	eventset = PAPI_NULL;
	if(PAPI_create_eventset(&eventset) != PAPI_OK){
		printf("Can't create eventset!\n");
		exit(-3);
	}
	if(PAPI_OK != PAPI_add_events(eventset, events, eventnum)){
		printf("Can't add events!\n");
		exit(-4);
	}

	a = (int *) malloc(len*sizeof(int));
	PAPI_start(eventset);
	func(a);
	PAPI_stop(eventset, values);
	free(a);

	/*Print out PAPI reading*/
	char event_name[PAPI_MAX_STR_LEN];
	if (PAPI_event_code_to_name( events[0], event_name ) == PAPI_OK)
		printf("%s: %lld\n", event_name, values[0]);
	
	return EXIT_SUCCESS;
}
