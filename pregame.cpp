#ifndef _PREGAME
#define _PREGAME
#include "headers.h"



void pregame_layout_foundation(char *input, bool show_cards)
{
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");    
    pregame_layout_cards(show_cards);
    
    printf("\n");
    msg_bottom_left_last_message(input);
    msg_bottom_left_message(g_msg);
    msg_bottom_left_input(empty);
}

void pregame_layout_cards(bool show_cards)
{
    int f = 0; 
    for (int i = 0; i < PREGAME_ROWSIZE; i++)
    {

        for (int j = 0; j < COLUMNSIZE; j++)
        {
            if (i * 7 + j < CARDSIZE)
            {
                card *c = stack.cards_ref[i * 7 + j]->card;
                char const *suit = int_to_suit(c->color);
                char const *num = int_to_letter(c->number);
                if(show_cards) {
                    printf("%s%s\t", num, suit);
                }
                else {
                    printf("[]\t");
                }
            }
        }
        if (i == 0 || i == 2 || i == 4 || i == 6)
        {
            printf("\t\t");
            printf("[]");
            // layout_foundation(f++);
            printf("\tF%d", ++f);
        }

        printf("\n");
    }
}

// void pregame_layout_cards(bool show_cards)
// {
//     printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
//     // make this ** and contain each element
//     column_card *c1 = cols->columns[0]->head;
//     column_card *c2 = cols->columns[1]->head;
//     column_card *c3 = cols->columns[2]->head;
//     column_card *c4 = cols->columns[3]->head;
//     column_card *c5 = cols->columns[4]->head;
//     column_card *c6 = cols->columns[5]->head;
//     column_card *c7 = cols->columns[6]->head;
//     int i = 0, f = 0;
//     while (c1 != nullptr || c2 != nullptr || c3 != nullptr || c4 != nullptr || c5 != nullptr || c6 != nullptr || c7 != nullptr)
//     {
//         c1 = layout_field(c1, 1, 1);
//         c2 = layout_field(c2, 2, 2);
//         c3 = layout_field(c3, 3, 3);
//         c4 = layout_field(c4, 3, 3);
//         c5 = layout_field(c5, 3, 3);
//         c6 = layout_field(c6, 3, 3);
//         c7 = layout_field(c7, 3, 3);

//         i++;
//         if (i == 1 || i == 3 || i == 5 || i == 7)
//         {
//             printf("\t\t");
//             layout_foundation(f++);
//             printf("\tF%d", f);
//         }

//         printf("\n");
//     }
// }

#endif