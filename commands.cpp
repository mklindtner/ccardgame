#include "headers.h"

void transfer_column(int from_column, int to_column, column_card *movecc)
{


    // last card in column
    if (movecc->next == nullptr)
    {
        movecc->next = cols->columns[to_column]->head;
        cols->columns[from_column]->head = nullptr;
        cols->columns[to_column]->head = movecc;
        return;
    }

    column_card *mvnext = movecc->next;
    movecc->next = cols->columns[to_column]->head;

    cols->columns[to_column]->head = cols->columns[from_column]->head;
    cols->columns[from_column]->head = mvnext;

    mvnext->stack_card->isturned = 1;
}

// lhss: C1:4C
// rhss: C2
// total: C1->F2, C1:A4->C2, F1->C3
void move_col_card(char **input)
{
    // LHS
    char *lhss = input[0];

    char lhstype = lhss[0];
    char cfnum = lhss[1];
    char cardinfo[3];
    memcpy(cardinfo, &lhss[3], sizeof(char) * 2);
    cardinfo[2] = '\0';

    int char_card_number = 0;
    int char_card_color = 1;
    int number_card = letter_to_int(cardinfo[char_card_number]);
    char *color_card = &cardinfo[char_card_color];
    printf("color_card :%d\n", cardinfo[char_card_color]);

    // RHS
    char *rhss = input[1];
    int to_column = atoi(&rhss[1]) - 1;
    char rhstype = rhss[0];

    // printf("lhs: %s\t lhstype: %c#\trhs: %s\t rhstype: %c#\n", lhss, lhstype ,rhss, rhstype);
    // from foundation
    if (!strncmp(&lhstype, "F", 1))
    {
        // printf("<here>\n");
        int from_foundation = atoi(&cfnum) - 1;
        // char *rhss = input[1];
        int to_column = atoi(&rhss[1]) - 1;

        // hånter nullpointer her
        column_card *fcnext = fonds->foundations[from_foundation]->head->next;

        // move foundation head to column head
        column_card *fc = fonds->foundations[from_foundation]->head;
        fc->next = cols->columns[to_column]->head;
        cols->columns[to_column]->head = fc;

        // foundation head move
        fonds->foundations[from_foundation]->head = fcnext;
        return;
    }

    // to foundation
    if (!strncmp(&rhstype, "F", 1))
    {
        int to_foundation = atoi(&rhss[1]) - 1;
        int from_column = atoi(&cfnum) - 1;
        // printf("to_foundation: %d\tfrom column:%d\n",to_foundation, from_column);

        column_card *ccnext = cols->columns[from_column]->head->next;
        column_card *cchead = cols->columns[from_column]->head;

        // cchead->next = fonds->foundations[to_foundation]->head;
        cchead->next = fonds->foundations[to_foundation]->head;
        fonds->foundations[to_foundation]->head = cchead;

        cols->columns[from_column]->head = ccnext;
        return;
    }

    int from_column = atoi(&cfnum) - 1;

    column_card *mv_ccard = find_card_payload(from_column, number_card, color_card);
    if (mv_ccard != nullptr)
    {
        if(!validate_move(to_column, mv_ccard->stack_card->card)) {
            transfer_column(from_column, to_column, mv_ccard);
        }        
    }

}

char validate_move(int to_column, card *cvalidate)
{
    card *chead = cols->columns[to_column]->head->stack_card->card;
    if((cvalidate->color != chead->color) && (chead->number-1 == cvalidate->number))
    {
        return 0;
    }
    sprintf(g_msg, "Illegal move");
    return 1;
}

char **split_move(char *input, char *pos)
{
    // printf("found at index: %ld\n", abs(input - pos));
    int s = strlen(input) - strlen(pos);
    int lsize = abs(s);
    char *lhss = (char *)malloc(lsize);

    int diff = strlen(input) - strlen(pos);
    int d2 = (strlen(input) - diff) - 2;
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
    char **splits = (char **)malloc(sizeof(char *) * 2);

    // C1->C2, C1->F1 = C1:A1->F1, F1->C1 = F1:A4->C1
    if (strlen(lhss) == 2)
    {
        char *new_lhss = lhss_pad_card(lhss);
        splits[0] = new_lhss;
        splits[1] = rhss;
        printf("splits from:|%s| to:|%s|\n",splits[0],splits[1]);
        return splits;
    }
    // printf("\nsize of lhss: %d\n", lsize);
    // printf("\nsize of rhss: %d\n", d2);
    // printf("\nrhss:|%s|\n", rhss);
    // printf("\nlhss:|%s|\n", lhss);

    splits[0] = lhss;
    splits[1] = rhss;
    // printf("final lhs: %s\trhs:%s\n",splits[0],splits[1]);

    return splits;
}

char *lhss_pad_card(char *lhss)
{
    // printf("lhss: %s\n", lhss);
    int fromcol = atoi(&lhss[1]) - 1;
    int cnum = cols->columns[fromcol]->head->stack_card->card->number;
    COLOR suit = cols->columns[fromcol]->head->stack_card->card->color;

    char *new_lhss = (char *)malloc(sizeof(char) * 20);
    char *cholor = (char *)malloc(sizeof(char) * 20);
    char cc[2];
    sprintf(cholor, "%s", color_to_string(suit));
    
    char const *ccnum = int_to_letter(cnum);
    snprintf(new_lhss, sizeof(new_lhss), "%s:%s%s", lhss, ccnum, cholor);

    // printf("|%s|\n", new_lhss);
    return new_lhss;
}