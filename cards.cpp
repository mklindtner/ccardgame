#include "headers.h"


//C1->C2
//C1:1S->C2
//C4:2D->C1
column_card *find_card_payload(int idcolumn,int number, char *_color)
{
    //convert char to enum
    COLOR color = string_to_color(_color);
    // printf("after string_to_color\n");
    column_card *column_card = cols->columns[idcolumn]->head;
    // printf("looking for colid: %d\t number: %d\tcolor: %d\n",idcolumn, number, color);
    while(column_card != nullptr)
    {
        card *c = column_card->stack_card->card;
        // printf("----\n");
        // printf("card number: %d\tcard color: %d\n",c->number, c->color);
        if(c->number == number && c->color == color)
        {
            // printf("<FOUND CARD>\n");
            return column_card;  
        }    
        column_card = column_card->next;
    }
    // printf("card not found\n");
    sprintf(g_msg, "CARD NOT FOUND");
    return nullptr;
}

int letter_to_int(char letter)
{
    if(!strncmp(&letter, ACE, 1)) { return 1;}
    if(!strncmp(&letter, TEN, 1)) {return 10;}
    if(!strncmp(&letter, JACK, 1)) {return 11;} 
    if(!strncmp(&letter, QUEEN, 1)) {return 12;} 
    if(!strncmp(&letter, KING, 1)) {return 13;} 
    return atoi(&letter);
}

char const *int_to_letter(int cardvalue) {
    switch(cardvalue)
    {
        case 1:
            return ACE;
            break;
        case 10:
            return TEN;
            break;
        case 11:
            return JACK;
            break;
        case 12:
            return QUEEN;
            break;
        case 13:
            return KING;
            break;
        default:
            sprintf(letter, "%d", cardvalue);
            return letter;
    }
}

enum COLOR string_to_color(char *color)
{        
    // printf("colorz: %s\n", color);
    if(!strncmp(color,sSPADE,1))
    {
        return COLOR::SPADE;
    }
    if(!strncmp(color,sHEARTS,1))
    {
        return COLOR::HEARTS;
    }
    if(!strncmp(color,sDIAMONDS,1))
    {
        return COLOR::DIAMONDS;
    }
    if(!strncmp(color,sCLOVER,1))
    {
        return COLOR::CLOVER;
    }
    sprintf(g_msg, "COLOR NOT FOUND");
    return COLOR::NOTFOUND;
}

const char *color_to_string(enum COLOR c)
{
    if(c == COLOR::SPADE)
    {
        return sSPADE;
    }
    if(c == COLOR::HEARTS)
    {
        return sHEARTS;
    }
    if(c == COLOR::DIAMONDS)
    {       
        return sDIAMONDS;
    }
    if(c == COLOR::CLOVER)
    {        
        return sCLOVER;
    }
    return nullptr;
}


void reversell()
{
    for (int i = 0; i < COLUMNSIZE; i++)
    {
        column_card *cc = cols->columns[i]->head;
        column_card *next = nullptr;
        column_card *prev = nullptr;
        while (cc != nullptr)
        {
            next = cc->next;
            // Reverse current node's pointer

            cc->next = prev;
            // Move pointers one position ahead.
            prev = cc;
            cc = next;
        }
        cols->columns[i]->head = prev;
    }
}

void rm_col_card(column_card *elem, int colid)
{
    column_card *cc = cols->columns[colid]->head;
    column_card *prev = nullptr;
    while (cc != elem)
    {
        prev = cc;
        cc = cc->next;
    }

    if (cc == cols->columns[colid]->head)
    {
        free(cc);
        return;
    }
    // remove element that's not header
    prev->next = cc->next;
    free(cc);
}

card **push(card **head_ref, int number, COLOR color)
{
    card *new_node = (card *)malloc(sizeof(card));

    new_node->number = number;
    new_node->color = color;    

    new_node->next = (*head_ref);

    (*head_ref) = new_node;

    card_definition_list[color*13 + number - 1] = new_node;
    return head_ref;
}

// col1 represents the number of column
int placearray[CARDSIZE] = {
    1, 2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7,
    3, 4, 5, 6, 7,
    4, 5, 6, 7,
    5, 6, 7,
    6, 7,
    7};



// generate_cards must be called first
void initialize_columns()
{
    for (int i = 0; i < CARDSIZE; i++)
    {
        column_card *c = cols->columns[placearray[i] - 1];
        stack_card *sc = stack.cards_ref[i];
        push_stack_to_column(sc, c);
    }
}

void push_stack_to_column(stack_card *sc, column_card *col)
{
    // new head
    column_card *cc = (column_card *)malloc(sizeof(column_card));
    cc->stack_card = sc;
    cc->next = nullptr;
    column_card *tmp = nullptr;
    if (col->head != nullptr)
    {
        tmp = col->head;
        cc->next = tmp;
    }
    col->head = cc;
}

