#include <stdio.h>
#include "headers.h"
#include "mainwindow.cpp"
#include "cards.cpp"
#include "commands.cpp"
#include "pregame.cpp"

int main()
{
    card **cards = generate_cards(0);
    // shuffle_stack();
    generate_columns();
    initialize_columns();
    int foo = 1;
    start_turn();
    sprintf(g_msg, "");
    char firsttime = true;

    char *input = (char *)malloc(sizeof(char) * 40);
    start_layout_table(input);
    while (1)
    {
        system("clear");
        sprintf(g_msg, "");

        fgets(input, MAX_INPUT_SZ, stdin);
        char *pos = strstr(input, "->");

        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
        {
            input[strlen(input) - 1] = '\0';
        }

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
                // printf("arg length: %d\n", (int) strlen(pregame_arg));
                if (strlen(pregame_arg) < 1)
                {
                    // shuffle_stack();

                    pregame_layout_foundation(input, false);
                    // printf("no argument\n");
                }
                else
                {                    
                    printf("called LD w.argument\n");
                }
            }

            if (!strcmp(pregame_cmd, "SD"))
            {
                if (strlen(pregame_arg) < 1)
                {
                    sprintf(pregame_arg, "%s", "cards.txt");
                }

                FILE *f = fopen(pregame_arg, "w+");                
                // get cards
                for (int i = 0; i < CARDSIZE; i++)
                {
                    card *c = stack.cards_ref[i]->card;
                    char const *suit = int_to_suit(c->color);
                    char const *letter = int_to_letter(c->number);
                    sprintf(card_tmp, "%s%s\n", letter, suit);
                    fputs(card_tmp, f);
                }
                fclose(f);
            }

            // if for sw

            // if for..
        }

        // play mode, only relevant if pos is 1 long
        if (!strcmp(input, "P"))
        {
            while (1)
            {
                layout_tableau();
                msg_bottom_left_last_message(input);
                msg_bottom_left_message(g_msg);
                msg_bottom_left_input(empty);
                sprintf(g_msg, "");
                scanf("%s", input);
                if (!strcmp(input, "Q"))
                {
                    break;
                }
                if (pos)
                {
                    //['C1:A1']
                    char **c = split_move(input, pos);
                    printf("--------------------\n");
                    move_col_card(c);
                }
            }
        }
    }

    // rm_col_card(cc,foo);
    // write_single_column(foo);
    // write_columns();
    // write_stack();

    return 0;
}
