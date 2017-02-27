GCC=gcc
MCC=mcc
CFLAGS=-std=c99 -fopenmp

all: gcc_parallel_with_atomic \
     gcc_parallel_with_builtin_01 \
     gcc_parallel_with_builtin_02 \
     mcc_parallel_with_atomic \
     mcc_parallel_with_builtin_01 \
     mcc_parallel_with_builtin_02

gcc_parallel_with_atomic: parallel_with_atomic.c
	$(GCC) -o $@ $(CFLAGS) $?

mcc_parallel_with_atomic: parallel_with_atomic.c
	$(MCC) -o $@ $(CFLAGS) $?

gcc_parallel_with_builtin_01: parallel_with_builtin_01.c
	$(GCC) -o $@ $(CFLAGS) $?

mcc_parallel_with_builtin_01: parallel_with_builtin_01.c
	$(MCC) -o $@ $(CFLAGS) $?

gcc_parallel_with_builtin_02: parallel_with_builtin_02.c
	$(GCC) -o $@ $(CFLAGS) $?

mcc_parallel_with_builtin_02: parallel_with_builtin_02.c
	$(MCC) -o $@ $(CFLAGS) $?

run:
	OMP_NUM_THREADS=1 ./gcc_parallel_with_atomic
	OMP_NUM_THREADS=1 ./mcc_parallel_with_atomic
	OMP_NUM_THREADS=1 ./gcc_parallel_with_builtin_01
	OMP_NUM_THREADS=1 ./mcc_parallel_with_builtin_01
	OMP_NUM_THREADS=1 ./gcc_parallel_with_builtin_02
	OMP_NUM_THREADS=1 ./mcc_parallel_with_builtin_02

clean:
	rm *.o gcc_parallel_with_atomic gcc_parallel_with_builtin_0[1,2] \
	       mcc_parallel_with_atomic mcc_parallel_with_builtin_0[1,2] -if
