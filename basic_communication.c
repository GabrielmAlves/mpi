#include <mpi.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]) {
	int rank;
	int tag = 18;
	int sent_result;
	int received_result;
	int received_size;
	char message[20];
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		strcpy(message, "Pingo");
		sent_result = MPI_Send(message, 
				   strlen(message) + 1, 
                                   MPI_CHAR, 
                                   1, 
                                   tag, 
                                   MPI_COMM_WORLD);
		if (sent_result != MPI_SUCCESS) {
			fprintf(stderr, "MPI_Send falhou com codigo de erro %d\n", sent_result);
			MPI_Abort(MPI_COMM_WORLD, 1);
		} else {
			printf("Processo 0 enviou a mensagem - %s - para o processo 1\n", message);
		}
	}
	else if (rank == 1) {
		received_result = MPI_Recv(message,
					   sizeof(message), 
					   MPI_CHAR, 
					   0, tag, 
					   MPI_COMM_WORLD, 
					   &status);

		if (received_result != MPI_SUCCESS) {
			fprintf(stderr, "MPI_Recv falhou com codigo de erro %d\n", received_result);
			MPI_Abort(MPI_COMM_WORLD, 1);
		} else {
			MPI_Get_count(&status, MPI_CHAR, &received_size);
			printf("Processo 1 recebeu mensagem - %s - com tamanho %d do processo 0\n", 
				message, received_size);
		}
	}
	MPI_Finalize();
}