// make columns, no header made
void generate_columns()
{
    // allocate array in struct
    (*cols).columns = (column_card **)malloc(sizeof(column_card) * COLUMNSIZE);
    (*fonds).foundations = (column_card **)malloc(sizeof(column_card) * FOUNDATIONSIZE);

    for (int i = 0; i < COLUMNSIZE; i++)
    {
        (*cols).columns[i] = (column_card *)malloc(sizeof(column_card));
    }

    for(int j = 0; j < FOUNDATIONSIZE; j++)
    {
        (*fonds).foundations[j] = (column_card *)malloc(sizeof(column_card));
    }
}

void swap_stack_card(int r1, int r2)
{

    // we could flex here and use xor instead
    stack_card *tmp = stack.cards_ref[r1];
    stack.cards_ref[r1] = stack.cards_ref[r2];
    stack.cards_ref[r2] = tmp;
}

void setup_cards()
{
    //testing for C2->F1 (put 2S unto AS)
    // swap_stack_card(1, 31);

    //bug error nr. 16
    //C3:8H->C6
    //C2->F1
    //C3->F1
    // swap_stack_card(13,31);
    // swap_stack_card(47, 49);

    
}

// this is shuffle deck
// rand is unsafe, we should use libsodium but cba https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
void shuffle_stack()
{
    srand(time(NULL));
    // times we randomize array
    for (int i = 0; i < 5; i++)
    {
        // randomize entire array
        for (int j = 0; j < CARDSIZE; j++)
        {
            int r1 = rand() % CARDSIZE;
            int r2 = rand() % CARDSIZE;
            swap_stack_card(r1, r2);
        }
    }
}

void turn_card(stack_card *sc, bool isturned)
{
    sc->isturned = isturned;
}

void push_stack_card(int id, card *card)
{
    stack_card *scard = (stack_card *)malloc(sizeof(stack_card));
    scard->id = id;
    scard->card = card;
    scard->isturned = false;
    stack.cards_ref[id] = scard;
    // card_definition_list[id] = card;
}

card **generate_cards(int nothing)
{
    int one_color = 13;
    card **prev = (card **)malloc(sizeof(card));
    // card_definition_list[0] = prev[0];

    prev = push(prev, 1, COLOR::SPADE);    
    push_stack_card(0, *prev);

    // start 1-off due to head in linked list
    for (int i = 1; i < CARDSIZE; i++)
    {
        if (i < one_color)
        {             
            // card_definition_list[i] = prev[0];   
            prev = push(prev, i + 1, COLOR::SPADE); //(new insertion) -> null
        }
        else if (i < one_color * 2)
        {
            // card_definition_list[i] = prev[0];   
            prev = push(prev, (i + 1) - one_color, COLOR::HEARTS);
        }
        else if (i < one_color * 3)
        {
            // card_definition_list[i] = prev[0];   
            prev = push(prev, (i + 1) - one_color * 2, COLOR::DIAMONDS);
        }
        else
        {
            // card_definition_list[i] = prev[0];   
            prev = push(prev, (i + 1) - one_color * 3, COLOR::CLOVER);
        }
        push_stack_card(i, *prev);
    }
    return prev;
}

column_card *last_elem_col(int id)
{
    column_card *cc = cols->columns[id]->head;
    column_card *prev = nullptr;
    while (cc != nullptr)
    {
        prev = cc;
        cc = cc->next;
    }
    return prev;
}

// debugging writes
void write_single_column(int id)
{
    column_card *cc = cols->columns[id]->head;
    while (cc != nullptr)
    {
        printf("head: %p\t card num: %d\n", cc, cc->stack_card->card->number);
        cc = cc->next;
    }
}

void write_columns()
{
    for (int i = 0; i < COLUMNSIZE; i++)
    {
        column_card *head = cols->columns[i]->head;
        printf("col num: %d\thead: %p\t card num: %d\n", i, head, head->stack_card->card->number);
    }
}

void write_stack()
{
    stack_card *t = stack.cards_ref[0];
    for (int i = 0; i < CARDSIZE; i++)
    {
        stack_card *sc = stack.cards_ref[i];
        printf("cnum: %d\t ccolor: %d\t", sc->card->number, sc->card->color);
    }
}

void write_name(card **col)
{
    card *cur = (*col);
    while (cur != NULL) // columns
    {
        printf("num: %d\t type: %d\t ", cur->number, cur->color);
        cur = cur->next;
    }
    printf("\n");
    return;
}

// todo: fix naming: https://stackoverflow.com/questions/9907160/how-to-convert-enum-names-to-string-in-c
void write_card(card *card)
{

    printf("%d:%d", card->number, card->color);
}
