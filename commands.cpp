#include "headers.h"

//lhss: C1:4C
//rhss: C2
void move_col_card(char **input)
{
    char *lhss = input[0];
    char *rhss = input[1];

    char lhstype = lhss[0]; 
    char cfnum = lhss[1];
    char cardinfo[3];
    memcpy(cardinfo, &lhss[3], sizeof(char)*2);
    cardinfo[2] = '\0'; //'4','h','\0',
    printf("cardinfo: %c\t%c\n", cardinfo[0], cardinfo[1]);
}


char **split_move(char *input, char *pos)
{
    // printf("found at index: %ld\n", abs(input - pos));
    int s = strlen(input) - strlen(pos);
    int lsize = abs(s);
    char *lhss = (char *)malloc(lsize);

    int diff = strlen(input) - strlen(pos);
    int d2 = (strlen(input) - diff) - 2; // lmao
    char *rhss = (char *)malloc(d2);

    // get LHS of str
    for (int i = 0; i < lsize; i++)
    {
        // printf("lhs char: %c\n", input[i]);
        lhss[i] = input[i];
    }

    // printf("---\n");
    int idx = 0;

    // get RHS of str
    for (int j = lsize + 2; j < strlen(input); j++)
    {
        // printf("rhs char: %c\n", input[j]);
        rhss[idx++] = input[j];
    }
    // printf("\nsize of lhss: %d\n", lsize);
    // printf("\nsize of rhss: %d\n", d2);
    // printf("\nrhss:|%s|\n", rhss);
    // printf("\nlhss:|%s|\n", lhss);

    char **splits = (char **)malloc(sizeof(char *)*2);
    splits[0] = lhss;
    splits[1] = rhss;
    return splits;
}