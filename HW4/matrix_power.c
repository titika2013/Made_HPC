#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

void random_graph(int n, int mat[n][n]) {
    unsigned int tid, seed;
#pragma omp parallel for  private(seed, tid) shared(mat, n) default(none)
    for (int i = 0; i < n; i++) {
        tid = omp_get_thread_num();
        seed = (15 & 0xFFFFFFF0) | (tid + 1);
        for (int j = 0; j < n; j++) {
            mat[i][j] = mat[i][j];
            if (i == j) {
                mat[i][j] = 0;
            } else {
            }
            mat[i][j] = rand_r(&seed) & 1;
        }
    }
}

void print_matrix(int n, int mat[n][n]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}


void matmul(int n, int in_arr[n][n], int temp[n][n], int res_arr[n][n]) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res_arr[i][j] = 0;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                res_arr[i][j] += in_arr[i][k] * temp[k][j];
            }
        }
    }
}

void power(int n, int in_arr[n][n], int res_arr[n][n], int power) {
    int temp_1[n][n];

#pragma omp parallel for shared(temp_1, in_arr, res_arr, n) default(none)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp_1[i][j] = in_arr[i][j];
            if (i == j) {
                res_arr[i][j] = 1;
            } else {
                res_arr[i][j] = 0;
            }
        }
    }
    int temp_2[n][n];

    while (1) {
        if (power == 1) {


            matmul(n, temp_1, res_arr, temp_2);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    res_arr[i][j] = temp_2[i][j];
                }
            }
            return;
        }

        if (power % 2 == 1) {
            power = power - 1;
            matmul(n, temp_1, res_arr, temp_2);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    res_arr[i][j] = temp_2[i][j];
                }
            }
        } else {
            power = power / 2;
            matmul(n, temp_1, temp_1, temp_2);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    temp_1[i][j] = temp_2[i][j];
                }
            }

        }
    }
}

int main() {
    int n = 4;
    int init_matrix[n][n], res_matrix[n][n];

    double time_start, end_time;
    time_start = omp_get_wtime();

    random_graph(n, init_matrix);
    print_matrix(n, init_matrix);
    power(n, init_matrix, res_matrix, 7);


    end_time = omp_get_wtime();

    printf("Time: %f sec\n", end_time - time_start);

    print_matrix(n, res_matrix);

    return 0;
}
