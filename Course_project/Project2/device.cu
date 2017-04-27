#include <cuda.h>
#include <stdio.h>

int main (void) {
  int deviceCount = 0;
  CUresult result = cuInit (0);
  
  result = cuDeviceGetCount (&deviceCount);
  for (int i=0; i<deviceCount; i++) {
    CUdevice device;
    char name[256];
    size_t bytes;
    int major, minor;
    CUdevprop prop;
    CUcontext ctx;
    size_t free, total;
    result = cuDeviceGet (&device, i);
    cuCtxCreate (&ctx, 0, device);
    printf ("device #           : %i\n"
            "=======================\n", i);
    cuDeviceGetName (name, 256, device);
    printf (" name              : %s\n", name);
    cuDeviceTotalMem (&bytes, device);
    printf (" memory            : %iMB\n", ((int) bytes)/(1024*1024));
    cuDeviceComputeCapability (&major, &minor, device);
    printf (" version           : %i.%i\n", major, minor);
    cuDeviceGetProperties (&prop, device);
    printf (" max threads/block : %i\n", prop.maxThreadsPerBlock);
    printf (" max thread size   : %ix%ix%i\n", 
            prop.maxThreadsDim[0],
	    prop.maxThreadsDim[1],
	    prop.maxThreadsDim[2]);
    printf (" max grid size     : %ix%ix%i\n", 
            prop.maxGridSize[0],
	    prop.maxGridSize[1],
	    prop.maxGridSize[2]);
    printf (" shared mem/block : %iKB\n", prop.sharedMemPerBlock/1024);
    printf (" constant memory  : %iKB\n", prop.totalConstantMemory/(1024));
    printf (" wrap size        : %i\n", prop.SIMDWidth);
    printf (" max mem pitch    : %i\n", prop.memPitch);
    printf (" registers/block  : %i\n", prop.regsPerBlock);
    printf (" clock rate       : %iMHz\n", prop.clockRate/1000);
    printf (" texture align    : %i\n", prop.textureAlign);
    printf ("\nMemory Info:\n");
    cuMemGetInfo (&free, &total);
    printf (" free             : %iMB\n", ((int) free)/(1024*1024));
    printf (" total            : %iMB\n", ((int) total)/(1024*1024));
    printf ("\n\n"); 
    cuCtxDetach(ctx);
  }
 
  return 0;
}
