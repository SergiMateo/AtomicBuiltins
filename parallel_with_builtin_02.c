#include<stdio.h>
#include<omp.h>

typedef union
{
  float __val;
  int __addr;
} MyUnion;

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
          {
            float __oldval;
            float __newval;
            float __temp = q;
            do
              {
                __oldval = *p;
                __newval = __oldval + __temp;
              }
            while (!__sync_bool_compare_and_swap_4((int *)&(*p), (MyUnion){.__val = __oldval}.__addr, (MyUnion){.__val = __newval}.__addr));
          }
        }
    }
    double end = omp_get_wtime();
    printf("bin, %s, val, %lf, time, %lf\n",argv[0], *p, end  - init);
}
