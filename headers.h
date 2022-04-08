#ifndef _HEADERS
#define _HEADERS
#include <stdio.h>
#include <stdlib.h>
#define CARDSIZE 52
#define COLUMNSIZE 7
#define FOUNDATIONSIZE 4

void msg_bottom_left_last_message(char const *msg);
void msg_bottom_left_message(char const *msg);
void msg_bottom_left_input(char const *msg);
void layout();


char const *empty = "";
char const *header = "C1\tC2\tC3\tC4\tC5\tC6\tC7";
enum MSGTYPE {LAST, MESSAGE,INPUT};
enum COLOR {SPADE, HEARTS, DIAMONDS,CLOVER};
void f_set(int fnum);


typedef struct card {
    COLOR color;
    int number;
    bool isturned;   
    struct card *next;
}card;

//each column contain 1 cards
typedef struct stack_card {
    int id;
    bool ondeck;
    card *card;
}stack_card;

typedef struct sstack {
    stack_card **cards_ref;
}sstack;

//linked list to store stack_cards
typedef struct column_card {
    struct stack_card *stack_card;
    struct column_card *next;
}column_card;

//linked list for .. ? 
typedef struct column {
    struct column_card *head;
}column;

//7 columns
//array for columns
typedef struct scolumns {
    column **columns; 
}scolumns;


scolumns *cols;
stack_card **cards_ref = (stack_card **)malloc(sizeof(stack_card)*CARDSIZE);
sstack stack = {cards_ref}; 

//card functions
void write_name(card **col);
card **push(card **head_ref, int number, COLOR color);

card **generate_cards(card **placeholder);

//stack functions
void write_stack();
void swap_stack_card(int j);
void shuffle_stack();

//column funcitons
void generate_columns();
void push_stack_to_column(stack_card *sc, column *col);
void write_columns();
void rm_col_card(column_card *elem, int colid);


#endif



