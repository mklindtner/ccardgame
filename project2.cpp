#include <stdio.h>
#include "headers.h"
#include "mainwindow.cpp"
#include "cards.cpp"
#include "commands.cpp"

int main()
{
    card **cards = generate_cards(0);
    // write_name(cards);
    shuffle_stack();
    generate_columns();
    initialize_columns();
    int foo = 1;
    // write_single_column(foo);
    // column_card *cc = last_elem_col(foo);
    // make_copy();
    // write_single_column(foo);
    start_turn();
    sprintf(g_msg, "");
    // g_msg = "";
    char *input = (char *)malloc(sizeof(char) * 40);
    while (1)
    {
        system("clear");
        layout_tableau();
        msg_bottom_left_last_message(input);
        msg_bottom_left_message(g_msg);
        msg_bottom_left_input(empty);
        sprintf(g_msg, "");
        scanf("%s", input);
        char *pos = strstr(input, "->");

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

    // rm_col_card(cc,foo);
    // write_single_column(foo);
    // write_columns();
    // write_stack();

    return 0;
}

