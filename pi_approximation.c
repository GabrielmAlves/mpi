#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
	int rank, size, n, i;
	double PI25DT = 3.141592653589793238462643;
	double h, my_pi, pi, sum, x;
	
	sum = 0.0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		printf("Insira o numero de intervalos n: \n");
		scanf("%d", &n);
	}
	
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	h = 1.0/(double) n;	

	for (i = rank + 1; i <= n; i += size) {
		x = h*((double) i - 0.5);
		sum += 4.0 / (1 + x*x);
	}

	my_pi = h*sum;

	MPI_Reduce(&my_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("PI eh aproximadamente %.16f - O erro foi de %.16f\n", 
			pi, 
			fabs(pi - PI25DT));
	}
	
	MPI_Finalize();

}
