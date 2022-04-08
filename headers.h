#ifndef _HEADERS
#define _HEADERS
#include <stdio.h>

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

// //each column contain 1 cards
typedef struct column {
    // int id;
    // card *val;
    card cards[];
    // struct column *next; //next column
}column;

//card functions
void write_name(card **col);
card **push(card **head_ref, int number, COLOR color);

card **generate_cards(card **placeholder);

// typedef struct column {
//     int id;
//     cards *c;
// };




#endif



