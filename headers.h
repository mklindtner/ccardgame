#ifndef _HEADERS
#define _HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define CARDSIZE 52
#define COLUMNSIZE 7
#define FOUNDATIONSIZE 4

//commands
char **split_move(char *input, char *pos);
void move_col_card(char **input);

//layout
void msg_bottom_left_last_message(char const *msg);
void msg_bottom_left_message(char const *msg);
void msg_bottom_left_input(char const *msg);
void layout();


char const *empty = "";
char const *header = "C1\tC2\tC3\tC4\tC5\tC6\tC7";
char const *sSPADE = "S";
char const *sHEARTS = "H";
char const *sDIAMONDS = "D";
char const *sCLOVER = "C";

enum MSGTYPE {LAST, MESSAGE,INPUT};
enum COLOR {SPADE, HEARTS, DIAMONDS,CLOVER};
void f_set(int fnum);
char const *get_number(int color);




typedef struct card {
    COLOR color;
    int number;
    struct card *next;
}card;

//row in stack
typedef struct stack_card {
    int id;
    // bool ondeck;
    bool isturned;   
    card *card;
}stack_card;

typedef struct sstack {
    stack_card **cards_ref;
}sstack;

//a single column (linked list) containing a column card on each payload
typedef struct column_card {
    struct stack_card *stack_card;
    struct column_card *next;
    struct column_card *head;    
}column_card;

// typedef struct output_card {
//     int id;
//     stack_card *c;
// }output_card;

//7 columns
//array for columns
typedef struct scolumns {
    column_card **columns; 
}scolumns;


scolumns *cols = (scolumns *)malloc(sizeof(scolumns));
stack_card **cards_ref = (stack_card **)malloc(sizeof(stack_card)*CARDSIZE);
sstack stack = {cards_ref}; 

scolumns *copycols = (scolumns *)malloc(sizeof(scolumns));



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
void push_stack_to_column(stack_card *sc, column_card *col);
void write_columns();
void rm_col_card(column_card *elem, int colid);
void reversell();
void layout_tableau();
void initialize_columns();
void start_turn();

//window functions
column_card *layout_field(column_card *c, int tabs, int);

#endif



