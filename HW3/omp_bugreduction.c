#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

float dotprod(float *a, float *b, size_t N) {
    int i, tid;
    float sum = 0.;

#pragma omp parallel default(none) \
    shared(sum, a, b, N) \
    private(i, tid)
    {
        tid = omp_get_thread_num();
#pragma omp for reduction(+:sum)
        for (i = 0; i < N; ++i) {
            tid = omp_get_thread_num();
            sum += a[i] * b[i];

            printf("tid = %d i = %d\n", tid, i);
//            printf("%d of %d\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    const size_t N = 100;
    int i;
    float sum;
    float a[N], b[N];


    for (i = 0; i < N; ++i) {
        a[i] = b[i] = (double) i;
    }

    sum = dotprod(a, b, N);

    printf("Sum = %f\n", sum);

    return 0;
}
