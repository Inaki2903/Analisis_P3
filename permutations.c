/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>

/***************************************************/
/* Function: random_num Date:                      */
/* Authors: Daniel Martín                          */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  unsigned long range, limit, r;
  const unsigned long MAX = (unsigned long)RAND_MAX;
  const unsigned long N = MAX + 1UL;

  range = (unsigned long)(sup - inf + 1);
  if (range == 0)
  {
    return inf;
  }

  limit = MAX - (N % range);

  do {
    r = (unsigned long)rand();
  }while (r > limit);

  return inf + (int)r%range;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors: Daniel Martín                          */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int *arr1 = NULL, i, inter, rand;

  if (N <= 0)
  {
    return NULL;
  }

  if(!(arr1 = (int *)malloc(N * sizeof(int))))
  {
    return NULL;
  }

  for(i = 0; i < N; i++)
  {
    arr1[i] = i+1;
  }

  for(i = 0; i < N; i++)
  {
    rand = random_num(i+1, N);
    inter = arr1[i];
    arr1[i] = arr1[rand-1];
    arr1[rand-1] = inter;
  }

  return arr1;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors: Daniel Martín                          */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int **perm_arr = NULL, i;

  if(n_perms <= 0 || N <= 0)
  {
    return NULL;
  }

  if(!(perm_arr = (int **)malloc(sizeof(int **) * n_perms)))
  {
    return NULL;
  }

  for(i = 0; i < n_perms; i++)
  {
    perm_arr[i] = generate_perm(N);
  }

  return perm_arr;

}

/***************************************************/
/* Function: free_permutations Date:               */
/* Authors: Daniel Martín                          */
/*                                                 */
/* Function that frees a given array of perms      */
/*                                                 */
/* Input:                                          */
/* int perm_arr: array to be freed                 */
/* int N: number of perms in the array             */
/* Output:                                         */
/* OK if everything went fine, ERR otherwise       */
/***************************************************/
short free_permutations(int **perm_arr, int n_perms)
{
  int i;

  if(perm_arr == NULL || n_perms <= 0)
  {
    return ERR;
  }

  for(i = 0; i < n_perms; i++)
  {
    free(perm_arr[i]);
  }

  free(perm_arr);
  return OK;
}