#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "omp_apps.h"

int main() {
	// Generate input vectors and destination vector
	double *x = gen_array(ARRAY_SIZE);
	double *y = gen_array(ARRAY_SIZE);
	double *z = (double*) malloc(ARRAY_SIZE*sizeof(double));

	// Test framework that sweeps the number of threads and times each run
	double start_time, run_time;
	int num_threads = omp_get_max_threads();	

	double naive_max;
	double adj_min = 100.0;
	double chunks_min = 100.0;

	double adj_total = 0.0;
	double chunks_total = 0.0;

	// naive benchmark
	omp_set_num_threads(num_threads);		
	start_time = omp_get_wtime();
	for(int j=0; j<REPEAT; j++){
		v_add_naive(x,y,z);
	}
	run_time = omp_get_wtime() - start_time;

	naive_max = run_time;

	printf("Naive: %d threads took %f seconds\n",num_threads,run_time);

  	for(int i=1; i<=num_threads; i++) {
		omp_set_num_threads(i);		
	  	start_time = omp_get_wtime();
		for(int j=0; j<REPEAT; j++){
			v_add_optimized_adjacent(x,y,z);
		}
		run_time = omp_get_wtime() - start_time;
		printf("Optimized adjacent: %d thread(s) took %f seconds\n",i,run_time);

    	if(!verify(x,y, v_add_optimized_adjacent)){
     		printf("v_add optimized adjacent does not match reference.\n");
      		return -1; 
    	}

    	if (run_time < adj_min) {
			adj_min = run_time;
		}
		adj_total += run_time;
  	}

  	if (adj_min * 2 > naive_max) {
  		printf("Fastest adjacent runtime didn't provide at least 2x speedup from naive benchmark.\n");
  		return -1;
  	}

  	for (int i=1; i<=num_threads; i++) {
		omp_set_num_threads(i);		
	  	start_time = omp_get_wtime();
		for(int j=0; j<REPEAT; j++){
			v_add_optimized_chunks(x,y,z);
		}
		run_time = omp_get_wtime() - start_time;
		printf("Optimized chunks: %d thread(s) took %f seconds\n",i,run_time);

    	if(!verify(x,y, v_add_optimized_chunks)){
      		printf("v_add optimized chunks does not match reference.\n");
      		return -1; 
    	}

    	if (run_time < chunks_min) {
			chunks_min = run_time;
		}
		chunks_total += run_time;
  	}

  	if (chunks_min * 2 > naive_max) {
  		printf("Fastest chunks runtime didn't provide at least 2x speedup from naive benchmark.\n");
  		return -1;
  	}

  	if (chunks_total > adj_total) {
  		printf("Chunks didn't have better performance than adjacent.\n");
  		return -1;
  	}

    printf("Congrats! All vector tests passed!\n");

  	return 0;
}