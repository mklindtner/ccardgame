#ifndef _PLAY_GAME
#define _PLAY_GAME
#include "headers.h"

//untested
void make_sorted_memory()
{
    generate_columns();
    printf("--sucessfully generated columns---\n");
    start_turn();
    printf("--sucessfully start_turn---\n");
    initialize_columns();
    printf("--successfully initialized columns--\n");
}

void release_memory()
{
    // printf("--freeing columns--\n");
    
    //free columns
    for (int i = 0; i < 7; i++)
    {
        struct column_card *tmp;
        column_card *head = cols->columns[i]->head;
        // printf("--column--\n");
        while (head != NULL)
        {
            // printf("<<<<<<<<HERE>>>>>>>>>>>>>>>\n");
            tmp = head;
            // tmp->stack_card = nullptr;
            head = head->next;
            free(tmp);
        }
        cols->columns[i]->head = nullptr;
    }

    //free foundation
    for (int i = 0; i < 4; i++)
    {
        struct column_card *tmp;
        column_card *head = fonds->foundations[i]->head;
        while (head != NULL)
        {
            tmp = head;
            head = head->next;
            free(tmp);
        }
        fonds->foundations[i]->head = nullptr;
    }
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