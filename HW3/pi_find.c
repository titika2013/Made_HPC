#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

unsigned int INTERVAL = 100000000;

int main() {
    double r_x, r_y, pi;
    unsigned int x_seed, y_seed, circle_points, tid;
    size_t i;
    double time_start, end_time;

    time_start = omp_get_wtime();

#pragma omp parallel default(none)\
    private(r_x, r_y, x_seed, y_seed, i, tid) \
    shared(INTERVAL, circle_points)

    {
        tid = omp_get_thread_num();
        x_seed = (time(NULL) & 0xFFFFFFF0) | (tid + 1);
        y_seed = (time(NULL) & 0xF0F0F0F0) | (tid + 13);

#pragma omp  for reduction(+: circle_points)
        for (i = 0; i < (INTERVAL); i++) {
            r_x = (double) rand_r(&x_seed) / (double) RAND_MAX;
            r_y = (double) rand_r(&y_seed) / (double) RAND_MAX;

            if (r_x * r_x + r_y * r_y <= 1)
                ++circle_points;
//            printf("%d of %d\n", omp_get_thread_num(), omp_get_num_threads());
        }

    }

    pi = (double) (4 * circle_points) / INTERVAL;


    printf("Iter %d ,  pi = %1.5f \n", INTERVAL, pi);
    end_time = omp_get_wtime();
    printf("Time: %f sec\n", end_time - time_start);
    return 0;
}
