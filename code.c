#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double rand_normal(double mean, double stddev) {
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return z0 * stddev + mean;
}

int main() {
    int n = 100000;
    double mean = 0.0;
    double stddev = 1.0;

    double *U1 = (double *)malloc(n * sizeof(double));
    double *U2 = (double *)malloc(n * sizeof(double));
    double *G2 = (double *)malloc(n * sizeof(double));

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        U1[i] = rand_normal(mean, stddev);
        U2[i] = rand_normal(mean, stddev);
    }

    int num_failed = 0;
    for (int i = 0; i < n; i++) {
        G2[i] = ((U1[i] - 3) * (U1[i] - 3)) / (2 * 2) + ((U2[i] - 2) * (U2[i] - 2)) / (1 * 1) - 1;
        if (G2[i] <= 0) {
            num_failed++;
        }
    }

    double pf_MCS = (double)num_failed / n;

    
    printf("shape: %d\n", n);
    printf("total number of samples in U1: %d\n", n);
    printf("total number of samples in U2: %d\n", n);
    printf("mean of U1: %f\n", mean);
    printf("mean of U2: %f\n", mean);
    printf("standard deviation of U1: %f\n", stddev);
    printf("standard deviation of U2: %f\n", stddev);
    printf("TOTAL NUMBER OF FAILED SIMULATIONS: %d\n", num_failed);
    printf("pf_MCS = %f\n", pf_MCS);

    free(U1);
    free(U2);
    free(G2);

    return 0;
}
