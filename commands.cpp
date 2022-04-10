#include "headers.h"

char **split_move(char *input, char *pos)
{
    printf("found at index: %ld\n", abs(input - pos));
    int s = strlen(input) - strlen(pos);
    int lsize = abs(s);
    char lhss[lsize];

    int diff = strlen(input) - strlen(pos);
    int d2 = (strlen(input) - diff) - 2; // lmao
    char rhss[d2];

    // get LHS of str
    for (int i = 0; i < lsize; i++)
    {
        printf("lhs char: %c\n", input[i]);
        lhss[i] = input[i];
    }

    printf("---\n");
    int idx = 0;

    // get RHS of str
    for (int j = lsize + 2; j < strlen(input); j++)
    {
        printf("rhs char: %c\n", input[j]);
        rhss[idx++] = input[j];
    }
    printf("\nsize of lhss: %d\n", lsize);
    printf("\nsize of rhss: %d\n", d2);
    printf("\nrhss:|%s|\n", rhss);
    printf("\nlhss:|%s|\n", lhss);

    char **splits = (char **)malloc(sizeof(char *)*2);
    splits[0] = rhss;
    splits[1] = lhss;
    return splits;
}