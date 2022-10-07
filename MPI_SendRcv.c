// MPI
#include <mpi.h>
#include <stdio.h>

#define ROTULO 42

int main(int argc, char **argv) 
{
  // Initialize the MPI environment
  MPI_Init(&argc, &argv);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  float data[9] = {1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5};

  // 0->2
  // 3->5
  // 6->8

  if (world_rank == 0) 
  {
    float bufferRcv[3];
    float temp1[3];
    float temp2[3];
    float temp3[3];

    int i = 0;
    int j = 0;
    for (i = 0; i < 3; ++i)
    {
      temp1[i] = data[j];
      ++j;
    }

    for (i = 0; i < 3; ++i)
    {
      temp2[i] = data[j];
      ++j;
    }

    for (i = 0; i < 3; ++i)
    {
      temp3[i] = data[j];
      ++j;
    }
    
    MPI_Send(&temp1, 3, MPI_INT, 1, ROTULO, MPI_COMM_WORLD);
    MPI_Send(&temp2, 3, MPI_INT, 2, ROTULO, MPI_COMM_WORLD);
    MPI_Send(&temp3, 3, MPI_INT, 3, ROTULO, MPI_COMM_WORLD);
    
    printf("\nProcesso 0 enviou valores... \n");

    MPI_Recv(&bufferRcv[0], 1, MPI_INT, 1, ROTULO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Recv(&bufferRcv[1], 1, MPI_INT, 2, ROTULO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Recv(&bufferRcv[2], 1, MPI_INT, 3, ROTULO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf ("\n\n\nProcesso 0 recebeu Maiores Locais: ");

    for (i = 0; i < 3; ++i)
      printf ("%f, ", bufferRcv[i]);
    printf ("\n");

  
    float maiorLocal = bufferRcv[0];
    for (i = 0; i < 3; ++i)
    {
      if (bufferRcv[i] > maiorLocal)
        maiorLocal = bufferRcv[i];
    }
    printf ("\nO MAIORAL -> - %f\n", maiorLocal);  
  } 
  else if (world_rank == 1) 
  {
    float buffer[3];
    
    MPI_Recv(&buffer, 3, MPI_INT, 0, ROTULO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Processo 1 Recebeu - ");
    int i;
    for (i = 0; i < 3; ++i)
      printf ("%f, ", buffer[i]);
    printf ("\n");

    float maiorLocal = buffer[0];
    for (i = 0; i < 3; ++i)
    {
      if (buffer[i] > maiorLocal)
        maiorLocal = buffer[i];
    }
    printf ("Maior do processo 1 - %f\n", maiorLocal);

    MPI_Send(&maiorLocal, 1, MPI_INT, 0, ROTULO, MPI_COMM_WORLD);
  }  
  else if (world_rank == 2) 
  {
    float buffer[3];
    
    MPI_Recv(&buffer, 3, MPI_INT, 0, ROTULO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Processo 2 Recebeu - ");
    int i;
    for (i = 0; i < 3; ++i)
      printf ("%f, ", buffer[i]);
    printf ("\n");

    float maiorLocal = buffer[0];
    for (i = 0; i < 3; ++i)
    {
      if (buffer[i] > maiorLocal)
        maiorLocal = buffer[i];
    }
    printf ("Maior do processo 2 - %f\n", maiorLocal);

    MPI_Send(&maiorLocal, 1, MPI_INT, 0, ROTULO, MPI_COMM_WORLD);
  }  
  else if (world_rank == 3) 
  {
    float buffer[3];
    
    MPI_Recv(&buffer, 3, MPI_INT, 0, ROTULO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Processo 3 Recebeu - ");
    int i;
    for (i = 0; i < 3; ++i)
      printf ("%f, ", buffer[i]);
    printf ("\n");

    float maiorLocal = buffer[0];
    for (i = 0; i < 3; ++i)
    {
      if (buffer[i] > maiorLocal)
        maiorLocal = buffer[i];
    }
    printf ("Maior do processo 3 - %f\n", maiorLocal);

    MPI_Send(&maiorLocal, 1, MPI_INT, 0, ROTULO, MPI_COMM_WORLD);    
  }  
  else 
  {
    printf("NA\n");
  }

  // Finalize the MPI environment.
  MPI_Finalize();
}

// PRONTO FUNCIONA