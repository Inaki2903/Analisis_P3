/**
 *
 * Descripcion: Header file for time measurement functions (adaptado a búsquedas)
 *
 * Fichero: times.h
 * Autor: Carlos Aguirre.
 * Version: 1.2
 * Fecha: 2025
 *
 */

#ifndef TIMES_H
#define TIMES_H

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

#include "permutations.h"
#include "search.h"
#include <stdlib.h>
#include <stdio.h>

/* type definitions */
typedef struct time_aa {
  int N;           /* tamaño del diccionario */
  int n_elems;     /* número total de búsquedas (N * n_times) */
  double time;     /* tiempo medio por búsqueda */
  double average_ob; /* número medio de OB */
  int min_ob;      /* mínimo de OB */
  int max_ob;      /* máximo de OB */
} TIME_AA, *PTIME_AA;

short average_search_time(pfunc_search method,
                          pfunc_key_generator generator,
                          int order, int N,
                          int n_times,
                          PTIME_AA ptime);

short generate_search_times(pfunc_search method,
                            pfunc_key_generator generator,
                            int order, char* file,
                            int num_min, int num_max,
                            int incr, int n_times);

short save_time_table(char* file, PTIME_AA ptime, int n_times);

#endif

