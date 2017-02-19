#include <stdio.h>
#include <stdlib.h>
#define N 1024

__global__ void MatrixMultiply(float *d_A, float *d_B, float *d_C, int NB, int NT)
{
	__shared__ float Mds[64*64];
	__shared__ float Nds[64*64];
	int tx =threadIdx.x;
	int ty =threadIdx.y;
	int numrow = NB*(blockIdx.y*NT + threadIdx.y);
        int numcol = NB*(blockIdx.x*NT+threadIdx.x);


	for (int j=0;j<NB;j++){
		for (int i=0;i<NB;i++){		
        	float cvalue=0.0;
       		for (int m=0; m < N/(NT*NB); ++m){
	Mds[(ty+j)*NT*NB+tx+i] = d_A[(j+numrow)*N + (m*NT*NB+tx+i)];
	Nds[(ty+j)*NT*NB+tx+i] = d_B[numcol+i + (m*NT*NB + ty+j)*N];
	__syncthreads();
                        for (int k=0;k<NB*NT;k+=4){
                cvalue+= Mds[(ty+j)*NT*NB+k] * Nds[k*NT*NB+tx+i];
		cvalue+= Mds[(ty+j)*NT*NB+k+1] * Nds[(k+1)*NT*NB+tx+i];

		cvalue+= Mds[(ty+j)*NT*NB+k+2] * Nds[(k+2)*NT*NB+tx+i];

		cvalue+= Mds[(ty+j)*NT*NB+k+3] * Nds[(k+3)*NT*NB+tx+i];

                        }
                d_C[(j+numrow)*N+numcol+i] = cvalue;
}}}}


int main(){

	int i,j,k;
	int NB =1;
	int NT= 64;
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
	/*for(NT=32;NT<N;NT=2*NT){*/
	/*for(NB=2;NB<(N/NT);NB=NB*2){*/

	//Invoke kernel
	dim3 blockPerGrid(N/(NT*NB),N/(NT*NB));
	dim3 threadPerBlock(NT,NT);

	cudaEventRecord(start);	
	MatrixMultiply<<<blockPerGrid, threadPerBlock>>>(d_A, d_B, d_C,NB,NT);
	cudaEventRecord(stop);	


	//Read C from device
	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
	
	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

	printf("NB %d NK %d NT %d Elapsed time (ms): %f\n",NB,N/(NT*NB),NT, milliseconds);

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
