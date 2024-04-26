#include <iostream>
void matmul(int *A, int *B, int *C, int N)
{
    for (int Row = 0; Row < N; Row++)
    {
        for (int Col = 0; Col < N; Col++)
        {
            int Pvalue = 0;
            for (int k = 0; k < N; k++)
            {
                Pvalue += A[Row * N + k] * B[k * N + Col];
            }
            C[Row * N + Col] = Pvalue;
        }
    }
}
int main()
{
    int N = 512;
    int size = N * N * sizeof(int);
    int *A, *B, *C;
    A = new int[size];
    B = new int[size];
    C = new int[size];
    // Initialize matrices A and B
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i * N + j] = i * N + j;
            B[i * N + j] = j * N + i;
        }
    }
    // Perform matrix multiplication
    matmul(A, B, C, N);
    // Print the result (just printing the first 10x10 elements)
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << C[i * N + j] << " ";
        }
        std::cout << std::endl;
    }
    // Free memory
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