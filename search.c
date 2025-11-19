/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
    PDICT pdict;

    if (size <= 0) 
        return NULL;

    pdict = (PDICT) malloc(sizeof(DICT));
    if (pdict == NULL)
        return NULL;

    pdict->table = (int *) malloc(size * sizeof(int));
    if (pdict->table == NULL) {
        free(pdict);
        return NULL;
    }
    pdict->size = size;
    pdict->n_data = 0;
    pdict->order = order;

    return pdict;
}


void free_dictionary(PDICT pdict)
{
    if (pdict == NULL)
        return;

    if (pdict->table != NULL)
        free(pdict->table);

    free(pdict);
}


int insert_dictionary(PDICT pdict, int key)
{
    int j, A;
    int ob = 0; 

    if (pdict == NULL || pdict->n_data >= pdict->size)
        return ERR;

    if (pdict->order == NOT_SORTED) {
        pdict->table[pdict->n_data] = key;
        pdict->n_data++;
        ob++;  
        return ob;
    }

    pdict->table[pdict->n_data] = key;
    ob++;   

    A = key;
    j = pdict->n_data - 1;

    while (j >= 0 && pdict->table[j] > A) {
        ob++; 
        pdict->table[j + 1] = pdict->table[j];
        j--;
    }

    ob++;

    pdict->table[j + 1] = A;
    pdict->n_data++;

    return ob;
}


int massive_insertion_dictionary (PDICT pdict, int *keys, int n_keys)
{
    int i;
    int ob_total = 0;
    int ob;

    if (pdict == NULL || keys == NULL || n_keys < 0)
        return ERR;

    for (i = 0; i < n_keys; i++) {
        ob = insert_dictionary(pdict, keys[i]);
        if (ob == ERR)
            return ERR;

        ob_total += ob;
    }

    return ob_total;
}


int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
    if (pdict == NULL || pdict->table == NULL || method == NULL)
        return ERR;

    if (pdict->n_data == 0) {
        if (ppos != NULL)
            *ppos = NOT_FOUND;
        return NOT_FOUND;
    }

    return method(pdict->table, 0, pdict->n_data - 1, key, ppos);
}



int bin_search(int *table, int F, int L, int key, int *ppos)
{
    int inf = F;
    int sup = L;
    int mid;
    int ob = 0;

    if (table == NULL || ppos == NULL || F < 0 || L < F)
        return ERR;

    while (inf <= sup) {

        mid = (inf + sup) / 2;

        ob++; 

        if (table[mid] == key) {
            *ppos = mid;
            return ob;
        }

        ob++;

        if (table[mid] > key) {
            sup = mid - 1;
        } else {
            inf = mid + 1;
        }
    }

    *ppos = NOT_FOUND;
    return NOT_FOUND;
}


int lin_search(int *table, int F, int L, int key, int *ppos)
{
    int i;
    int ob = 0;   

    if (table == NULL || ppos == NULL || F < 0 || L < F)
        return ERR;

    for (i = F; i <= L; i++) {
        ob++;  

        if (table[i] == key) {
            *ppos = i;
            return ob;
        }
    }

    *ppos = NOT_FOUND;
    return NOT_FOUND;
}


int lin_auto_search(int *table, int F, int L, int key, int *ppos)
{
    int i, tmp;
    int ob = 0;  

    if (table == NULL || ppos == NULL || F < 0 || L < F)
        return ERR;

    for (i = F; i <= L; i++) {
        ob++;  

        if (table[i] == key) {

           
            if (i > F) {
                tmp = table[i];
                table[i] = table[i - 1];
                table[i - 1] = tmp;

                *ppos = i - 1;
            } else {
                
                *ppos = F;
            }

            return ob;
        }
    }

    *ppos = NOT_FOUND;
    return NOT_FOUND;
}



