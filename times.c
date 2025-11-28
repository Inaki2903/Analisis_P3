#define _POSIX_C_SOURCE 200809L
#include "times.h"
#include <time.h>

#define NS_PER_S 1000000000

short average_search_time(pfunc_search method,
                          pfunc_key_generator generator,
                          int order, int N,
                          int n_times,
                          PTIME_AA ptime)
{
    PDICT dict = NULL;
    int *perm = NULL, *keys;
    int avg_ob, min_ob = __INT_MAX__, max_ob = __WINT_MIN__, ob_act, ob_tot = 0, i, pos;
    struct timespec time_init, time_fin;
    double avg_time;

    if (method == NULL || generator == NULL || (order != NOT_SORTED && order != NOT_SORTED) || N <= 0 || n_times <= 0)
    {
        printf("Invalid parameters");
        return ERR;
    }

    dict = init_dictionary(N, (char)order);
    perm = generate_perm(N);
    massive_insertion_dictionary(dict, perm, N);

    if (!(keys = (int *)malloc(sizeof(int) * n_times * N)))
    {
        printf("Allocation error");
        return ERR;
    }

    generator(keys, n_times * N, N);

    clock_gettime(CLOCK_REALTIME, &time_init);
    for (i = 0; i < N * n_times; i++)
    {
        ob_act = search_dictionary(dict, keys[i], &pos, method);
        if (ob_act > max_ob)
        {
            max_ob = ob_act;
        }
        if (ob_act < min_ob)
        {
            min_ob = ob_act;
        }

        ob_tot += ob_act;
    }
    clock_gettime(CLOCK_REALTIME, &time_fin);

    avg_time = (time_fin.tv_sec - time_init.tv_sec + (time_fin.tv_nsec - time_init.tv_nsec) / NS_PER_S) / (N * n_times);
    avg_ob = ob_tot / (N * n_times);

    ptime->average_ob = avg_ob;
    ptime->max_ob = max_ob;
    ptime->min_ob = min_ob;
    ptime->N = N;
    ptime->n_elems = n_times;
    ptime->time = avg_time;

    free(perm);
    free(keys);
    free_dictionary(dict);
    return OK;
}

short generate_search_times(pfunc_search method,
                            pfunc_key_generator generator,
                            int order, char *file,
                            int num_min, int num_max,
                            int incr, int n_times)
{
    int n_incrs, i, j, res;
    PTIME_AA results = NULL;

    if(method == NULL || generator == NULL || (order != NOT_SORTED && order != SORTED) || file == NULL || num_min <= 0 || num_max <= 0 || num_min > num_max
        || incr <= 0 || n_times <= 0)
    {
        return ERR;
    }

    n_incrs = (num_max - num_min + 1)/incr;
    
    if(!(results = (PTIME_AA)malloc(sizeof(TIME_AA) * n_incrs)))
    {
        return ERR;
    }

    for(i = num_min, j = 0; i <= num_max; i += incr, j++)
    {
        res = average_search_time(method, generator, order, i, n_times, &results[j]);
        if(res == ERR)
        {
            return ERR;
        }
    }

    res = save_time_table(file, results, n_incrs);
    if(res == ERR)
    {
        return ERR;
    }

    free(results);
    return OK;
}

short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  int i;
  FILE *f = NULL;

  if (file == NULL || ptime == NULL ||  n_times <= 0)
  {
    return ERR;
  }

  if(!(f = fopen(file, "w")))
  {
    return ERR;
  }

  fprintf(f, "+------------+------------+------------+------------+------------+\n");
  fprintf(f, "|  Tamaño(N) |    Time    | OBPromedio |  OBMinimo  |  OBMaximo  |\n");

  for(i = 0; i < n_times; i++)
  {
    fprintf(f, "+------------+------------+------------+------------+------------+\n");
    fprintf(f, "|%-12d|%-10.10f|%-12.4f|%-12d|%-12d|\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob);
  }

  fprintf(f, "+------------+------------+------------+------------+------------+\n");
  fclose(f);
  return OK;
}