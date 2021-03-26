// ----------------------------------------------------------

#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// ----------------------------------------------------------

// We provide a small library so we can easily setup OpenCL
#include "clutils.h"

// ----------------------------------------------------------

int main(int argc,char **argv)
{

    const char *clu_File = SRC_PATH "basics.cl"; 

    // Initialize OpenCL
    cluInit();

    // After this call you have access to
    // clu_Context;      <= OpenCL context (pointer)
    // clu_Devices;      <= OpenCL device list (vector)
    // clu_Queue;        <= OpenCL queue (pointer)

    // Load Kernel
    cl::Program *program = cluLoadProgram(clu_File);
    cl::Kernel  *kernel = cluLoadKernel(program, "exercice1");

    // allocate memory and opencl buffer
    const int size = 12;
    cl::Buffer a_buffer(*clu_Context, CL_MEM_READ_ONLY, size * sizeof(int));
    cl::Buffer b_buffer(*clu_Context, CL_MEM_READ_ONLY, size * sizeof(int));
    cl::Buffer c_buffer(*clu_Context, CL_MEM_WRITE_ONLY, size * sizeof(float));

    // fill a_buffer and b_buffer with values
    int* a = new int[size];
    int* b = new int[size];
    int list_a[] = {1, 2, 4, 1, 3, 1, 4, 3, 2, 4, 1, 2};
    int list_b[] = {1, 5, 9, 3, 4, 6, 2, 1, 7, 3, 8, 5};
    for (int i = 0; i < size; i++) {
        a[i] = list_a[i];
        b[i] = list_b[i];
    }
    clu_Queue->enqueueWriteBuffer(a_buffer, true, 0, size * sizeof(int), a);
    clu_Queue->enqueueWriteBuffer(b_buffer, true, 0, size * sizeof(int), b);
    delete[] a;
    delete[] b;

    // execute kernel
    kernel->setArg(0, a_buffer);
    kernel->setArg(1, b_buffer);
    kernel->setArg(2, c_buffer);

    cl_int clerr = clu_Queue->enqueueNDRangeKernel(*kernel, cl::NullRange,
        cl::NDRange(size),    // global work size
        cl::NDRange(size));   // group work size
    cluCheckError(clerr, "Error running the kernel");

    // copy back the results
    float* c = new float[size];

    clu_Queue->enqueueReadBuffer(c_buffer, true, 0, size * sizeof(float), c);

    for (int i = 0; i < size; i++) {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl;

    delete[] c;

    return 0;
}

// ----------------------------------------------------------

