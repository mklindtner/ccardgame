#include "headers.h"
#include <stdlib.h>
#include <time.h>

//generate a random cardset
column *randomize_set()
{

    // column *cols = (column *) malloc(sizeof(column)*7);
    column *cols = (column *)malloc(sizeof(column) * 7);

    card cards[52];
    //generate all 7 columns
    for (int i = 0; i < 7; i++)
    {
        // card* c = (cards *) malloc(sizeof(card)*11);
        for (int j = 0; j < 11; j++)
        {
            card *c = (card *)malloc(sizeof(card));
        }

        // cols->id = i;
        // cols->cards = c;
    }

    //generate all 52 cards

    // int decksize = 52;
    // for(int i = 0; i < 52; i++)
    // {

    // }

    //insert cards randomly in each column
    return nullptr;
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

//generate_cards must be called first, ideally also shuffle_cards
void initialize_columns() {
    stack_card *sc = stack.cards_ref[0];
    column *c = cols->columns[0];
    stack_card *sc2 = stack.cards_ref[1];
    push_stack_to_column(sc, c);
    push_stack_to_column(sc2, c);
}

void push_stack_to_column(stack_card *sc, column *col)
{
    //new head
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

void generate_columns()
{
    //allocate struct
    cols = (scolumns *)malloc(sizeof(scolumns));
    //allocate array in struct
    (*cols).columns = (column **)malloc(sizeof(column) * COLUMNSIZE);

    for(int i = 0; i < COLUMNSIZE; i++)
    {
        (*cols).columns[i] = (column *)malloc(sizeof(column));        
    }

    //example
    //allocate element in array
    // (*cols).columns[0] = (column *)malloc(sizeof(column));

    //assign array and set next to null
    // column *c = (*cols).columns[0];
    // c->next = nullptr;
}

void swap_stack_card(int r1, int r2)
{

    //we could flex here and use xor instead
    stack_card *tmp = stack.cards_ref[r1];
    stack.cards_ref[r1] = stack.cards_ref[r2];
    stack.cards_ref[r2] = tmp;
}

//this is shuffle deck
//rand is unsafe, we should use libsodium but cba https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
void shuffle_stack()
{
    srand(time(NULL));
    //times we randomize array
    for (int i = 0; i < 5; i++)
    {
        //randomize entire array
        for (int j = 0; j < CARDSIZE; j++)
        {
            int r1 = rand() % CARDSIZE;
            int r2 = rand() % CARDSIZE;
            swap_stack_card(r1, r2);
        }
    }
}

void push_stack_card(int id, card *card)
{
    stack_card *scard = (stack_card *)malloc(sizeof(stack_card));
    scard->id = id;
    scard->card = card;
    scard->ondeck = false;
    stack.cards_ref[id] = scard;
    // printf("id input: %d\n", id);
    // printf("id: %d\n", scard->id);
    // printf("card0 id:%d\t card0 color:%d\n",card->number, card->color);
    // printf("addr: %p\n", stack.arr[id]);
}

card **generate_cards(int nothing)
{
    int one_color = 13;
    card **prev = (card **)malloc(sizeof(card));
    prev = push(prev, 1, COLOR::SPADE);
    push_stack_card(0, *prev);

    //start 1-off due to head in linked list
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

void write_columns()
{
    column_card *head = cols->columns[0]->head;
    printf("head: %p\t card num: %d\n", head, head->stack_card->card->number);
    printf("head next: %p\t card next num: %d\n",head->next, head->next->stack_card->card->number);
}

void write_stack()
{
    stack_card *t = stack.cards_ref[0];
    // printf("id: %d\tp:%p", t->id, t->card);
    for (int i = 0; i < CARDSIZE; i++)
    {
        stack_card *sc = stack.cards_ref[i];
        //card *c = sc->card;
        // printf("num: %d\t pointer: %p\t ondeck: %d\n", sc->id, sc->card, sc->ondeck);
        printf("cnum: %d\t ccolor: %d\t isturned: %d\n", sc->card->number, sc->card->color, sc->card->isturned);
    }
}

void write_name(card **col)
{
    card *cur = (*col);
    while (cur != NULL) //columns
    {
        printf("num: %d\t type: %d\t isturned: %d\t", cur->number, cur->color, cur->isturned);
        cur = cur->next;
    }
    printf("\n");
    return;
}

// card generate_card(int number, )
// {

// }