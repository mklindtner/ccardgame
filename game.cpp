#ifndef _PLAY_GAME
#define _PLAY_GAME
#include "headers.h"

void play_game(char *input)
{
    // printf("--starting play--\n");
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

#endif