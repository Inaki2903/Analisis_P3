#define _POSIX_C_SOURCE 200809L

#include "times.h"
#include "permutations.h"
#include "search.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

enum { NS_PER_SECOND = 1000000000 };

short average_search_time(pfunc_search method,
                          pfunc_key_generator generator,
                          int order, int N,
                          int n_times,
                          PTIME_AA ptime)
{
    PDICT pdict = NULL;
    int *perm = NULL;
    int *keys = NULL;
    int total_keys;
    int i;
    int ob, pos;
    int min_ob, max_ob;
    long total_ob;
    struct timespec start, finish;
    double elapsed;

    if (!method || !generator || !ptime || N <= 0 || n_times <= 0)
        return ERR;

    ptime->N = N;
    total_keys = N * n_times;
    total_ob = 0;

    pdict = init_dictionary(N, (char)order);
    if (!pdict)
        return ERR;

    perm = generate_perm(N);
    if (!perm) {
        free_dictionary(pdict);
        return ERR;
    }

    if (massive_insertion_dictionary(pdict, perm, N) == ERR) {
        free(perm);
        free_dictionary(pdict);
        return ERR;
    }

    keys = (int*) malloc(sizeof(int) * total_keys);
    if (!keys) {
        free(perm);
        free_dictionary(pdict);
        return ERR;
    }

    generator(keys, total_keys, N);

    clock_gettime(CLOCK_REALTIME, &start);

    min_ob = 0;
    max_ob = 0;

    for (i = 0; i < total_keys; i++) {

        ob = search_dictionary(pdict, keys[i], &pos, method);

        if (ob == ERR) {
            free(keys);
            free(perm);
            free_dictionary(pdict);
            return ERR;
        }

        if (ob == NOT_FOUND)
            ob = 0;

        total_ob += ob;

        if (i == 0) {
            min_ob = ob;
            max_ob = ob;
        } else {
            if (ob < min_ob) min_ob = ob;
            if (ob > max_ob) max_ob = ob;
        }
    }

    clock_gettime(CLOCK_REALTIME, &finish);

    elapsed = (finish.tv_sec - start.tv_sec)
            + (finish.tv_nsec - start.tv_nsec) / (double)NS_PER_SECOND;

    ptime->n_elems = total_keys;
    ptime->time = elapsed / total_keys;
    ptime->average_ob = (double) total_ob / total_keys;
    ptime->min_ob = min_ob;
    ptime->max_ob = max_ob;

    free(keys);
    free(perm);
    free_dictionary(pdict);

    return OK;
}

short generate_search_times(pfunc_search method,
                            pfunc_key_generator generator,
                            int order, char* file,
                            int num_min, int num_max,
                            int incr, int n_times)
{
    int count;
    int i, N;
    PTIME_AA results;

    if (!method || !generator || !file ||
        num_min <= 0 || num_max < num_min || incr <= 0 || n_times <= 0)
        return ERR;

    count = ((num_max - num_min) / incr) + 1;

    results = (PTIME_AA) malloc(sizeof(TIME_AA) * count);
    if (!results)
        return ERR;

    N = num_min;

    for (i = 0; i < count; i++) {

        if (average_search_time(method, generator, order, N,
                                n_times, &results[i]) == ERR) {
            free(results);
            return ERR;
        }

        N += incr;
    }

    if (save_time_table(file, results, count) == ERR) {
        free(results);
        return ERR;
    }

    free(results);
    return OK;
}

short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
    FILE *f;
    int i;

    if (!file || !ptime || n_times <= 0)
        return ERR;

    f = fopen(file, "w");
    if (!f)
        return ERR;

    fprintf(f, "+------------+------------+------------+------------+------------+\n");
    fprintf(f, "|  Tamaño(N) |    Time    | OBPromedio |  OBMinimo  |  OBMaximo  |\n");

    for (i = 0; i < n_times; i++) {
        fprintf(f, "+------------+------------+------------+------------+------------+\n");
        fprintf(f, "|%-12d|%-12.8f|%-12.4f|%-12d|%-12d|\n",
                ptime[i].N,
                ptime[i].time,
                ptime[i].average_ob,
                ptime[i].min_ob,
                ptime[i].max_ob);
    }

    fprintf(f, "+------------+------------+------------+------------+------------+\n");

    fclose(f);

    return OK;
}
