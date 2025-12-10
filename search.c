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

/***************************************************/
/* Function: init_dictionary Date:                 */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Initializes an empty dictionary                 */
/*                                                 */
/* Input:                                          */
/* size: size of the dictionary                    */
/* order: wether the dictionary is ordered or not  */
/* Output:                                         */
/* pointer to the new dictionary if everything     */
/* went right, NULL otherwise                      */
/***************************************************/
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

/***************************************************/
/* Function: free_dictionary Date:                 */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Frees the memory of a given dictionary          */
/*                                                 */
/* Input:                                          */
/* pdict: pointer to the dictionary to be freed    */
/***************************************************/
void free_dictionary(PDICT pdict)
{
    if (pdict == NULL)
        return;

    if (pdict->table != NULL)
        free(pdict->table);

    free(pdict);
}

/***************************************************/
/* Function: insert_dictionary Date:               */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Inserts a new element into a dictionary         */
/*                                                 */
/* Input:                                          */
/* pdict: dictionary where the key will be inserted*/
/* key: the key to be inserted                     */
/* Output:                                         */
/* OB's if everything went right, ERR otherwise    */
/***************************************************/
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

/***************************************************/
/* Function: massive_insertion_dictionary Date:    */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Inserts multiple elements into a dictionary     */
/*                                                 */
/* Input:                                          */
/* pdict: pointer to the dictionary where the keys */
/*        will be inserted into                    */
/* keys: array with the keys to be inserted        */
/* n_keys: number of keys to be inserted           */
/* Output:                                         */
/* OB's if everything went okay, ERR otherwise     */
/***************************************************/
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

/***************************************************/
/* Function: search_dictionary Date:               */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Searches through a dictionary for a key using a */
/* given method                                    */
/*                                                 */
/* Input:                                          */
/* pdict: pointer to the dictionary that'll be used*/
/* key: key to be searched for                     */
/* ppos: position of the key that has been searched*/
/* for                                             */
/* method: the function that'll be used for the    */
/* search                                          */
/* Output:                                         */
/* NOT_FOUND if the key wasn't found, ERR if       */
/* something went wrong or OB's if everything went */
/* okay                                            */
/***************************************************/
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


/***************************************************/
/* Function: bin_search      Date:                 */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Searches for a key using binary search          */
/*                                                 */
/* Input:                                          */
/* table: array that's being searched              */
/* F: first index of the range that's being        */
/* searched                                        */
/* L: last index of the range that's being serached*/
/* key: the key that's being searched for          */
/* ppos: the position of the key if found          */
/* Output:                                         */
/* NOT_FOUND if the key wasn't found, ERR if       */
/* something went wrong or OB's if everything went */
/* okay                                            */
/***************************************************/
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

/***************************************************/
/* Function: lin_search      Date:                 */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Searches for a key using linear search          */
/*                                                 */
/* Input:                                          */
/* table: array that's being searched              */
/* F: first index of the range that's being        */
/* searched                                        */
/* L: last index of the range that's being serached*/
/* key: the key that's being searched for          */
/* ppos: the position of the key if found          */
/* Output:                                         */
/* NOT_FOUND if the key wasn't found, ERR if       */
/* something went wrong or OB's if everything went */
/* okay                                            */
/***************************************************/
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

/***************************************************/
/* Function: lin_auto_search      Date:            */
/* Authors: Iñaki Lopez                            */
/*                                                 */
/* Searches for a key using linear auto search     */
/*                                                 */
/* Input:                                          */
/* table: array that's being searched              */
/* F: first index of the range that's being        */
/* searched                                        */
/* L: last index of the range that's being serached*/
/* key: the key that's being searched for          */
/* ppos: the position of the key if found          */
/* Output:                                         */
/* NOT_FOUND if the key wasn't found, ERR if       */
/* something went wrong or OB's if everything went */
/* okay                                            */
/***************************************************/
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



