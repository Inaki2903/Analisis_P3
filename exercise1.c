/***********************************************/
/* Program: exercise1     Date:             */
/* Authors:                                    */
/*                                             */
/* Program that checks the correct behaviour of*/
/* linear and binary search                    */
/*                                             */
/* Input: Command line                         */
/*   -size <int>                               */
/*   -key <int>                                */
/*   -ordered (optional)                       */
/*   -method <lin|bin|auto>                    */
/***********************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "permutations.h"
#include "search.h"

int main(int argc, char** argv)
{
    int i, nob, pos;
    unsigned int key = 0, size = 0;
    char ordered = NOT_SORTED;
    pfunc_search method = lin_search;
    PDICT pdict;
    int *perm;

    srand(time(NULL));

    if (argc < 5) {
        fprintf(stderr, "Error in the input parameters:\n\n");
        fprintf(stderr, "%s -size <int> -key <int> [-ordered] -method <lin|bin|auto>\n", argv[0]);
        exit(-1);
    }

    printf("Pratice number 3, section 1\n");
    printf("Done by: Innaki_Lopez_Rocha, Daniel_Martin_Jaen\n");
    printf("Group: Your group\n");

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-size") == 0) {
            size = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-key") == 0) {
            key = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-ordered") == 0) {
            ordered = SORTED;
        }
        else if (strcmp(argv[i], "-method") == 0) {
            i++;
            if      (strcmp(argv[i], "lin")  == 0) method = lin_search;
            else if (strcmp(argv[i], "bin")  == 0) method = bin_search;
            else if (strcmp(argv[i], "auto") == 0) method = lin_auto_search;
            else {
                fprintf(stderr, "Unknown method %s. Use lin, bin or auto.\n", argv[i]);
                exit(-1);
            }
        }
        else {
            fprintf(stderr, "Parameter %s is invalid\n", argv[i]);
            exit(-1);
        }
    }


    pdict = init_dictionary(size, ordered);
    if (!pdict) {
        printf("Error: Dictionary could not be initialized\n");
        exit(-1);
    }


    perm = generate_perm(size);
    if (!perm) {
        printf("Error: No memory\n");
        free_dictionary(pdict);
        exit(-1);
    }


    nob = massive_insertion_dictionary(pdict, perm, size);
    if (nob == ERR) {
        printf("Error: Dictionary could not be created\n");
        free(perm);
        free_dictionary(pdict);
        exit(-1);
    }


    if (ordered == NOT_SORTED && method == bin_search) {
        printf("Error: binary search cannot be used on an unsorted table.\n");
        free(perm);
        free_dictionary(pdict);
        return -1;
    }

    nob = search_dictionary(pdict, key, &pos, method);
    if (nob >= 0) {
        printf("Key %d found in position %d in %d basic op.\n", key, pos, nob);
    }
    else if (nob == NOT_FOUND) {
        printf("Key %d not found in table\n", key);
    }
    else {
        printf("Error when searching the key %d\n", key);
    }

    free(perm);
    free_dictionary(pdict);

    return 0;
}


