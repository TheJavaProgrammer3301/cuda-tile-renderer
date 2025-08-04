#include <iostream>

__global__ void helloFromGPU() {
    printf("Hello from GPU!\n");
}

int main() {
    helloFromGPU<<<1, 1>>>();
    cudaDeviceSynchronize();
    std::cout << "Hello from CPU!\n";
    return 0;
}
