/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Iñaki Lopez
 * Version: 1.0
 *
 */


#include "sorting.h"
#include <stddef.h>

/***************************************************/
/* Function: average_search_time Date:             */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Orders the contents of array using InsertSort   */
/*                                                 */
/* Input:                                          */
/* array: the elements to be ordered               */
/* ip: first index of the range to be ordered      */
/* iu: last index of the range to be ordered       */
/* Output:                                         */
/* OBs if everything went right, ERR otherwise     */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
  int elem, i, j, counter;

  if (array == NULL || ip > iu || ip < 0 || iu < 0)
  {
    return ERR;
  }

  for (i = ip + 1, counter = 0; i <= iu; i++)
  {
    elem = array[i];
    j = i - 1;

    while (j >= ip && array[j] > elem) /*OB*/
    {
        counter++;
        array[j+1] = array[j];
        j--;
    }

    array[j+1] = elem;
  }

  return counter;
}


/***************************************************/
/* Function: average_search_time Date:             */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Sorts the contents of the array using BubbleSort*/
/*                                                 */
/* Input:                                          */
/* array: the array of numbers to be ordered       */
/* ip: the first index of the range to be ordered  */
/* iu: the last index of the range to be ordered   */
/* Output:                                         */
/* OBs if everything went right, ERR otherwise     */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{

  int swapped, j, i, aux, counter = 0;

  if(!(array))
  {
    return ERR;
  }

  if(ip == iu){
    return 0;
  }

  if (iu < ip)
  {
    return ERR;
  }

  i = iu;
  swapped = 1;

  while (i > ip && swapped == 1){
    swapped = 0;

    for (j = ip; j < iu; j++) {
      if (array[j] > array[j + 1]) { /*OB*/
          counter++;
          aux = array[j];
          array[j] = array[j + 1];
          array[j + 1] = aux;
          swapped = 1;
      }
    }

    i--;
  }

  return counter;
}









