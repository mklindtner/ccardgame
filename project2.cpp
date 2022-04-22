#include <stdio.h>
#include "headers.h"
#include "mainwindow.cpp"
#include "cards.cpp"
#include "commands.cpp"
#include "pregame.cpp"


int main()
{
    card **cards = generate_cards(0);
    // printf("card number: %d\n",cards[0]->next->next->number);
    // shuffle_stack();
    generate_columns();
    initialize_columns();
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
        cut_space(input);

        pregame_main(input);

        // play mode
        if (!strcmp(input, "P"))
        {
            while (1)
            {
                layout_tableau();
                msg_bottom_left_last_message(input);
                msg_bottom_left_message(g_msg);
                msg_bottom_left_input(empty);
                sprintf(g_msg, "");

                fgets(input, MAX_INPUT_SZ, stdin);
                char *pos = strstr(input, "->");
                cut_space(input);

                if (!strcmp(input, "Q"))
                {
                    break;
                }
                if (pos)
                {
                    //['C1:A1']
                    char **c = split_move(input, pos);
                    printf("lhs: %s\t rhs:%s\n", c[0], c[1]);
                    printf("--------------------\n");
                    move_col_card(c);
                }
            }
        }
    }

    return 0;
}

void cut_space(char *input)
{
    // printf("input before cut: |%s|\n", pos, input);
    if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
    {
        input[strlen(input) - 1] = '\0';
    }
    // printf("input after cut: |%s|\n", input);
}