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

    char *input = (char *)malloc(sizeof(char) * 40);
    while (1)
    {
        system("clear");
        layout_tableau();
        msg_bottom_left_last_message(input);
        msg_bottom_left_message(empty);
        msg_bottom_left_input(empty);
        scanf("%s", input);
        char *pos = strstr(input, "->");

        if (!strcmp(input, "Q"))
        {
            break;
        }
        if (pos)
        {
            char **c = split_move(input, pos);
            // printf("outer loop lhs: |%s|\n rhs: |%s|\n", c[0],c[1]);
            move_col_card(c);            
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
    *split_move (commands.cpp) has a huge memory leak and doesn't clean any pointers, fix this.
    *move_col_card uses atoi, this is a deprecated function, we should swap
    
    
NOTICE
    *move_col_card doesn't converge "A,Q,J,K" into a number
    *find_card_by_payload (cards.cpp) doesn't account for F (foundations)
    *find_card_by_payload doesn't account for giving a wrong color/id of a card
    *transfer_columns cannot currently move to an empty column
    *transfer_columns does not consider a null-head
        *more exceptions to consider
    
    *the program does not deal with cols->columns[i]->head = nullptr, implement this behavior
 */