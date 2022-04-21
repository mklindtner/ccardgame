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
#define MAX_INPUT_SZ 256
#define PREGAME_ROWSIZE 8


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

char const *KING = "K";
char const *QUEEN = "Q";
char const *JACK = "J";
char const *TEN = "T";
char const *ACE = "A";
char *letter = (char *)malloc(sizeof(char)*2);
char *g_msg = (char *)malloc(sizeof(char)*100);
char *pregame_cmd = (char *)malloc(sizeof(char)*3);
char *pregame_arg = (char *)malloc(sizeof(char)*MAX_INPUT_SZ-2);
char *card_tmp = (char *)malloc(sizeof(char)*3);


enum MSGTYPE {LAST, MESSAGE,INPUT};
enum COLOR {SPADE, HEARTS, DIAMONDS,CLOVER,  NOTFOUND};
void f_set(int fnum);
char const *int_to_suit(int color);




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

//7 columns
//array for columns
typedef struct scolumns {
    column_card **columns; 
}scolumns;

typedef struct sfoundations {
    column_card **foundations;
}sfoundations;

sfoundations *fonds = (sfoundations *)malloc(sizeof(sfoundations));
scolumns *cols = (scolumns *)malloc(sizeof(scolumns));
stack_card **cards_ref = (stack_card **)malloc(sizeof(stack_card)*CARDSIZE);
sstack stack = {cards_ref}; 

scolumns *copycols = (scolumns *)malloc(sizeof(scolumns));



//card functions
void write_name(card **col);
card **push(card **head_ref, int number, COLOR color);
card **generate_cards(card **placeholder);
column_card *find_card_payload(int idcolumn,int number, char *_color);
enum COLOR string_to_color(char *color);
const char *color_to_string(enum COLOR c);
int letter_to_int(char letter);


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
char const *int_to_suit(int color);
char const *int_to_letter(int cardvalue);
void start_layout_table(char *input);
void layout_foundation(int fond_id);

//foundation functions
stack_card *find_card_payload_foundation(int from_foundation);

//commands
char **split_move(char *input, char *pos);
void move_col_card(char **input);
char *lhss_pad_card(char *lhss);
char validate_move(int to_column, card *cvalidate);
char validate_move_foundation(int to_foundation, card *cvalidate);

//pregame
void pregame_layout_foundation(char *input, bool show_cards);
void pregame_layout_cards(bool show_cards);
void pregame_empty();
#endif



