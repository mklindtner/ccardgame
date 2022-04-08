#ifndef _MAINWINDOW
#define _MAINWINDOW
//make a shared cpp file for headers 
#include <stdio.h>
#include "headers.h"
#include <stdlib.h>

//load msg here




// void LD()
// {
//     system("clear");
//     printf("%s",header);
    
// }

void layout()
{
    printf("%s",header);
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
    switch(fnum)
    {
        case 1:
           printf("\n%s[]\tF1\n\n",tabs);
           break;
        case 2:
            printf("%s[]\tF2\n\n",tabs);
            break;
        case 3:
            printf("%s[]\tF3\n\n",tabs);
            break;
        case 4:
            printf("%s[]\tF4\n",tabs);  
            break;
        default:
            char const *err = "f not specificed";
            msg_bottom_left_last_message(err);
    }
}

void all_bottom_left(char const *msg, MSGTYPE t)
{
    //LAST
    if(t == 0)
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
    //printf("\n\n\n\n\n\n");
    printf("Message: %s\n", msg);
}

//this is just a placeholder for now, don't use to update automatically
void msg_bottom_left_input(char const *msg)
{
    // printf("\n\n\n\n\n\n\n");
    printf("INPUT > %s",msg);
    //msg_bottom_left_last_message(msg);
    
}
#endif