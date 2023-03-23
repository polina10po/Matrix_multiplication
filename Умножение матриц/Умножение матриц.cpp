#include <iostream>
#include <chrono>
#include <omp.h>
const int N = 1000;
int main()
{
    srand(unsigned(time(NULL)));

    int** A = new int* [N];
    for (int i = 0; i < N; i++)
        A[i] = new int[N];
    int** B = new int* [N];
    for (int i = 0; i < N; i++)
        B[i] = new int[N];
    int** C = new int* [N];
    for (int i = 0; i < N; i++)
        C[i] = new int[N];

    //заполнение массива рандомными числами
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    //последовательное
    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
                C[i][j] = sum;
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Sequential multiplication: " << elapsed_ms.count() << " milliseconds\n";

    //OpenMP
    begin = std::chrono::steady_clock::now();
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Multiplication with OpenMP: " << elapsed_ms.count() << " milliseconds\n";

    return 0;
}