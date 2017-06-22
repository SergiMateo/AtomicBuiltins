#include<stdio.h>
#include<omp.h>

typedef double REAL_TYPE;
typedef long int INT_TYPE_OF_REAL_TYPE_SIZE;

typedef  union {
    REAL_TYPE __val;
    INT_TYPE_OF_REAL_TYPE_SIZE __addr;
} MyUnion;

REAL_TYPE q = (REAL_TYPE) 0.1237;
int num_iterations = 10000000;

void compute_atomic_reduction(REAL_TYPE val, REAL_TYPE* sum)
{
#if VERSION == 1

    #pragma omp atomic
    (*sum) += val;

#elif VERSION == 2

    REAL_TYPE __oldval;
    REAL_TYPE __newval;
    REAL_TYPE __temp = val;
    do
    {
        __oldval = *sum;
        __newval = __oldval + __temp;
        __sync_synchronize();
    }
    while (!__sync_bool_compare_and_swap_8((INT_TYPE_OF_REAL_TYPE_SIZE *)&(*sum), (MyUnion){.__val = __oldval}.__addr, (MyUnion){.__val = __newval}.__addr));

#elif VERSION == 3

    volatile REAL_TYPE __oldval;
    volatile REAL_TYPE __newval;
    REAL_TYPE __temp = val;
    do
    {
        __oldval = *sum;
        __newval = __oldval + __temp;
    }
    while (!__sync_bool_compare_and_swap_8((INT_TYPE_OF_REAL_TYPE_SIZE *)&(*sum), (MyUnion){.__val = __oldval}.__addr, (MyUnion){.__val = __newval}.__addr));

#elif VERSION == 4

    REAL_TYPE __oldval;
    REAL_TYPE __newval;
    REAL_TYPE __temp = val;
    do
    {
        __oldval = *sum;
        __newval = __oldval + __temp;
    }
    while (!__sync_bool_compare_and_swap_8((INT_TYPE_OF_REAL_TYPE_SIZE *)&(*sum), (MyUnion){.__val = __oldval}.__addr, (MyUnion){.__val = __newval}.__addr));

#else

#error "You have to choose a valid implementation of 'compute_atomic_reduction'"
#endif
}

int main(int argc, char *argv[])
{
    REAL_TYPE res = 0;
    double init = omp_get_wtime();
    #pragma omp parallel
    {
        for(int i = 0; i < num_iterations; ++i)
        {
          compute_atomic_reduction(q*i, &res);
        }
    }
    double end = omp_get_wtime();
    printf("bin, %s, val, %lf, time, %lf\n",argv[0], res, end  - init);
}
