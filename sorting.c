/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include <stddef.h>

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
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
/* Function: SelectSort    Date: 26/09/2025        */
/* Your comment                                    */
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









