#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 100

int main(int argc, char* argv[]){
	int rank, size;
	int global_array[N];
	int local_array[N/4];
	int local_sum = 0;
	int global_sum = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0){
		for (int i = 0; i < N; ++i) {
			global_array[i] = i + 1;
		}
	}

	MPI_Scatter(global_array,
		    N/size, 
		    MPI_INT, 
                    local_array, 
                    N/size, 
                    MPI_INT, 
		    0,
		    MPI_COMM_WORLD);

	for (int i = 0; i < N/size; ++i) {
		local_sum += local_array[i];
	}

	MPI_Gather(&local_sum, 1, MPI_INT, global_array, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	if (rank == 0) {
		for (int i = 0; i < size; ++i) {
			global_sum += global_array[i];
		}
		printf("Soma total: %d\n", global_sum);
	}

	MPI_Finalize();

	return 0;
}
