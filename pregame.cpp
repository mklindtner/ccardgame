#ifndef _PREGAME
#define _PREGAME
#include "headers.h"

void pregame_LD(char *input)
{
    // printf("arg length: %d\n", (int) strlen(pregame_arg));
    if (strlen(pregame_arg) < 1)
    {
        // shuffle_stack();
        pregame_layout(input, false);
    }
    else
    {
        char buff[MAX_LENGTH_FILE];
        FILE *f = fopen(pregame_arg, "r");
        char *reader = nullptr;
        int i = 0;
        card *head = stack.cards_ref[0]->card;
        do
        {
            fgets(buff, MAX_LENGTH_FILE, f);
            int number = letter_to_int(buff[0]);
            COLOR suit = string_to_color(&buff[1]);
            int index = suit * 13 + number;
            // printf("head is: %d\t head next: %d\n", head->number, head->next->number);
            // card *ccur = head;
            // for (int i = 0; i < index; i++)
            // {
            //     ccur = head->next;
            // }

            // stack.cards_ref[i]->card = head;
            // printf("cards number: %d\n", cards[index]->number);
            i++;
            // for(int i = 0; i < index; i++)
            // {

            // }
            // stack.cards_ref[index]->card =

            // stack.cards_ref[i]

            // printf("num: %d\t",number);
        } while (!feof(f));
        printf("\nout of loop\n");
        fclose(f);
    }
}

void pregame_SD()
{
    if (strlen(pregame_arg) < 1)
    {
        sprintf(pregame_arg, "%s", "cards.txt");
    }
    FILE *f = fopen(pregame_arg, "w+");

    for (int i = 0; i < CARDSIZE; i++)
    {
        card *c = stack.cards_ref[i]->card;
        char const *suit = int_to_suit(c->color);
        char const *letter = int_to_letter(c->number);
        if (i == CARDSIZE - 1)
        {
            sprintf(card_tmp, "%s%s", letter, suit);
        }
        else
        {
            sprintf(card_tmp, "%s%s\n", letter, suit);
        }
        fputs(card_tmp, f);
    }

    fclose(f);
}
void pregame_main(char *input)
{
    // pregame, only relevant if pos is 2 long
    //  printf("input is:|%s|\n",input);
    if (strcmp(&input[1], "\0"))
    {
        // cut 2 first letters here
        sprintf(pregame_cmd, "%.2s", input);
        sprintf(pregame_arg, "%s", input + 3);
        printf("pregame_cmd: |%s|\n", pregame_cmd);
        printf("pregame_arg: |%s|\n", pregame_arg);

        if (!strcmp(pregame_cmd, "LD"))
        {
            pregame_LD(input);
        }

        if (!strcmp(pregame_cmd, "SD"))
        {
            pregame_SD();
        }

        if (!strcmp(pregame_cmd, "SW"))
        {
            pregame_layout(input, true);
        }
    }
}

void pregame_layout(char *input, bool show_cards)
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
                if (show_cards)
                {
                    printf("%s%s\t", num, suit);
                }
                else
                {
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