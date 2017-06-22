GCC=gcc
CFLAGS=-std=c99 -fopenmp -O3

all: gcc_parallel_with_atomic \
     gcc_parallel_with_builtin_with_extra_mem_fence \
     gcc_parallel_with_builtin_with_volatile \
     gcc_parallel_with_builtin

gcc_parallel_with_atomic: *.c
	$(GCC) -DVERSION=1 -o $@ $(CFLAGS) $?

gcc_parallel_with_builtin_with_extra_mem_fence: *.c
	$(GCC) -DVERSION=2 -o $@ $(CFLAGS) $?

gcc_parallel_with_builtin_with_volatile: *.c
	$(GCC) -DVERSION=3 -o $@ $(CFLAGS) $?

gcc_parallel_with_builtin: *.c
	$(GCC) -DVERSION=4 -o $@ $(CFLAGS) $?

run:
	echo "-----------------------------------------------------------------"
	OMP_NUM_THREADS=1 ./gcc_parallel_with_atomic
	OMP_NUM_THREADS=1 ./gcc_parallel_with_builtin_with_extra_mem_fence
	OMP_NUM_THREADS=1 ./gcc_parallel_with_builtin_with_volatile
	OMP_NUM_THREADS=1 ./gcc_parallel_with_builtin
	echo "-----------------------------------------------------------------"
	./gcc_parallel_with_atomic
	./gcc_parallel_with_builtin_with_extra_mem_fence
	./gcc_parallel_with_builtin_with_volatile
	./gcc_parallel_with_builtin
	echo "-----------------------------------------------------------------"

clean:
	rm -f *.o gcc_parallel*
