#ifndef _PLAY_GAME
#define _PLAY_GAME
#include "headers.h"

void release_memory()
{
    struct column_card *tmp;

    printf("--freeing columns--\n");
    for(int i = 0; i < 7; i++)
    {
        column_card *head = cols->columns[i]->head;
        // printf("--column--\n");
        while(head != NULL)
        {
            tmp = head;            
            head = head->next;
            free(tmp);
        }
    }
    // printf("head: %d\n", cols->columns[0]->head->stack_card->isturned);

    printf("--freeing stack--\n");
    for(int i = 0; i < CARDSIZE; i++)
    {
        free(stack.cards_ref[i]);        
    }            
    // printf("stack id : %d\n", stack.cards_ref[0]->id);
}

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