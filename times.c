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

        if(method == NULL ||generator == NULL || (order != "0" && order != "1")
            || N <= 0 || n_times <= 0)
        {
            printf("Invalid parameters");
            return ERR;
        }

        dict = init_dictionary(N, order);
        perm = generate_perm(N);
        massive_insertion_dictionary(dict, perm, N);

        if(!(keys = (int *)malloc(sizeof(int) * n_times * N)))
        {
            printf("Allocation error");
            return ERR;
        }

        generator(keys, n_times * N, N);

        clock_gettime(CLOCK_REALTIME, &time_init);
        for(i = 0; i < N * n_times; i++)
        {
            ob_act = search_dictionary(dict, keys[i], &pos, method);
            if (ob_act > max_ob)
            {
                max_ob = ob_act;
            } 
            else if(ob_act < min_ob)
            {
                min_ob = ob_act;
            }

            ob_tot += ob_act;
        }
        clock_gettime(CLOCK_REALTIME, &time_fin);

        avg_time = (time_fin.tv_sec - time_init.tv_sec + (time_fin.tv_nsec - time_init.tv_nsec)/NS_PER_S)/(N*n_times);
        avg_ob = ob_tot/(N*n_times);

        ptime->average_ob = avg_ob;
        ptime->max_ob = max_ob;
        ptime->min_ob = min_ob;
        ptime->N = N;
        ptime->n_elems = n_times;
        ptime->time = avg_time;

        return OK;
    }
