#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cuda_profiler_api.h>
#define N 512
#define TILE_SIZE 16
__global__ void MatrixMultiply(float *d_A, float *d_B, float *d_C, int length)
{
	
	/*int ty = threadIdx.y;*/
	/*int tx = threadIdx.x;*/
	int numcol = blockIdx.x*TILE_SIZE + threadIdx.x;
 	int numrow = blockIdx.y*TILE_SIZE + threadIdx.y;
 	float  cvalue = 0;
 	for (int k =0; k<N;++k){
        float d_Aelement =  d_A[numrow*N+k];
        float d_Belement =  d_B[k*N+numcol];
        cvalue += d_Aelement * d_Belement;
        }
d_C[numrow*N+numcol] = cvalue;
}
int main(){

	int i,j,k;
	
	float *d_A, *d_B, *d_C;	
	float *h_A, *h_B, *h_C;

	size_t size = N*N*sizeof(float);

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	//Allocate Device memory
	cudaMalloc((void **)&d_A, size);
	cudaMalloc((void **)&d_B, size);
	cudaMalloc((void **)&d_C, size);

	//Allocate Host memory
	cudaMallocHost((void **)&h_A, size);
	cudaMallocHost((void **)&h_B, size);	
	cudaMallocHost((void **)&h_C, size);

	
	//Initialize matrices on the host
	for(i=0;i<N;i++){
	    for(j=0;j<N;j++){
		h_A[i*N+j]=i;
		h_B[i*N+j]=i+1;
	    }
	}


	//Allocate A and B to the Device
	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);


	//Invoke kernel
	dim3 blockPerGrid(N/TILE_SIZE,N/TILE_SIZE);
	dim3 threadPerBlock(TILE_SIZE,TILE_SIZE);

	cudaEventRecord(start);	
	MatrixMultiply<<<blockPerGrid, threadPerBlock>>>(d_A, d_B, d_C,N);
	cudaEventRecord(stop);	


	//Read C from device
	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
	
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

	printf("Elapsed time (ms): %f\n", milliseconds);
	
	//Calculate the MM result with normal CPU implementation and compare the results with the GPU

	float * test_C;
	test_C = (float *)malloc(size);	
	for (i=0; i<N; i++){
		for (j=0;j<N;j++){
			float sum = 0;
			for (k=0;k<N;k++){
				float a = h_A[i*N+k];
				float b = h_B[k*N+j];
				sum += a*b;
			}
			test_C[i*N+j]= sum;
		}
	}
	int compare = 0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if (test_C[i*N+j]==h_C[i*N+j]){
				compare++;
			}else{
				compare+=0;
			}
		}
	}
	if(compare == N*N){
		printf("Success!\n");
	}else{
		printf("Error!\n");	
	}

	/*=============================Finish Test=================================*/

	free(test_C);
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	cudaFree(h_A);
	cudaFree(h_B);
	cudaFree(h_C);
	cudaDeviceReset();
	return EXIT_SUCCESS;
}
