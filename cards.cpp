#include "headers.h"



void reversell()
{
    for (int i = 0; i < COLUMNSIZE; i++)
    {
        column_card *cc = cols->columns[i]->head;
        column_card *next = nullptr;
        column_card *prev = nullptr;
        while (cc != nullptr)
        {
            next = cc->next;
            // Reverse current node's pointer

            cc->next = prev;
            // Move pointers one position ahead.
            prev = cc;
            cc = next;
        }
        cols->columns[i]->head = prev;
    }
}

void rm_col_card(column_card *elem, int colid)
{
    column_card *cc = cols->columns[colid]->head;
    column_card *prev = nullptr;
    while (cc != elem)
    {
        prev = cc;
        cc = cc->next;
    }

    if (cc == cols->columns[colid]->head)
    {
        free(cc);
        return;
    }
    // remove element that's not header
    prev->next = cc->next;
    free(cc);
}

card **push(card **head_ref, int number, COLOR color)
{

    /* 1. allocate node */
    card *new_node = (card *)malloc(sizeof(card));

    /* 2. put in the data */
    new_node->number = number;
    new_node->color = color;    

    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);

    /* 4. move the head to point to the new node */
    (*head_ref) = new_node;
    return head_ref;
}

// col1 represents the number of column
int placearray[CARDSIZE] = {
    1, 2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    3, 4, 5, 6, 7,
    4, 5, 6, 7,
    5, 6, 7,
    6, 7,
    7};

// generate_cards must be called first, ideally also shuffle_cards
void initialize_columns()
{
    for (int i = 0; i < CARDSIZE; i++)
    {
        column_card *c = cols->columns[placearray[i] - 1];
        stack_card *sc = stack.cards_ref[i];
        push_stack_to_column(sc, c);
    }
}

void push_stack_to_column(stack_card *sc, column_card *col)
{
    // new head
    column_card *cc = (column_card *)malloc(sizeof(column_card));
    cc->stack_card = sc;
    cc->next = nullptr;
    column_card *tmp = nullptr;
    if (col->head != nullptr)
    {
        tmp = col->head;
        cc->next = tmp;
    }
    col->head = cc;
}

// make columns, no header made
void generate_columns()
{

    // allocate array in struct
    (*cols).columns = (column_card **)malloc(sizeof(column_card) * COLUMNSIZE);

    // (*copycols).columns = (column_card **)malloc(sizeof(column_card) * COLUMNSIZE);

    for (int i = 0; i < COLUMNSIZE; i++)
    {
        (*cols).columns[i] = (column_card *)malloc(sizeof(column_card));
        // (*copycols).columns[i] = (column_card *)malloc(sizeof(column_card));
    }
}

void swap_stack_card(int r1, int r2)
{

    // we could flex here and use xor instead
    stack_card *tmp = stack.cards_ref[r1];
    stack.cards_ref[r1] = stack.cards_ref[r2];
    stack.cards_ref[r2] = tmp;
}

// this is shuffle deck
// rand is unsafe, we should use libsodium but cba https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
void shuffle_stack()
{
    srand(time(NULL));
    // times we randomize array
    for (int i = 0; i < 5; i++)
    {
        // randomize entire array
        for (int j = 0; j < CARDSIZE; j++)
        {
            int r1 = rand() % CARDSIZE;
            int r2 = rand() % CARDSIZE;
            swap_stack_card(r1, r2);
        }
    }
}

void turn_card(stack_card *sc, bool isturned)
{
    sc->isturned = isturned;
}

void push_stack_card(int id, card *card)
{
    stack_card *scard = (stack_card *)malloc(sizeof(stack_card));
    scard->id = id;
    scard->card = card;
    scard->isturned = false;
    // scard->ondeck = false;
    stack.cards_ref[id] = scard;
}

card **generate_cards(int nothing)
{
    int one_color = 13;
    card **prev = (card **)malloc(sizeof(card));
    prev = push(prev, 1, COLOR::SPADE);
    push_stack_card(0, *prev);

    // start 1-off due to head in linked list
    for (int i = 1; i < CARDSIZE; i++)
    {
        if (i < one_color)
        {
            prev = push(prev, i + 1, COLOR::SPADE); //(new insertion) -> null
        }
        else if (i < one_color * 2)
        {
            prev = push(prev, (i + 1) - one_color, COLOR::HEARTS);
        }
        else if (i < one_color * 3)
        {
            prev = push(prev, (i + 1) - one_color * 2, COLOR::DIAMONDS);
        }
        else
        {
            prev = push(prev, (i + 1) - one_color * 3, COLOR::CLOVER);
        }
        push_stack_card(i, *prev);
    }
    return prev;
}

column_card *last_elem_col(int id)
{
    column_card *cc = cols->columns[id]->head;
    column_card *prev = nullptr;
    while (cc != nullptr)
    {
        prev = cc;
        cc = cc->next;
    }
    return prev;
}

// debugging writes
void write_single_column(int id)
{
    column_card *cc = cols->columns[id]->head;
    while (cc != nullptr)
    {
        printf("head: %p\t card num: %d\n", cc, cc->stack_card->card->number);
        cc = cc->next;
    }
}

void write_columns()
{
    for (int i = 0; i < COLUMNSIZE; i++)
    {
        column_card *head = cols->columns[i]->head;
        printf("col num: %d\thead: %p\t card num: %d\n", i, head, head->stack_card->card->number);
    }
}

void write_stack()
{
    stack_card *t = stack.cards_ref[0];
    for (int i = 0; i < CARDSIZE; i++)
    {
        stack_card *sc = stack.cards_ref[i];
        printf("cnum: %d\t ccolor: %d\t", sc->card->number, sc->card->color);
    }
}

void write_name(card **col)
{
    card *cur = (*col);
    while (cur != NULL) // columns
    {
        printf("num: %d\t type: %d\t ", cur->number, cur->color);
        cur = cur->next;
    }
    printf("\n");
    return;
}

// todo: fix naming: https://stackoverflow.com/questions/9907160/how-to-convert-enum-names-to-string-in-c
void write_card(card *card)
{

    printf("%d:%d", card->number, card->color);
}
