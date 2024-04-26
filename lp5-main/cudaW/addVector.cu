#include <iostream>
void addVectors(int *A, int *B, int *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        C[i] = A[i] + B[i];
    }
}
int main()
{
    int n = 1000000;
    int *A, *B, *C;
    A = new int[n];
    B = new int[n];
    C = new int[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = i;
        B[i] = i * 2;
    }
    addVectors(A, B, C, n);
    for (int i = 0; i < 10; i++)
    {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;
    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}

/*
without gpu
1. sudo apt install nvidia-cuda-toolkit
2. wget https://developer.download.nvidia.com/compute/cuda/12.4.1/local_installers/cuda_12.4.1_550.54.15_linux.run
3. nvcc -arch=sm_60 addVector.cu -o addVector
4. ./addVector
*/