#include <stdio.h>
#include "headers.h"
#include "mainwindow.cpp"
#include "cards.cpp"
#include "commands.cpp"

int main()
{
    card **cards = generate_cards(0);    
    // write_name(cards);
    // shuffle_stack();
    generate_columns();
    initialize_columns();
    int foo = 1;
    // write_single_column(foo);
    // column_card *cc = last_elem_col(foo);
    // make_copy();
    // write_single_column(foo);
    start_turn();
    // layout_tableau();    

    char *input = (char *)malloc(sizeof(char)*40);
    while(1)
    {
        system("clear");
        layout_tableau();
        msg_bottom_left_last_message(input);
        msg_bottom_left_message(empty);
        msg_bottom_left_input(empty);       
        scanf("%s",input);
        char *pos = strstr(input, "->");

        if(!strcmp(input, "Q"))
        {
            break;
        }
        if(pos)
        {            
           char **c = split_move(input, pos);
        } 
    }



    // rm_col_card(cc,foo);
    // write_single_column(foo);
    // write_columns();
    // write_stack();

    return 0;
}


/* tests / todos
    *make sure input can deal w. spaces (i.e. "C4 -> C4")
    *strlen(input)- strlen(pos) returns a float, floor this so we get an integer
*/