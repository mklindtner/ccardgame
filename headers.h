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
#define MAX_LENGTH_FILE 52*4+1


//layout
void msg_bottom_left_last_message(char const *msg);
void msg_bottom_left_message(char const *msg);
void msg_bottom_left_input(char const *msg);
void layout();

extern char const *empty;
extern char const *header;
extern char const *sSPADE;
extern char const *sHEARTS;
extern char const *sDIAMONDS;
extern char const *sCLOVER;
extern char const *KING;
extern char const *QUEEN;
extern char const *JACK;
extern char const *TEN;
extern char const *ACE;
extern char quit;
extern char quit_game;

extern char *letter;
extern char *g_msg;
extern char *pregame_cmd;
extern char *pregame_arg;
extern char *card_tmp;

enum MSGTYPE {LAST, MESSAGE, INPUT};
enum COLOR {SPADE, HEARTS, DIAMONDS, CLOVER, NOTFOUND};

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

extern card **card_definition_list;
extern sfoundations *fonds;
extern scolumns *cols;
extern stack_card **cards_ref;
extern sstack stack;
extern scolumns *copycols;



//card functions
void write_name(card **col);
card **push(card **head_ref, int number, COLOR color);
card **generate_cards(int placeholder);
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
void pregame_layout(char *input, bool show_cards);
void pregame_layout_cards(bool show_cards);
void pregame_empty();
bool pregame_main(char *input);
void pregame_LD(char *input, char *pregame_cmd, char *pregame_arg);
void cut_space(char *input);
void SR_shuffle();
void pregame_SI(int split_point);

//game
void play_game(char *input);
void setup_cards();

#endif



