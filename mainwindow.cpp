#ifndef _MAINWINDOW
#define _MAINWINDOW
// make a shared cpp file for headers
#include "headers.h"

int turnarray[CARDSIZE] = {
    1, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0,
    1, 1, 1, 1, 0, 0,
    1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1,
    1, 1,
    1};

void start_turn()
{
    for (int i = 0; i < CARDSIZE; i++)
    {
        stack_card *sc = stack.cards_ref[i];
        sc->isturned = turnarray[i];
    }
}

// use cards to place
void layout_tableau()
{
    reversell();
    // make this ** and contain each element
    column_card *c1 = cols->columns[0]->head;
    column_card *c2 = cols->columns[1]->head;
    column_card *c3 = cols->columns[2]->head;
    column_card *c4 = cols->columns[3]->head;
    column_card *c5 = cols->columns[4]->head;
    column_card *c6 = cols->columns[5]->head;
    column_card *c7 = cols->columns[6]->head;
    while (c1 != nullptr || c2 != nullptr || c3 != nullptr || c4 != nullptr || c5 != nullptr || c6 != nullptr || c7 != nullptr)
    {
        // for(int i = 0; i <COLUMNSIZE; i++)
        // {
        //     pp[i] = layout_field(pp[i], 1, 1);
        // }
        c1 = layout_field(c1, 1, 1);
        c2 = layout_field(c2, 2, 2);
        c3 = layout_field(c3, 3, 3);
        c4 = layout_field(c4, 3, 3);
        c5 = layout_field(c5, 3, 3);
        c6 = layout_field(c6, 3, 3);
        c7 = layout_field(c7, 3, 3);

        printf("\n");
    }

    reversell();
}

column_card *layout_field(column_card *c, int tabs, int colnum)
{
    if (c != nullptr)
    {
        stack_card *sc = c->stack_card;
        if (sc->isturned == true)
        {
            char const *num = get_number(sc->card->color);
            printf("%d%s\t", sc->card->number, num);
        }
        else
        {
            printf("[]\t");
        }
        c = c->next;
    }
    else
    {
        printf("\t");
    }
    return c;
}

char const *get_number(int color)
{
    switch (color)
    {
    case 0:
        return sSPADE;
        break;
    case 1:
        return sHEARTS;
        break;
    case 2:
        return sDIAMONDS;
        break;
    case 3:
        return sCLOVER;
        break;
    default:
        return nullptr;
    }
    return nullptr;
}

void layout()
{
    printf("%s", header);
    f_set(1);
    f_set(2);
    f_set(3);
    f_set(4);
    char const *m = "";
    msg_bottom_left_last_message(m);
    msg_bottom_left_message(m);
    msg_bottom_left_input(m);
}

void f_set(int fnum)
{
    const char *tabs = "\t\t\t\t\t\t\t\t";
    switch (fnum)
    {
    case 1:
        printf("\n%s[]\tF1\n\n", tabs);
        break;
    case 2:
        printf("%s[]\tF2\n\n", tabs);
        break;
    case 3:
        printf("%s[]\tF3\n\n", tabs);
        break;
    case 4:
        printf("%s[]\tF4\n", tabs);
        break;
    default:
        char const *err = "f not specificed";
        msg_bottom_left_last_message(err);
    }
}

void all_bottom_left(char const *msg, MSGTYPE t)
{
    // LAST
    if (t == 0)
    {
        msg_bottom_left_last_message(msg);
        msg_bottom_left_message(empty);
        msg_bottom_left_input(empty);
        return;
    }
}

void msg_bottom_left_last_message(char const *msg)
{
    // printf("\n\n\n\n");
    printf("LAST Command: %s\n", msg);
}

void msg_bottom_left_message(char const *msg)
{
    // printf("\n\n\n\n\n\n");
    printf("Message: %s\n", msg);
}

// this is just a placeholder for now, don't use to update automatically
void msg_bottom_left_input(char const *msg)
{
    // printf("\n\n\n\n\n\n\n");
    printf("INPUT > %s", msg);
    // msg_bottom_left_last_message(msg);
}


#endif