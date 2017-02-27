#include<stdio.h>
#include<omp.h>

int main(int argc, char *argv[])
{
    float res = 0;
    float *p = &res;

    double init = omp_get_wtime();
    #pragma omp parallel
    {
        float q = 2.0f;
        for(int i = 0; i < 1000000; ++i)
        {
            #pragma omp atomic
            *p += q;
        }
    }
    double end = omp_get_wtime();
    printf("bin, %s, val, %lf, time, %lf\n",argv[0], *p, end  - init);
}
