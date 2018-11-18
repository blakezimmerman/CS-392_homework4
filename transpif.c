#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

// Check if string input is power of 2
int is_power_of_two(char *val)
{
  int num = atoi(val);
  return (ceil(log2(num)) == floor(log2(num)));
}

int main(int argc, char **argv)
{
  // Verify command line arguments
  if (argc != 4)
  {
    fprintf(stderr, "Wrong number of command-line arguments\n");
    fprintf(stderr, "Usage: %s <matrix_height> <matrix_width> <block_width>\n", argv[0]);
    return -1;
  }

  if (!is_power_of_two(argv[3]))
  {
    fprintf(stderr, "block_width must be a power of 2\n");
    return -1;
  }

  int matrix_height = atoi(argv[1]);
  int matrix_width = atoi(argv[2]);
  int block_width = atoi(argv[3]);

  struct timeval tvalBefore, tvalAfter;

  // Allocate matrices
  float *input = (float *)malloc(matrix_height * matrix_width * sizeof(float));
  float *output = (float *)malloc(matrix_height * matrix_width * sizeof(float));

  // Seed pseudo-random number generator
  srand((unsigned int)time(NULL));

  // Fill matrix with random floats (-100 - 100)
  for (int i = 0; i < matrix_height * matrix_width; i++)
  {
    input[i] = ((float)rand()) / RAND_MAX * 200 - 100;
  }

  // Get starting time
  gettimeofday(&tvalBefore, NULL);

  // Peform Block-Transpose
  for (int i = 0; i < matrix_height; i += block_width)
  {
    for (int j = 0; j < matrix_width; j += block_width)
    {
      for (int k = i; k < i + block_width; ++k)
      {
        for (int l = j; l < j + block_width; ++l)
        {
          if (i < matrix_height && j < matrix_width)
          {
            output[k + l * matrix_height] = input[l + k * matrix_width];
          }
        }
      }
    }
  }

  // Get ending time
  gettimeofday(&tvalAfter, NULL);

  // Report execution time
  printf("Time in microseconds: %ld microseconds\n",
         ((tvalAfter.tv_sec - tvalBefore.tv_sec) * 1000000L + tvalAfter.tv_usec) - tvalBefore.tv_usec);

  // Clean up and end program
  free(input);
  free(output);
  return 0;
}