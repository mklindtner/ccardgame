#include <stdio.h>
//#include "mainwindow.cpp"
//#include "headers.h"
#include "cards.cpp"

int main()
{
    // system("clear");
    // layout();

    // char *input;
    // while(1)
    // {
    //     scanf("%s",input);
    //     // msg_bottom_left_last_message(input);
    //     // msg_bottom_left_input(empty);
       
    // }

    card **cards = generate_cards(0);    
    // write_name(cards);
    shuffle_stack();
    generate_columns();
    initialize_columns();
    write_columns();
    // write_stack();

    return 0;
}


/*
make layout()
make 

*/