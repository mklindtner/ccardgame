#include "headers.h"
#include <stdlib.h>

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

card **generate_cards(int nothing)
{
    int one_color = 13;
    card **prev = (card **)malloc(sizeof(card));
    push(prev, 1, COLOR::SPADE);
    //start 1-off
    for (int i = 1; i < 51; i++)
    {
        if (i < one_color)
        {
            prev = push(prev, i + 1, COLOR::SPADE); //(new insertion) -> null
        }
        else if (i < one_color * 2)
        {
            prev = push(prev, i + 1, COLOR::HEARTS); //(new insertion) -> null
        }
        else if (i < one_color * 3)
        {
            prev = push(prev, i + 1, COLOR::DIAMONDS); //(new insertion) -> null
        }
        else
        {
            prev = push(prev, i + 1, COLOR::CLOVER); //(new insertion) -> null
        }
    }
    return prev;
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